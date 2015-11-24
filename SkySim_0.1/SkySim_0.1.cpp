// ===============================
// AUTHOR     :		Adri
// CREATED(d/m/yy):	17/11/15
// PURPOSE     :	This will be the only cpp file with a boilerplate. This implementation is only used for debugging.
// SPECIAL NOTES:	HYSYS uses RealFlexVariable for arrays. Why this is (aside from convenience) remains to be seen.
// ===============================
// Change History: - put name, date and description of change
// 1. Created
//==================================

#include "RPManager.h"

#include "CommandInterpreter.h"
#include "FSObject.h"
#include "FlowSheet.h"
#include "ErrorLogger.h"
#include "OutputLogger.h"



using namespace std;

ErrorLogger *ErrorLogger::s_instance = 0;
RPManager* RPManager::_instance = 0;

OutputLogger *OutputLogger::_instance = 0;


int main()
{
	ErrorLogger* glogger = ErrorLogger::Instance();
	OutputLogger* OpLogger = OutputLogger::Instance();
	OpLogger->Name("testvalveout.txt");
	CommandInterpreter mycase("testphases.txt");

	//CommandInterpreter mycase("myinputfile.txt");
	//CommandInterpreter mycase;
	string mycommand;
	mycommand = "";
	bool isexit = false;
	//mycase.

	mycase.tempDoMore();

	//cout << mycase.GetUnitOpJSON("E1");

	while (!isexit)
	{
		cin >> mycommand;
		if (mycommand == "EXIT")
		{
			isexit = true;
		}
		else
		{
			mycase.SendCommand(mycommand);
		}
	}

	cout << "Exiting. Press enter.";
	getchar();

	return 0;
}

