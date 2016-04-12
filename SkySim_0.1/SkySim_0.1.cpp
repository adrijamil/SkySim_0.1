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
#include "CompressorTester.h"
using namespace std;

ErrorLogger *ErrorLogger::s_instance = 0;
RPManager* RPManager::_instance = 0;
OutputLogger *OutputLogger::_instance = 0;

void runtests()
{
	std::string outputstr;
	bool isworking = false;


	//MixerTester mytester;
	//outputstr.append(mytester.name);
	//outputstr.append(": ");
	////HeaterTester mytester;
	//isworking = false;
	//isworking = mytester.TestAll();
	//if (isworking)
	//{
	//	outputstr.append("pass \n");
	//}
	//else
	//{
	//	outputstr.append("fail \n");
	//}

	//HeaterTester mytester2;
	//outputstr.append(mytester2.name);
	//outputstr.append(": ");
	// isworking = false;
	//isworking = mytester2.TestAll();
	//if (isworking)
	//{
	//	outputstr.append("pass \n");
	//}
	//else
	//{
	//	outputstr.append("fail \n");
	//}


	//ValveTester mytester3;
	//outputstr.append(mytester3.name);
	//outputstr.append(": ");
	//isworking = false;
	//isworking = mytester3.TestAll();
	//if (isworking)
	//{
	//	outputstr.append("pass \n");
	//}
	//else
	//{
	//	outputstr.append("fail \n");
	//}

	//SplitterTester mytester4;
	//outputstr.append(mytester4.name);
	//outputstr.append(": ");
	//isworking = false;
	//isworking = mytester4.TestAll();
	//if (isworking)
	//{
	//	outputstr.append("pass \n");
	//}
	//else
	//{
	//	outputstr.append("fail \n");
	//}

	CompressorTester mytester5;
	outputstr.append(mytester5.name);
	outputstr.append(": ");
	isworking = false;
	isworking = mytester5.TestAll();
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
	OpLogger->Name("CompressorTests//CompressorTestInput_1.txt");
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
		CommandInterpreter mycase("testheatexchanger.txt");
		//CommandInterpreter mycase("CompressorTests//CompressorTestInput_4.txt");
		//mycase.tempDoMore();
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


	CommandInterpreter mycase;
	//mycase.SendCommand("testcompressor.txt");
	
	/*mycase.SendCommand("SETUP REFPROP METHANE,ETHANE,HEXANE");

	mycase.SendCommand("ADDSTREAM STRM1 PRESSURE 5000 TEMPERATURE 330 COMPOSITION 0.3,0.4,0.3");

	mycase.SendCommand("SPECIFYVARIABLE STREAM STRM1 MASSFLOW 3162");

	mycase.SendCommand("ADDSTREAM STRM2");

	mycase.SendCommand("ADDUNITOP VALVE V1 K 100");
	
	mycase.SendCommand("CONNECT V1 INLET STRM1");
	
	mycase.SendCommand("CONNECT V1 OUTLET STRM2");
	
	mycase.SendCommand("SOLVE");*/

	//string myoutput;
	//myoutput = mycase.GetStreamJSON("STRM1");
	
	//cout << myoutput;

	cout << "Exiting. Press enter.";
	getchar();

	return 0;
}



