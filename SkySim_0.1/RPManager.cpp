#include "stdafx.h"
#include "RPManager.h"

typedef void(__stdcall *fp_SETUPdllTYPE)(long *, char*, char*, char*, long *, char*, long, long, long, long);
fp_SETUPdllTYPE SETUPdll;

RPManager::RPManager()
{
	
	RefpropdllInstance = LoadLibrary("C:\\Program Files (x86)\\REFPROP\\REFPRP64.DLL");
	SETUPdll = (fp_SETUPdllTYPE)GetProcAddress(RefpropdllInstance, "SETUPdll");
}


RPManager::~RPManager()
{
}

bool RPManager::Setup(string fluids, long i)
{
	string fluidstring;
	int n_attempts = 0;
	long  ierr;
	char hf[refpropcharlength*ncmax + 20], hrf[lengthofreference + 1],
		herr[errormessagelength + 1], hfmix[refpropcharlength + 1];
	ierr = 0;
	/*fluidstring = "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\";
	fluidstring.append(fluids);*/

	strcpy_s(hf, fluids.c_str());
	strcpy_s(hfmix, "D:\\East101\\Adri\\devprojects\\theSeed\\RefProp\\fluids\\HMX.BNC");//make this relative reference

	strcpy_s(hrf, "DEF");
	strcpy_s(herr, "Ok");


	try {
		SETUPdll(&i, hf, hfmix, hrf, &ierr, herr,
			refpropcharlength*ncmax, refpropcharlength,
			lengthofreference, errormessagelength);
	}
	catch (...) {   // catch block will only be executed under /EHa

		cout << "Caught an exception in catch(...)." << endl;
		return false;
	}
}