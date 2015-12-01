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
#include "SplitterTester.h"
using namespace std;

ErrorLogger *ErrorLogger::s_instance = 0;
RPManager* RPManager::_instance = 0;

OutputLogger *OutputLogger::_instance = 0;


void runtests()
{
	std::string outputstr;
	bool isworking = false;
	MixerTester mytester;
	outputstr.append(mytester.name);
	outputstr.append(": ");
	//HeaterTester mytester;
	isworking = false;
	isworking = mytester.TestAll();
	if (isworking)
	{
		outputstr.append("pass \n");
	}
	else
	{
		outputstr.append("fail \n");
	}

	HeaterTester mytester2;
	outputstr.append(mytester2.name);
	outputstr.append(": ");
	 isworking = false;
	isworking = mytester2.TestAll();
	if (isworking)
	{
		outputstr.append("pass \n");
	}
	else
	{
		outputstr.append("fail \n");
	}


	ValveTester mytester3;
	outputstr.append(mytester3.name);
	outputstr.append(": ");
	isworking = false;
	isworking = mytester3.TestAll();
	if (isworking)
	{
		outputstr.append("pass \n");
	}
	else
	{
		outputstr.append("fail \n");
	}

	SplitterTester mytester4;
	outputstr.append(mytester4.name);
	outputstr.append(": ");
	isworking = false;
	isworking = mytester4.TestAll();
	if (isworking)
	{
		outputstr.append("pass \n");
	}
	else
	{
		outputstr.append("fail \n");
	}

	std::cout << outputstr;
}

void generateoutputfile(CommandInterpreter* thecmd)
{
	OutputLogger* OpLogger = OutputLogger::Instance();
	OpLogger->Name("SplitterTests//SplitterTestOutput_5.txt");
	OpLogger->Output("STREAM");
	OpLogger->Output("STRM1");
	std::string jsonstring = thecmd->GetStreamJSON("STRM1");
	OpLogger->Output(jsonstring);

	OpLogger->Output("STREAM");
	OpLogger->Output("STRM2");
	jsonstring = thecmd->GetStreamJSON("STRM2");
	OpLogger->Output(jsonstring);

	OpLogger->Output("SPLITTER");
	OpLogger->Output("S1");
	jsonstring = thecmd->GetUnitOpJSON("S1");
	OpLogger->Output(jsonstring);

	OpLogger->Output("DONE");
}

int main()
{
	ErrorLogger* glogger = ErrorLogger::Instance();
	OutputLogger* OpLogger = OutputLogger::Instance();
	//OpLogger->Name("testvalveout.txt");
	
	
	//runtests();
	string mycommand;
	mycommand = "";
	bool isexit = false;


	
	bool istesting = false;
	if (istesting)
	{
		runtests();
	}
	else
	{

		CommandInterpreter mycase("testDemoCase.txt");
		mycase.tempDoMore();
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
		//generateoutputfile(&mycase);
	}


	
	
	cout << "Exiting. Press enter.";
	getchar();

	return 0;
}



