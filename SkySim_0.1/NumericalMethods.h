#pragma once

class NumericalMethods
{
	

public:

	typedef double(*FUNC_PTR)(double x);
	NumericalMethods();
	double  Brent(FUNC_PTR theF, double ain, double bin){}; //fx has to obtain inputs (eg x,y,p,t) internally.
	void RegFx();
	~NumericalMethods();
private:
	FUNC_PTR _myfx = 0;

};

