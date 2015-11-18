#ifndef __PROPPACKBUILDER_H_INCLUDED__
#define __PROPPACKBUILDER_H_INCLUDED__

#include "PropPack.h"
#include "MolWtCalc.h"
#include "DensityCalc.h"
#include "RPMassDensityCalc.h"
#include "MassMolFlowCalc.h"
#include "RPEnergyCalc.h"
class PropPackBuilder
{
public:
	PropPackBuilder(){
		_current_proppack = 0;
	}

	~PropPackBuilder();
	virtual void BuildPackage()
	{
		_current_proppack = new PropPack;
	}
	virtual void SetFlashMethod(FlashMethodEnum theflashmethod)
	{

		_current_proppack->SetMethod(theflashmethod);

		//refprop still neeeds this
		MolWtCalc* newcalc = new MolWtCalc;
		_current_proppack->AddProperty(newcalc);

		if (theflashmethod == IDEAL)
		{
			DensityCalc* newcalc = new DensityCalc;
			_current_proppack->AddProperty(newcalc);
		}
		else if (theflashmethod == REFPROP)
		{
			RPMassDensityCalc* newcalc = new RPMassDensityCalc;
			_current_proppack->AddProperty(newcalc);

			RPEnergyCalc* newcalc1 = new RPEnergyCalc;
			_current_proppack->AddProperty(newcalc1);

			MassMolFlowCalc* newcalc2 = new MassMolFlowCalc;
			_current_proppack->AddProperty(newcalc2);
		}
	}
	virtual void AddComponent(string componentname){ _current_proppack->AddComponent(componentname); }
	virtual void AddPropertyCalc(string theproperty);
	virtual void EditPackage(PropPack* existingpackage){ _current_proppack = existingpackage; }

	virtual PropPack* GetPackage(){
		_current_proppack->Setup();

		return _current_proppack;
		_current_proppack = 0; //does this actually get executed?
	}
private:

	PropPack* _current_proppack;

};

#endif

/*template <class string, size_t N >
void Setup(FlashMethodEnum flashmethod, string const (&components)[N])
{
int ncomps;
ncomps =N;
std::string thecomp;

thePPBuilder->BuildPackage();

for (int i = 0; i < 3; i++)
{
thecomp = components[i];
if (thecomp.compare("none") != 0)
{
thePPBuilder->AddComponent(thecomp);
}

}

thePPBuilder->SetFlashMethod(flashmethod);


_default_package = thePPBuilder->GetPackage();

}*/