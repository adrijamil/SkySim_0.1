// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy): 7/9/15
// PURPOSE     :	This is a subclass of the FSObject. 
//					This object will contain Stream, UnitOp and FlowSheet
//					uses the composite pattern to recursively solve itself
// SPECIAL NOTES:	The idea is to treat Stream, UnitOp and FlowSheet in a similar fashion
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __FLOWSHEET_H_INCLUDED__
#define __FLOWSHEET_H_INCLUDED__

#include "Stream.h"
#include "Valve.h"
#include "Heater.h"
#include "Compressor.h"
#include "SolveStack.h"
#include "FSObject.h"

class FlowSheet :
	public FSObject
{
public:
	FlowSheet()
	{
		_nchildren = 0;
		_stack = new SolveStack;
		_stack->SetParent(this);
	};
	~FlowSheet();

	bool Solve();
	void SetPropPack(PropPack* thePP)
	{
		_default_package = thePP;
	}
	void Remove(){};//to be implemented
	int NComps(){ return _default_package->NComps(); };
	void AddStream(string strname)
	{
		
		for (int i = 0; i < _nchildren; i++)
		{
			if (_children[i]->Name() == strname)
			{
				cout << strname << " found \n";
				return;
			}
		}

		Stream* strm = new Stream(strname);
		if (!_default_package == 0)
		{
			strm->SetPropertyPackage(_default_package);
			Add(strm);
		}
		else
		{
			cout << "set package first";
		}
	

	}
	Stream* GetStream(string daname)
	{
		Stream* strmptr;
		strmptr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			if (_children[i]->Name() == daname)
			{
				strmptr = dynamic_cast<Stream *>(_children[i]);  //downcasting 
			}
		}

		return strmptr;
	}
	UnitOp* GetUnitOp(string daname)
	{
		UnitOp* UnitOpPtr;
		UnitOpPtr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			if (_children[i]->Name() == daname)
			{
				UnitOpPtr = dynamic_cast<UnitOp *>(_children[i]);  //downcasting 
			}
		}
		return UnitOpPtr;
	}
	void AddUnitOp(UnitOp* theop)
	{
		Add(theop);
	}

	void Output()
	{

		Stream* strmptr;
		Valve* vlvptr;
		Heater* heatptr;
		Compressor* compptr;

		strmptr = 0;
		for (int i = 0; i < _nchildren; i++)
		{
			_children[i]->Output();
			//FSobject should have the an output member function then by subclasses override.
			//strmptr = static_cast<Stream *>(_children[i]);  //downcasting to stream type. later if unit ops how?
			//if (strmptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
			//{
			//	strmptr->Output();
			//	continue;
			//}
			//vlvptr = dynamic_cast<Valve *>(_children[i]);
			//if (vlvptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
			//{
			//	vlvptr->Output();
			//	continue;
			//}
			//heatptr = dynamic_cast<Heater *>(_children[i]);
			//if (heatptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
			//{
			//	heatptr->Output();
			//	continue;
			//}
			//compptr = dynamic_cast<Compressor *>(_children[i]);
			//if (compptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
			//{
			//	compptr->Output();
			//	continue;
			//}

		}
	}

protected:
	FSObject** _children; //array of pointers to objects  
	int _nchildren;
	string _name;
	PropPack* _default_package;
	SolveStack* _stack; //decouple this guy from stack
	void Add(FSObject* thechild);
};

#endif
