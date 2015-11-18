#include "stdafx.h"
#include "PropPack.h"
#include "Ideal.h"
#include "RefPropPack.h"
#include <fstream>
#include <sstream>
using namespace std;

PropPack::PropPack()
{
	_propertycalculation = new PropertyCalc;
	fwStream* _refstream = new fwStream;
}



void PropPack::AddComponent(string thecompname)
{
	//add component from D:\East101\Adri\devprojects\theSeed\Variables\Variables\ComponentDatabase.csv
	 Component* mycomp = new Component;
	string myline;
	string mystring;
	istringstream mystream;
	int err;
	int NComps, Nparams;
	int namesize;
	/*signed int namelen = thecompname.length() + 1;
	namelen = namelen*-1;*/
	long position;

	ifstream mycsv; //open for input
	//mycsv.open("ComponentDatabase.csv", ios::in);
	mycsv.open("D:/East101/Adri/devprojects/theSeed/Variables/Variables/ComponentDatabase.csv", ios::in);
	//mycsv.open("test.txt", ios::in);
	if (mycsv.is_open())
	{
		//get NComps and Nparams;
		getline(mycsv, mystring, ',');
		Nparams = atoi(mystring.c_str());
		getline(mycsv, mystring, ',');
		NComps = atoi(mystring.c_str());

		//skip params line
		getline(mycsv, myline);
		getline(mycsv, myline);

		//cout<< "\n";
		position = mystream.cur;
		while (getline(mycsv, myline))
		{
			//cout << "\n";
			mystream.str(myline); //turn the line string into a stream
			getline(mystream, mystring, ','); //get element (ID)
			getline(mystream, mystring, ',');//get element (Name)
		//	cout << mystring << "\n";
			if (mystring == thecompname)
			{	
				//start again at begining of stream
				mystream.seekg(0);
	
				getline(mystream, mystring, ',');
				mycomp->ID = atoi(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Name = mystring;

				getline(mystream, mystring, ',');
				mycomp->Mw = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Pc = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Tc = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->Acentric = atof(mystring.c_str());

				getline(mystream, mystring, ',');
				mycomp->StdIdealLiqDens = atof(mystring.c_str());

				mycsv.seekg(0,mycsv.end); //go to end to terminate while loop
			}
			position = mystream.cur;

		}
		mycsv.close();
	}


	_ncomps = _ncomps + 1; //update count
	Component* newcomps=new Component[_ncomps];


	for (int k = 0; k < _ncomps - 1; k++)
	{
		newcomps[k] = _components[k];
	}

	newcomps[_ncomps-1] = *mycomp;

	 _components = new Component[_ncomps];

	for (int k = 0; k < _ncomps ; k++)
	{
		_components[k] = newcomps[k];


	}

}


void  PropPack::AddProperty(PropertyCalc* thepropcalc)
{	
	thepropcalc->SetParent(this);
	_propertycalculation->AddProperty(thepropcalc);

}

void PropPack::SetMethod(FlashMethodEnum theFlashMethod)
{
	switch (theFlashMethod)
	{
	case IDEAL:
		_flashmethod = new Ideal;
		//if ideal then need to add propertycalcs
		

		break;
	case REFPROP:
		_flashmethod = new RefPropPack;
		break;
	}

}


PropPack::~PropPack()
{
}

