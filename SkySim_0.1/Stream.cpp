#include "stdafx.h"
#include "Stream.h"
#include "StreamCalc.h"

Stream::Stream()
{
	/*_phases[0] = new Phase(VAPOUR);
	_phases[1] = new Phase(HCLIQUID);
	_phases[2] = new Phase(AQUEOUS);*/

	_pressure = new RealVariable;
	_temperature = new RealVariable;


	//this sets the phase P and T to the stream P and T
	/*_phases[0]->SetParent(this);
	_phases[1]->SetParent(this);
	_phases[2]->SetParent(this);*/
	//_phases[0]->_pressure = _pressure;

	AddVariable(_pressure);
	AddVariable(_temperature);
	AddVariable(_molenthalpy);
	AddVariable(_molentropy);

	AddVariable(_composition);

	_name = "fuck";
}
Stream::Stream(string daname)
{
	/*_phases[0] = new Phase(VAPOUR);
	_phases[1] = new Phase(HCLIQUID);
	_phases[2] = new Phase(AQUEOUS);*/

	_pressure = new RealVariable;
	_temperature = new RealVariable;

	/*_phases[0]->SetParent(this);
	_phases[1]->SetParent(this);
	_phases[2]->SetParent(this);*/

	//make a separate routine for this
	//should be handled by flash method -> other methods may provide more or less variables
	AddVariable(_pressure);
	AddVariable(_temperature);
	AddVariable(_molenthalpy);
	AddVariable(_molentropy);

	AddVariable(_composition);
	//AddVariable(_phases[0]->Composition());
	//AddVariable(_phases[1]->Composition());

	AddVariable(_molardensity);
	//AddVariable(_phases[0]->MolarDensity());
	//AddVariable(_phases[1]->MolarDensity());

	//AddVariable(_phases[0]->PhaseMoleFraction());
	//AddVariable(_phases[1]->PhaseMoleFraction());
	_name = daname;
}

void Stream::SetPropertyPackage(PropPack* thePP)
{
	_proppack = thePP;
}

void Stream::_setstreamcalcs()
{
	int ncalcs;

	ncalcs = _proppack->Properties()->NChildren();
	
	_streamcalcs = new StreamCalc[ncalcs];
	/*_streamcalcs[0].SetPropertyCalc(_proppack->GetFlashMethod());
	_streamcalcs[0].SetRefStream(this);*/
	//_streamcalcs = new StreamCalc[ncalcs + 1];

		for (int i = 0; i < ncalcs; i++)
		{
			_streamcalcs[i].Setup(_proppack->Properties()->GetProperty(i), this);
			//_streamcalcs[i].SetRefStream(this);
			
			//_streamcalcs[i].SetPropertyCalc(_proppack->Properties()->GetProperty(i));
		}
		//_stackobjects[_nstackobjects - 1] = &(*theSO);
	

	
	
	/*delete *(_streamcalcs[0]);
	_streamcalcs[0] = *temp;*/


	_nstreamcalcs = ncalcs + 1;
}



Stream::~Stream()
{
}


bool Stream::Solve()
{
	if (_issolved == true)
	{
		return true;
	}
	
	bool retval=true;
	//check DOF then call appropriate flash

	//calc specs
	FlashTypeEnum thetype;

	int nspecs=0;

	if (_pressure->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_temperature->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_phases[0]->PhaseMoleFraction()->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molenthalpy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_molentropy->IsKnown())
	{
		nspecs = nspecs + 1;
	}

	if (_composition->IsKnown())
	{
		nspecs = nspecs + 1;
	}
	bool* calcbythis = new bool[_nvariables]{false};

	if ((nspecs != 3))
	{
		
		cout << "Specifation error \n";
		retval = false;
		return retval;
		
	}
	_proppack->RefStream()->ReadStream(this);
		
	for (int i = 0; i < _nvariables; i++)
	{
		if (!_variables[i]->IsKnown())
		{
			//cout << i << "\n";
			calcbythis[i] = true;
		}
		else
		{
			calcbythis[i] = false;
		}
	}
	//if ((!(_pressure->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		if ((_pressure->IsKnown()) && (_temperature->IsKnown()))
		{
			//PTFlashMe();
			thetype = PT;

		}
	//}
	//else if ((!(_phases[0]->PhaseMoleFraction()->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_temperature->IsKnown()))
		{
			//TQFlashMe();
			thetype = TQ;
		}
	//}
	//else if ((!(_phases[0]->PhaseMoleFraction()->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_phases[0]->PhaseMoleFraction()->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PQ;
		}
	//}
	//else if ((!(_molenthalpy->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_molenthalpy->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PH;
		}
	//}
	//else if ((!(_molentropy->IsCalculated())) && (!(_pressure->IsCalculated())))
	//{
		else if ((_molentropy->IsKnown()) && (_pressure->IsKnown()))
		{
			//PQFlashMe();
			thetype = PS;
		}
	//}
	//else if ((!(_molentropy->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_molentropy->IsKnown()) && (_temperature->IsKnown()))
		{
			//PQFlashMe();
			thetype = TS;
		}
	//}
	//else if ((!(_molenthalpy->IsCalculated())) && (!(_temperature->IsCalculated())))
	//{
		else if ((_molenthalpy->IsKnown()) && (_temperature->IsKnown()))
		{
			//PQFlashMe();
			thetype = TH;
		}
	//}
	
	//Flash(thetype)

		_proppack->RefStream()->ReadStream(this);
		if (!_proppack->Flash(thetype))
		{
			retval = false;
		}

	othercalcs:
	/*	if (!_proppack->Properties()->Solve())
	{
		retval = false;
	}*/
	_proppack->RefStream()->WriteStream(this);
	
	for (int j = 0; j < _nvariables; j++)
	{
		if (_variables[j]->IsKnown() && calcbythis[j] == true)
		{
			_variables[j]->CalculatedBy(this);
			//cout << j << ":" << _variables[j]->GetValue() << "\n";

		}
	}

	_issolved = retval;
	return _issolved;

}


void Stream::Output()
{
	int myncomps;
	myncomps = _proppack->NComps();

	cout << "\n";
	cout << _name<< "\n";

	cout << "Pressure  [kPa] " << Pressure()->GetValue()<< "\n";
	cout << "Temperature  [K] " << Temperature()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << MolarFlow()->GetValue() << "\n";
	cout << "Mw  [g/mol] " << MolecularWeight()->GetValue() << "\n";
	//RealVariable* rv = MassDensity();
	cout << "MassDensity  [kg/m3] " << MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << MolarEntropy()->GetValue() << "\n";
	cout << "Vfrac  " << VapourFraction()->GetValue() << "\n\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << Composition()->GetValue(k) << "\n";
	}

	cout << "\n" << "GasPhase  " << "\n";
	cout << "Fraction  [mol/mol] " << _phases[0]->PhaseMoleFraction()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << _phases[0] -> MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << _phases[0] -> MolarFlow()->GetValue() << "\n";
	cout << "Mw  [g/mol] " << _phases[0]->MolecularWeight()->GetValue() << "\n";
	cout << "MassDensity  [kg/m3] " << _phases[0]->MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << _phases[0]->MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << _phases[0]->MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << _phases[0]->MolarEntropy()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{

		cout << _proppack->GetComponent(k).Name << "  " << _phases[0]->Composition()->GetValue(k) << "\n";
	}

	cout << "\n";
	cout << "LiquidPhase" << "\n";
	cout << "Fraction  [mol/mol] " << _phases[1]->PhaseMoleFraction()->GetValue() << "\n";
	cout << "MassFlow  [kg/h] " << _phases[1] -> MassFlow()->GetValue() << "\n";
	cout << "MolarFlow  [kmol/h] " << _phases[1] ->MolarFlow()->GetValue() << "\n";
	cout << "Mw  " << _phases[1]->MolecularWeight()->GetValue() << "\n";
	cout << "MassDensity  [kg/m3] " << _phases[1]->MassDensity()->GetValue() << "\n";
	cout << "MolarDensity  [mol/m3] " << _phases[1]->MolarDensity()->GetValue() << "\n";
	cout << "MolarEnthalpy  [J/mol] " << _phases[1]->MolarEnthalpy()->GetValue() << "\n";
	cout << "MolarEntropy  [J/mol/K] " << _phases[1]->MolarEntropy()->GetValue() << "\n";
	for (int k = 0; k < myncomps; k++)
	{
		cout << _proppack->GetComponent(k).Name << "  " << _phases[1]->Composition()->GetValue(k) << "\n";
	}
}

StackObject* Stream::GetStackObject(int i)
{
	if (_nstreamcalcs != _proppack->Properties()->NChildren() + 1)
	{
		_setstreamcalcs();
	}

	if (i == 0)
	{
		return this;
	}

	StackObject* thecalc = &(_streamcalcs[i - 1]);

	//dynamic_cast <StackObject*>(&(_streamcalcs[i]))
	return thecalc;
}

int Stream::NStackObjects()
{
	if (_nstreamcalcs != _proppack->Properties()->NChildren() + 1)
	{
		_setstreamcalcs();
	}
	
	return _nstreamcalcs;
}

void Stream::_addphase(PhaseTypeEnum thephasetype)
{
	_nphases++;

	int i = thephasetype;
	Phase* thenewphase = new Phase(thephasetype);
	//phases must be in order -> vap,liq,aq

	Phase** newphases = (Phase**)realloc(_phases, _nphases* sizeof(*thenewphase));
	if (_phases != NULL) //if it's null then realloc tak jadi
	{
		_phases[i] = &(*thenewphase);
	}
}


void Stream::_removephase(PhaseTypeEnum thephasetype)
{
	_nphases = _nphases - 1;

	Phase** _newphases = (Phase**)malloc(_nphases* sizeof(*_phases[0]));

	int j = 0;

	for (int i = 0;i < _nphases;i++)
	{
		if (_phases[i]->PhaseType() == thephasetype)
		{
			delete _phases[i];
		}
		else
		{
			_newphases[j] = _phases[i];
			j++;
		}
	}
	_phases = (Phase**)realloc(_newphases, _nphases* sizeof(*_newphases[0]));
}

bool Stream::_phasepresent(PhaseTypeEnum thephasetype)
{
	for (int i = 0;i < _nphases;i++)
	{
		if (_phases[i]->PhaseType() == thephasetype)
		{
			return true;
		}
	}
}