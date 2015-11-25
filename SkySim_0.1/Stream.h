// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	2/9/15
// PURPOSE     :	This a derived class of fluid.
//					Also Streams will have members of phases 
//					Should not need a name as it will not exist alone (or at all as a fluid object except in the implementation of subclasses)
//					Normalise method is included for testing. May not actually
//					On creation certain variables such as temperature and pressure will be pointing to the same block of memory (memory here refers to the double, not RealVariable object)
//					
// TO BE IMPLEMENTED: 
// 1. Copy/clone function
// 2. Attach a thermo package
// 3. Deal with phases that are not there

// SPECIAL NOTES:
// 1. Static initialisation of Phases to 3 phases. Phases then need to know whether they exist or not. \
//    Alternatively we can use a dynamic array of phases and take phase in and out. this seems slicker but is it?

// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================
#ifndef __STREAM_H_INCLUDED__
#define __STREAM_H_INCLUDED__

#include <vector>

#include "Fluid.h"//actually Phase.h already declared this. just keep it its guarded anyway
#include "Phase.h"
#include "FSObject.h"
#include "PropPack.h"
#include "StackObject.h"
#include "StreamCalc.h"

class StreamCalc;
//class Phase;  //this way we avoid recursion in header files;

class Stream :
	public Fluid, public FSObject, public StackObject
	
{
	friend class fwStream;
public:
	Stream();
	Stream(string daname);
	int NPhases() { return _nphases; };

	RealVariable* VapourFraction()
	{ 
		return _vapourfraction;
	};
	string Name()
	{ 
		string retstr = _name;
			return retstr;
	}
	string StackName()
	{
		string retstr = _name;
		retstr.append(":Flash");
		return retstr;
	}
	~Stream();

	Phase* Phases(int i)
	{
	//	cout<<	_phases.size()<<"\n";
		return _phases[i];
		
	}
	Phase* Phases(PhaseTypeEnum thephasetype)
	{
		for (std::vector<Phase*>::iterator it = _phases.begin(); it != _phases.end(); ++it) {
			if (it[0]->PhaseType() == thephasetype)
			{
				return it[0];
			}
		}
		//if you reach here then there's no phase. fwStream will command the stream to add a phase (if needed)
		return NULL;
	}
	
	void SetPropertyPackage(PropPack* thePP);
	
	int NComps(){ return _proppack->NComps(); }
	bool Solve();
	bool IsSolved(){ return _issolved; }
	void Output();
	PropPack* GetPropertyPackage()
	{
		return _proppack;
	}
	StackObject* GetStackObject(int i);
	int NStackObjects();
	
private:
	void _addphase(PhaseTypeEnum thephasetype);
	void _removephase(PhaseTypeEnum thephasetype);
	bool _phasepresent(PhaseTypeEnum thephasetype);
	RealVariable* _vapourfraction;
	std::vector <Phase*> _phases;
	PropPack* _proppack;
	bool _issolved;
	StreamCalc* _streamcalcs;
	int _nstreamcalcs=0;
	void _setstreamcalcs();
	int _nphases = 0;
	void _initialise();

};
#endif
