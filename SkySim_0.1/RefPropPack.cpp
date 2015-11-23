#include "stdafx.h"
#include "RefPropPack.h"
//#include "RefPropFunctions.h" //if I put this line in the header file a linker error will happen
#include <exception>
#include <Windows.h>

// Then get pointers into the dll to the actual functions.
//ABFL1dll = (fp_ABFL1dllTYPE)GetProcAddress(RefpropdllInstance, "ABFL1dll");
//ABFL2dll = (fp_ABFL2dllTYPE)GetProcAddress(RefpropdllInstance, "ABFL2dll");
//ACTVYdll = (fp_ACTVYdllTYPE)GetProcAddress(RefpropdllInstance, "ACTVYdll");
//AGdll = (fp_AGdllTYPE)GetProcAddress(RefpropdllInstance, "AGdll");
//CCRITdll = (fp_CCRITdllTYPE)GetProcAddress(RefpropdllInstance, "CCRITdll");
//CP0dll = (fp_CP0dllTYPE)GetProcAddress(RefpropdllInstance, "CP0dll");
//CRITPdll = (fp_CRITPdllTYPE)GetProcAddress(RefpropdllInstance, "CRITPdll");
//CSATKdll = (fp_CSATKdllTYPE)GetProcAddress(RefpropdllInstance, "CSATKdll");
//CV2PKdll = (fp_CV2PKdllTYPE)GetProcAddress(RefpropdllInstance, "CV2PKdll");
//CVCPKdll = (fp_CVCPKdllTYPE)GetProcAddress(RefpropdllInstance, "CVCPKdll");
//CVCPdll = (fp_CVCPdllTYPE)GetProcAddress(RefpropdllInstance, "CVCPdll");
//DBDTdll = (fp_DBDTdllTYPE)GetProcAddress(RefpropdllInstance, "DBDTdll");
//DBFL1dll = (fp_DBFL1dllTYPE)GetProcAddress(RefpropdllInstance, "DBFL1dll");
//DBFL2dll = (fp_DBFL2dllTYPE)GetProcAddress(RefpropdllInstance, "DBFL2dll");
//DDDPdll = (fp_DDDPdllTYPE)GetProcAddress(RefpropdllInstance, "DDDPdll");
//DDDTdll = (fp_DDDTdllTYPE)GetProcAddress(RefpropdllInstance, "DDDTdll");
//DEFLSHdll = (fp_DEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DEFLSHdll");
//DHD1dll = (fp_DHD1dllTYPE)GetProcAddress(RefpropdllInstance, "DHD1dll");
//DHFLSHdll = (fp_DHFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DHFLSHdll");
//DIELECdll = (fp_DIELECdllTYPE)GetProcAddress(RefpropdllInstance, "DIELECdll");
//DOTFILLdll = (fp_DOTFILLdllTYPE)GetProcAddress(RefpropdllInstance, "DOTFILLdll");
//DPDD2dll = (fp_DPDD2dllTYPE)GetProcAddress(RefpropdllInstance, "DPDD2dll");
//DPDDKdll = (fp_DPDDKdllTYPE)GetProcAddress(RefpropdllInstance, "DPDDKdll");
//DPDDdll = (fp_DPDDdllTYPE)GetProcAddress(RefpropdllInstance, "DPDDdll");
//DPDTKdll = (fp_DPDTKdllTYPE)GetProcAddress(RefpropdllInstance, "DPDTKdll");
//DPDTdll = (fp_DPDTdllTYPE)GetProcAddress(RefpropdllInstance, "DPDTdll");
//DPTSATKdll = (fp_DPTSATKdllTYPE)GetProcAddress(RefpropdllInstance, "DPTSATKdll");
//DSFLSHdll = (fp_DSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "DSFLSHdll");
//ENTHALdll = (fp_ENTHALdllTYPE)GetProcAddress(RefpropdllInstance, "ENTHALdll");
//ENTROdll = (fp_ENTROdllTYPE)GetProcAddress(RefpropdllInstance, "ENTROdll");
//ESFLSHdll = (fp_ESFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "ESFLSHdll");
//FGCTYdll = (fp_FGCTYdllTYPE)GetProcAddress(RefpropdllInstance, "FGCTYdll");
//FPVdll = (fp_FPVdllTYPE)GetProcAddress(RefpropdllInstance, "FPVdll");
//GERG04dll = (fp_GERG04dllTYPE)GetProcAddress(RefpropdllInstance, "GERG04dll");
//GETFIJdll = (fp_GETFIJdllTYPE)GetProcAddress(RefpropdllInstance, "GETFIJdll");
//GETKTVdll = (fp_GETKTVdllTYPE)GetProcAddress(RefpropdllInstance, "GETKTVdll");
//GIBBSdll = (fp_GIBBSdllTYPE)GetProcAddress(RefpropdllInstance, "GIBBSdll");
//HSFLSHdll = (fp_HSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "HSFLSHdll");
//INFOdll = (fp_INFOdllTYPE)GetProcAddress(RefpropdllInstance, "INFOdll");
//LIMITKdll = (fp_LIMITKdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITKdll");
//LIMITSdll = (fp_LIMITSdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITSdll");
//LIMITXdll = (fp_LIMITXdllTYPE)GetProcAddress(RefpropdllInstance, "LIMITXdll");
//MELTPdll = (fp_MELTPdllTYPE)GetProcAddress(RefpropdllInstance, "MELTPdll");
//MELTTdll = (fp_MELTTdllTYPE)GetProcAddress(RefpropdllInstance, "MELTTdll");
//MLTH2Odll = (fp_MLTH2OdllTYPE)GetProcAddress(RefpropdllInstance, "MLTH2Odll");
//NAMEdll = (fp_NAMEdllTYPE)GetProcAddress(RefpropdllInstance, "NAMEdll");
//PDFL1dll = (fp_PDFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PDFL1dll");
//PDFLSHdll = (fp_PDFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PDFLSHdll");
//PEFLSHdll = (fp_PEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PEFLSHdll");
//PHFL1dll = (fp_PHFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PHFL1dll");
//PHFLSHdll = (fp_PHFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PHFLSHdll");
//PQFLSHdll = (fp_PQFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PQFLSHdll");
//PREOSdll = (fp_PREOSdllTYPE)GetProcAddress(RefpropdllInstance, "PREOSdll");
//PRESSdll = (fp_PRESSdllTYPE)GetProcAddress(RefpropdllInstance, "PRESSdll");
//PSFL1dll = (fp_PSFL1dllTYPE)GetProcAddress(RefpropdllInstance, "PSFL1dll");
//PSFLSHdll = (fp_PSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "PSFLSHdll");
//PUREFLDdll = (fp_PUREFLDdllTYPE)GetProcAddress(RefpropdllInstance, "PUREFLDdll");
//QMASSdll = (fp_QMASSdllTYPE)GetProcAddress(RefpropdllInstance, "QMASSdll");
//QMOLEdll = (fp_QMOLEdllTYPE)GetProcAddress(RefpropdllInstance, "QMOLEdll");
//SATDdll = (fp_SATDdllTYPE)GetProcAddress(RefpropdllInstance, "SATDdll");
//SATEdll = (fp_SATEdllTYPE)GetProcAddress(RefpropdllInstance, "SATEdll");
//SATHdll = (fp_SATHdllTYPE)GetProcAddress(RefpropdllInstance, "SATHdll");
//SATPdll = (fp_SATPdllTYPE)GetProcAddress(RefpropdllInstance, "SATPdll");
//SATSdll = (fp_SATSdllTYPE)GetProcAddress(RefpropdllInstance, "SATSdll");
//SATTdll = (fp_SATTdllTYPE)GetProcAddress(RefpropdllInstance, "SATTdll");
//SETAGAdll = (fp_SETAGAdllTYPE)GetProcAddress(RefpropdllInstance, "SETAGAdll");
//SETKTVdll = (fp_SETKTVdllTYPE)GetProcAddress(RefpropdllInstance, "SETKTVdll");
//SETMIXdll = (fp_SETMIXdllTYPE)GetProcAddress(RefpropdllInstance, "SETMIXdll");
//SETMODdll = (fp_SETMODdllTYPE)GetProcAddress(RefpropdllInstance, "SETMODdll");
//SETREFdll = (fp_SETREFdllTYPE)GetProcAddress(RefpropdllInstance, "SETREFdll");
//SETUPdll = (fp_SETUPdllTYPE)GetProcAddress(RefpropdllInstance, "SETUPdll");
//SPECGRdll = (fp_SPECGRdllTYPE)GetProcAddress(RefpropdllInstance, "SPECGRdll");
//SUBLPdll = (fp_SUBLPdllTYPE)GetProcAddress(RefpropdllInstance, "SUBLPdll");
//SUBLTdll = (fp_SUBLTdllTYPE)GetProcAddress(RefpropdllInstance, "SUBLTdll");
//SURFTdll = (fp_SURFTdllTYPE)GetProcAddress(RefpropdllInstance, "SURFTdll");
//SURTENdll = (fp_SURTENdllTYPE)GetProcAddress(RefpropdllInstance, "SURTENdll");
//TDFLSHdll = (fp_TDFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TDFLSHdll");
//TEFLSHdll = (fp_TEFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TEFLSHdll");
//THERM0dll = (fp_THERM0dllTYPE)GetProcAddress(RefpropdllInstance, "THERM0dll");
//THERM2dll = (fp_THERM2dllTYPE)GetProcAddress(RefpropdllInstance, "THERM2dll");
//THERM3dll = (fp_THERM3dllTYPE)GetProcAddress(RefpropdllInstance, "THERM3dll");
//THERMdll = (fp_THERMdllTYPE)GetProcAddress(RefpropdllInstance, "THERMdll");
//THFLSHdll = (fp_THFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "THFLSHdll");
//TPFLSHdll = (fp_TPFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TPFLSHdll");
//TPRHOdll = (fp_TPRHOdllTYPE)GetProcAddress(RefpropdllInstance, "TPRHOdll");

//TRNPRPdll = (fp_TRNPRPdllTYPE)GetProcAddress(RefpropdllInstance, "TRNPRPdll");
//TSFLSHdll = (fp_TSFLSHdllTYPE)GetProcAddress(RefpropdllInstance, "TSFLSHdll");
//VIRBdll = (fp_VIRBdllTYPE)GetProcAddress(RefpropdllInstance, "VIRBdll");
//VIRCdll = (fp_VIRCdllTYPE)GetProcAddress(RefpropdllInstance, "VIRCdll");
//WMOLdll = (fp_WMOLdllTYPE)GetProcAddress(RefpropdllInstance, "WMOLdll");
//XMASSdll = (fp_XMASSdllTYPE)GetProcAddress(RefpropdllInstance, "XMASSdll");
//XMOLEdll = (fp_XMOLEdllTYPE)GetProcAddress(RefpropdllInstance, "XMOLEdll");

typedef void(__stdcall *fp_TPFLSHdllTYPE)(double &, double &, double *, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, double &, long &, char*, long);
typedef void(__stdcall *fp_TQFLSHdllTYPE)(double &, double &, double *, long &, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);\
typedef void(__stdcall *fp_PQFLSHdllTYPE)(double &, double &, double *, long &, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);

typedef void(__stdcall *fp_PSFLSHdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);
typedef void(__stdcall *fp_THFLSHdllTYPE)(double &, double &, double *, long &, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);
typedef void(__stdcall *fp_PHFLSHdllTYPE)(double &, double &, double *, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);
typedef void(__stdcall *fp_TSFLSHdllTYPE)(double &, double &, double *, long &, double &, double &, double &, double &, double *, double *, double &, double &, double &, double &, double &, double &, long &, char*, long);



fp_TPFLSHdllTYPE TPFLSHdll;
fp_TQFLSHdllTYPE TQFLSHdll;
fp_PQFLSHdllTYPE PQFLSHdll;
fp_PSFLSHdllTYPE PSFLSHdll;

fp_TSFLSHdllTYPE TSFLSHdll;
fp_THFLSHdllTYPE THFLSHdll;
fp_PHFLSHdllTYPE PHFLSHdll;


RefPropPack::RefPropPack()
{
	_fluids_path = "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\";
	//define functions to pointer
	TPFLSHdll = (fp_TPFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "TPFLSHdll");
	TQFLSHdll = (fp_TQFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "TQFLSHdll");
	PSFLSHdll = (fp_PSFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "PSFLSHdll");

	TSFLSHdll = (fp_TSFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "TSFLSHdll");
	THFLSHdll = (fp_THFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "THFLSHdll");
	PHFLSHdll = (fp_PHFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "PHFLSHdll");
	PQFLSHdll = (fp_PQFLSHdllTYPE)GetProcAddress(RPManager::Instance()->hInstance(), "PQFLSHdll");

}

bool RefPropPack::Setup(PropPack* thePP)
{
	long i;
	i = thePP->NComps();

	string fluidstring;

	fluidstring = "";
	for (int k = 0; k < i; k++)
	{
		if (k > 0)
		{
			fluidstring = fluidstring + "|";
		}
		fluidstring = fluidstring+_fluids_path;
		fluidstring = fluidstring+ thePP->GetComponent(k).Name+".FLD";
	}


	bool issetup;

	issetup = RPManager::Instance()->Setup(fluidstring, i);

	_proppack = thePP;
	return issetup;  //why so can try again if it fails
}



RefPropPack::~RefPropPack()
{


}


void regphases(fwStream* thefw, bool vappresent, bool hcliqpresent, bool aqpresent)
{
	thefw->Phases[1].IsPresent=vappresent;
	thefw->Phases[2].IsPresent = hcliqpresent;
	thefw->Phases[3].IsPresent = aqpresent;
}


void RefPropPack::Solve(FlashTypeEnum theflashtype)
{
	long  ierr,kq;
	char 	herr[errormessagelength + 1];
	double t, p, d, dl, dv, q, e, h, s, cv, cp, w;
	double x[ncmax], xliq[ncmax], xvap[ncmax];
	long kr;
	kr = 1;
	double sum = 0;

	//kr--flag specifying desired root for multi - valued inputs :
	//1 = return lower density root
	//2 = return higher density root
	//to be investigated

	

	int ncomps;
	ncomps = _proppack->NComps();
	kq = 1;//1 means molar phase fraction, 2 is mass

	//extract  compositions
	for (int k = 0; k < ncomps; k++)
	{
		x[k] = _proppack->RefStream()->Phases[0].Composition[k]; //getvalues doesnt work?
		cout << x[k] << "\n";
	}


	//for (int k = 0; k < ncomps-1; k++)
	//{
	//	x[k] = roundf(x[k] * 100000) / 100000;; //getvalues doesnt work?
	//	sum = sum + x[k];
	//	cout << x[k] << "\n";
	//}
	//x[ncomps - 1] = 1 - sum;
	fwStream* fw = _proppack->RefStream();
	t = fw->Temperature;
	p = fw->Pressure;
	h = fw->Phases[0].Enthalpy;
	q = fw->VapourFraction;
	s = fw->Phases[0].Entropy;
	ierr = 0;

	if (theflashtype == PT)
	{
		TPFLSHdll(t, p, x, d, dl, dv, xliq, xvap, q, e, h, s, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype==PH)
	{
		PHFLSHdll(p, h, x,t, d, dl, dv, xliq, xvap, q, e, s, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype == PQ)
	{
		PQFLSHdll( p,q, x,kq,t,d, dl, dv, xliq, xvap, e, h, s, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype == PS)
	{
		PSFLSHdll( p,s, x,t, d, dl, dv, xliq, xvap, q, e, h, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype == TQ)
	{
		TQFLSHdll(t, q, x, kq, p, d, dl, dv, xliq, xvap, e, h, s, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype == TS)
	{
		TSFLSHdll(t,s, x,kr,p, d, dl, dv, xliq, xvap, q, e, h, cv, cp, w, ierr, herr, errormessagelength);
	}
	else if (theflashtype == TH)
	{
		THFLSHdll(t, h, x,kr,p, d, dl, dv, xliq, xvap, q, e,  s, cv, cp, w, ierr, herr, errormessagelength);
		//can try figure out which root im looking for. 
	}

	if (!ierr == 0)
	{
		string str(herr);
		throw HandledException(str);
	}

	//check q
	//c        q--vapor quality on a MOLAR basis[moles vapor / total moles]
	//	c           q < 0 indicates subcooled(compressed) liquid
	//	c           q = 0 indicates saturated liquid
	//	c           q = 1 indicates saturated vapor
	//	c           q > 1 indicates superheated vapor
	//	c           q = -998 subcooled liquid, but quality not defined(p > Pc)
	//	c           q = 999 indicates supercritical state(t > Tc) and (p > Pc)
	
	
	//water is always not present using this proppack
	fw->Phases[3].IsPresent = false;
	if (q > 0 && q < 1)
	{
		regphases(fw, true, true, false);
	}
	else if (q < 0) //subcool
	{
		regphases(fw, false, true, false);
		q = 0;
	}
	else if (q == 0) //sat liq
	{
		regphases(fw, true, true, false);
	}
	else if (q>1) //superheat
	{
		regphases(fw, true, false, false);
		q = 1;
	}
	else if (q==1) //sat vap
	{
		regphases(fw, true, true, false);
	}
	else if (q==-998) //sub liq (say its liq)
	{
		regphases(fw, false, true, false);
		q = 0;

	}
	else if (q == 999) //supercritical (say its vapour)
	{
		regphases(fw, true, false, false);
		q = 1;
	}
	

	fw->Temperature=t;
	fw->Pressure=p;
	fw->Phases[0].Enthalpy = h;
	fw->VapourFraction=q;
	fw->Phases[0].Entropy = s;

	double* xtemp = new double[ncomps];
	double* ytemp = new double[ncomps];
	
	for (int k = 0; k < ncomps; k++)
	{
		xtemp[k] = xliq[k];
		ytemp[k] = xvap[k];
		cout << xvap[k] << "\n";
	}



	fw->Phases[0].MolarDensity = (d / 0.001);
	
	for (int j = 1;j < 3;j++)
	{
		if (fw->Phases[j].IsPresent)
		{
			if (j ==1)
			{
				fw->Phases[j].PhaseFraction = q;
				fw->Phases[j].Composition = ytemp;
				fw->Phases[j].MolarDensity = (dv / 0.001);
			}
			else if (j==2)
			{
				fw->Phases[j].PhaseFraction = 1-q;
				fw->Phases[j].Composition = xtemp;
				fw->Phases[j].MolarDensity = (dl / 0.001);
			}
			
		}
	}
	
}