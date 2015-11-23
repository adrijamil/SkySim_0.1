#pragma once
#include "StackObject.h"
#include "PropertyCalc.h"

//#include "Stream.h"
//StreamCalcs are stack object. they link PropertyCalc to individual streams (and their variables). For example, there is only one PropertyCalc MwCalc belonging to the PropPack. But an instances of streamcalc for MwCalc for each stream.
class Stream;

class StreamCalc :
	public StackObject
{
public:
	bool Solve();
	string Name();
	void SetPropertyCalc(PropertyCalc* thePC){ _propertycalc = thePC; }
	void SetRefStream(Stream* theRS){ _refstream = theRS; }
	void Setup(PropertyCalc* thePC, Stream* theRS);
	StreamCalc();
	~StreamCalc();
private:
	PropertyCalc* _propertycalc;
	Stream* _refstream;
};

