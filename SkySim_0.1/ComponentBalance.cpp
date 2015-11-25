#include "stdafx.h"
#include "ComponentBalance.h"
#include "UnitOp.h"
#include "Stream.h"

ComponentBalance::ComponentBalance()
{

	_name = "ComponentBalance";
}


bool ComponentBalance::_calculate()
{
	int nin, nout;
	nin = _parent->NInlets();
	nout = _parent->NOutlets();

	int ncompknown = 0;
	int nflowknown = 0;
	bool flowpassed = false;
	bool comppassed = false;
	double sumMol = 0;
	double sumMass = 0;
	Stream* UnknownX = 0;
	double* X;
	RealVariable* UnknownFmol = 0;
	RealVariable* UnknownFmass = 0;
	RealVariable* KnownX = 0;
	int massflowdir = 0;
	int molflowdir = 0;
	int Xdir = 0;
	double* moles;
	Stream* refstrm = 0;
	//if mixer i can have nstreams-1 compositions. i need all molar flows.
	//if valve i dont need flows. need 1 composition
	//if splitter i can have 1 composition. i dont actually need any flows

	int ncomps = _parent->GetStream(0, INLET)->NComps();
	X = new double[ncomps]{0};
	moles = new double[ncomps]{0};
	for (int k = 0; k < ncomps; k++)
	{
		X[k] = 0;
		moles[k] = 0;
	}


	for (int i = 0; i < nin; i++)
	{
		refstrm = _parent->GetStream(i, INLET);
		if (refstrm->MolarFlow()->IsKnown())
		{
			nflowknown++;
			
		}
		if (refstrm->Composition()->IsKnown())
		{
			for (int k = 0; k < ncomps; k++)
			{
				X[k] = refstrm->Composition()->GetValue(k);
				cout << X[k] << "\n";
				moles[k] = moles[k] + X[k] * refstrm->MolarFlow()->GetValue();
				cout << moles[k] << "\n";
			}
			ncompknown++;
		}
		else
		{
			molflowdir = -1;
			UnknownX = refstrm;
		}
	}

	for (int i = 0; i < nout; i++)
	{
		refstrm = _parent->GetStream(i, OUTLET);
		if (refstrm->MolarFlow()->IsKnown())
		{
			nflowknown++;
			
		}
		if (refstrm->Composition()->IsKnown())
		{
			for (int k = 0; k < ncomps; k++)
			{
				X[k] = refstrm->Composition()->GetValue(k);
				moles[k] = moles[k] - X[k] * refstrm->MolarFlow()->GetValue();

			}
			ncompknown++;
		}
		else
		{
			molflowdir = 1;
			UnknownX = refstrm;
		}
	}

	//if mixer i can have nstreams-1 compositions. i need all molar flows.
	//if valve i dont need flows. need 1 composition
	//if splitter i can have 1 known composition. i dont actually need any flows

	if (nin == 1 & nout == 1)
	{
		if (ncompknown == 1)
		{
			if (UnknownX != 0)
			{
				for (int k = 0; k < ncomps; k++)
				{

					UnknownX->Composition()->SetValue(k, X[k]);

				}
				comppassed = true;
			}
		}
		else if (ncompknown == 2)
		{
			comppassed = true;
		}
	}
	else if (nin == 1 &&nout > 1)
	{
		if (ncompknown == 1)
		{
			for (int i = 0; i < nin; i++)
			{
				refstrm = _parent->GetStream(i, INLET);
				if (refstrm->Composition()->IsKnown() == false);
				{
					for (int k = 0; k < ncomps; k++)
					{
						refstrm->Composition()->SetValue(k, X[k]);
					}
				}
			}
			for (int i = 0; i < nout; i++)
			{
				refstrm = _parent->GetStream(i, OUTLET);
				if (refstrm->Composition()->IsKnown() == false);
				{
					for (int k = 0; k < ncomps; k++)
					{
						refstrm->Composition()->SetValue(k, X[k]);
					}
				}
			}
			comppassed = true;
			
		}
		else if (ncompknown== nout + nin)
		{
			comppassed = true;
		}
	}
	else if (nout == 1 && nin > 1)
	{
		if (ncompknown + 1 == nout + nin&& nflowknown == nout + nin)
		{
			for (int k = 0; k < ncomps; k++)
			{
				moles[k] = moles[k] / UnknownX->MolarFlow()->GetValue()*molflowdir;
				cout << moles[k] << "\n";
				UnknownX->Composition()->SetValue(k, moles[k]);
			}
		}
		else if (ncompknown== nout + nin&& nflowknown == nout + nin)
		{
			comppassed = true;
		}
	}

	if (comppassed)
	{
		return true;
	}
	else
	{
		return false;
	}
}



ComponentBalance::~ComponentBalance()
{
}
