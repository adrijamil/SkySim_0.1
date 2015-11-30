#include "Tester.h"



Tester::Tester()
{
	
}


Tester::~Tester()
{
	
}


void Tester::AddTestFiles(std::string mytestlist)
{
	UnitOpTest* mytest = new UnitOpTest();

	std::string mystring;
	std::string myjsonactual, myjsonexpected;
	std::fstream myfile;
	std::string objname;
	bool endofjson = false;
	bool retval = true;
	bool testdefined = false;

		myfile.open(mytestlist);
		do
		{
			mytest = new UnitOpTest();

			getline(myfile, mystring);
			if (mystring == "DONE")
			{
				break;
			}
			mytest->Name = mystring;

			getline(myfile, mystring);
			mytest->Description = mystring;

			getline(myfile, mystring);
			mytest->Inputfile = mystring;

			getline(myfile, mystring);
			mytest->Outputfile = mystring;

			getline(myfile, mystring);//this will be mystring== ""

			mytest->Passed = false;
			mytests.push_back(*mytest);

		}while (myfile.good());

		myfile.close();
}

bool Tester::TestAll()
{
	std::string failedtests;
	std::string myoutputstring;
	std::string myjsonactual,myjsonexpected;
	std::fstream myfile;
	std::string objname;
	bool endofjson=false;
	bool retval = true;
	bool thistestok = false;

	bool isdone;
	isdone = false;
	//std::stringstream  mypartstream;
	
	cout << mytests.size() << " \n";
	for (int i = 0;i < mytests.size();i++)
	{
		cout <<"running test"<<mytests[i].Name <<": " <<mytests[i].Description<<" \n";
		cout << mytests[i].Inputfile << " \n";
		mycmd = new CommandInterpreter(mytests[i].Inputfile);
		
		myfile.open(mytests[i].Outputfile);
		do
		{
			getline(myfile, myoutputstring);
			if (myoutputstring == "STREAM")
			{
				getline(myfile, objname);
				myjsonactual = mycmd->GetStreamJSON(objname);
			}
			else if(myoutputstring=="DONE") //must be a unit op
			{
				break;
			}
			else //must be a unit op
			{
				getline(myfile, objname);

				myjsonactual = mycmd->GetUnitOpJSON(objname);
			}

			endofjson = false;
			myjsonexpected = "";
			do
			{
				getline(myfile, myoutputstring);
				
				if (myoutputstring != "")
				{
					myjsonexpected.append(myoutputstring);
				}
				else
				{
					endofjson = true;
				}

			} while (endofjson == false);


			myjsonexpected.erase(std::remove(myjsonexpected.begin(), myjsonexpected.end(), ' '), myjsonexpected.end());
			myjsonexpected.erase(std::remove(myjsonexpected.begin(), myjsonexpected.end(), '\n'), myjsonexpected.end());
			myjsonactual.erase(std::remove(myjsonactual.begin(), myjsonactual.end(), ' '), myjsonactual.end());
			myjsonactual.erase(std::remove(myjsonactual.begin(), myjsonactual.end(), '\n'), myjsonactual.end());

		/*	cout << "myjsonactual \n";
			cout << myjsonactual;
			cout << "myjsonexpected \n";
			cout << myjsonexpected;*/

			if (myjsonactual != myjsonexpected)
			{
				thistestok = false;
				retval = false;
				cout << objname << " tested, failed \n";
			}
			else
			{
				thistestok = true;
				cout << objname << " tested, passed \n";
			}

		}while( myfile.good());
		myfile.close();

		if (thistestok)
		{

			cout << mytests[i].Name << ": " << mytests[i].Description << " passed \n";
			
		}
		else
		{
			cout << mytests[i].Name << ": " << mytests[i].Description << " failed \n";
			failedtests.append(mytests[i].Name);
			failedtests.append(", ");
		}
		thistestok = false;
		delete mycmd;
	}
	
	if (retval)
	{
		cout << name << " passed all tests \n";
	}
	else
	{
		cout << name << " failed. failed tests are:"<<failedtests<<"\n";
		
	}
		return retval;
}




