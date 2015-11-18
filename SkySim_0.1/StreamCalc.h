#pragma once
#include "StackObject.h"
#include "PropertyCalc.h"
//#include "Stream.h"
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

