// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	Base class for other PropertyPackages such as Ideal and RefProp
//					Implements the strategy pattern for FlashMethod. can utilise this for other functions eg mixing rule
//					
//					
// TO BE IMPLEMENTED: 
// this class needs a factory.

// SPECIAL NOTES:	
// 1. Physical properties should be attached to property package I suppose.
// 2. Should include a setup method + issetup member. set the ncomps, define components etc.
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================




#ifndef __PROPPACK_H_INCLUDED__
#define __PROPPACK_H_INCLUDED__
#include "HandledException.h"
#include <iostream>
#include <string>
#include "FlashMethod.h"
#include "PropertyCalc.h"
#include "ErrorLogger.h"
#include "fwStream.h"

using namespace std;

class Stream;

//#define __STREAM_H_INCLUDED__ //this line tells the compiler that stream has already been defined
//#include "Stream.h"

struct Component
{
	string Name;
	int ID;
	double Mw;
	double Tc;
	double Pc;
	double Acentric;
	double StdIdealLiqDens;
};
//enum FlashTypeEnum { PT, PH, PQ,PS,TQ,TS,TH}; //7 types
enum FlashMethodEnum  {IDEAL,REFPROP};
enum ComponentNameEnum  { METHANE, ETHANE,BENZENE };
using namespace std;
//template<typename T = Stream>
class PropPack
{
	
public:
	 PropPack();
	~PropPack();
	PropertyCalc* Properties(){ return _propertycalculation; }
	FlashMethod* GetFlashMethod(){ return _flashmethod; }
	void SetMethod(FlashMethodEnum theFlashMethod);
	virtual bool Flash(FlashTypeEnum theflashtype)
	{
		bool retval = true;
		try
		{
			_flashmethod->Solve(theflashtype);
		}
		catch (HandledException& e)
		{
			//cout  << e.what() << '\n';
			ErrorLogger* logger=ErrorLogger::Instance();
			logger->Handle(e);
			retval = false;
		}
		
		return retval;
	}
	
	virtual void AddComponent(string thecompname);

	void SetName(string thename){ _name = thename; }
	int NComps(){ return _ncomps; }
	fwStream* RefStream() 
	{ 
		if (_refstream == 0)
		{
			_refstream = new fwStream;
		}
		return _refstream; 
	}
	Component GetComponent(int i){ return _components[i]; }
	void Setup()
	{
		bool SetupOk;
		SetupOk = _flashmethod->Setup(this);
		if (SetupOk == false)
		{
			Reload(REFPROP);//correct this, should rmb type
		}
	}
	void AddProperty(PropertyCalc* thepropcalc);
	void Reload(FlashMethodEnum theFlashMethod)
	{
		cout << "I'm reloading" << "\n";
		delete _flashmethod;
		SetMethod(theFlashMethod);
		Setup();
	}
protected:
	string _name;
	Component* _components; //make it fixed first
	int _ncomps;
	int _nprops;
	FlashMethod* _flashmethod;
	fwStream* _refstream;
	PropertyCalc* _propertycalculation; //
};



#endif
