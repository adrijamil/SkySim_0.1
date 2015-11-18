// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	7/9/15
// PURPOSE     :	This is a subclass of FlashMethod (referring to Ideal/RefProp/PengRob
//					used to apply strategy pattern to the PropPack class
//					PropPack class keeps a reference to this object to do flash calcs
// ===============================
// TO BE IMPLEMENTED: 
// 1. To keep relevant pure component data (Tc, Pc) on board so don't have too keep reaching into PropPack. Do this on the base class
// ===============================
// SPECIAL NOTES:	
// 1. 
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#ifndef __IDEAL_H_INCLUDED__
#define __IDEAL_H_INCLUDED__

#include "FlashMethod.h"
#include "Stream.h"

using namespace std;

class Ideal :
	public FlashMethod
{
public:
	Ideal(){ _name = "ideal"; };
	~Ideal();
	void Flash(fwStream* theStream, PropPack* thePP, FlashTypeEnum theflashtype);
	//need a reference to PropPack to get NComp and possibly other shit
	void PT_Flash(Stream* theStream, PropPack* thePP);
	void TQ_Flash(Stream* theStream, PropPack* thePP);
	bool Setup(PropPack* thePP);
	//{
	//	cout << "im flashing" <<thestream->Name() << "overrided by"<<_name;
	//};// i need P, T and x. Output H, vf and a bunch of props.
private:
	double* _Ki;
	double _RR(double vfrac,double* comps, int NComp);
	double _solveRR(double* comps, int NComp);
	void _calcKis(double p, double t);
};

#endif
