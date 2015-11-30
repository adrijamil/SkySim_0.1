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
#include "ValveTester.h"
#include "HeaterTester.h"
#include "MixerTester.h"

using namespace std;

ErrorLogger *ErrorLogger::s_instance = 0;
RPManager* RPManager::_instance = 0;

OutputLogger *OutputLogger::_instance = 0;


void runtests()
{
	MixerTester mytester;

	bool isworking = false;
	isworking = mytester.TestAll();

}

void generateoutputfile(CommandInterpreter* thecmd)
{
	OutputLogger* OpLogger = OutputLogger::Instance();
	OpLogger->Name("MixerTests//MixerTestOutput_3.txt");
	OpLogger->Output("STREAM");
	OpLogger->Output("STRM1");
	std::string jsonstring = thecmd->GetStreamJSON("STRM1");
	OpLogger->Output(jsonstring);

	OpLogger->Output("STREAM");
	OpLogger->Output("STRM2");
	jsonstring = thecmd->GetStreamJSON("STRM2");
	OpLogger->Output(jsonstring);

	OpLogger->Output("MIXER");
	OpLogger->Output("M1");
	jsonstring = thecmd->GetUnitOpJSON("M1");
	OpLogger->Output(jsonstring);

	OpLogger->Output("DONE");
}

int main()
{
	ErrorLogger* glogger = ErrorLogger::Instance();
	OutputLogger* OpLogger = OutputLogger::Instance();
	//OpLogger->Name("testvalveout.txt");
	
	
	runtests();
	string mycommand;
	mycommand = "";
	bool isexit = false;
	//mycase.

	//mycase.tempDoMore();
	
//CommandInterpreter mycase("MixerTests//MixerTestInput_3.txt");
//
//generateoutputfile(&mycase);
	

	while (!isexit)
	{
		cin >> mycommand;
		if (mycommand == "EXIT")
		{
			isexit = true;
		}
		else
		{
			//mycase.SendCommand(mycommand);
		}
	}
	
	cout << "Exiting. Press enter.";
	getchar();

	return 0;
}



