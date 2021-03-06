#include "stdafx.h"
#include "CommandInterpreter.h"

using namespace std;

CommandInterpreter::CommandInterpreter(string theinputfile)
{

	_initfrominput(theinputfile);
	//rapidxml serial;
	
	/*OutputLogger* oplgr=OutputLogger::Instance();

	oplgr->Output("adfdfdsfa");*/

}
CommandInterpreter::CommandInterpreter()
{ 
	//CaseSetup("","");

}


CommandInterpreter::~CommandInterpreter()
{


}

void CommandInterpreter::altSendCommand(string thecommand)
{
	bool lastline = true;
	string filename = thecommand;

	string allcommands;

	fstream myfile;
	
	cout << thecommand.substr(thecommand.find_last_of(".")+1);

	if (thecommand.substr(thecommand.find_last_of(".") + 1) == "txt")
	{
	
		filename = thecommand;

		myfile.open(filename);
	readcommandfile:
		getline(myfile, thecommand);
		if (myfile.good())
		{
			lastline = false;
		}
		else
		{
			lastline = true;
		}
	}
	/*
	I need the following commands


	1.	SETUP REFPROP Comp1,comp2,comp3
	2.	ADDSTREAM STRM1 PRESSURE 2000 TEMPERATURE 3000 COMPOSITION 0.3,0.4,0.4
		ADDSTREAM STRM1
	3.	ADDUNITOP VALVE V1 INLET STRM1 OUTLET STRM2 K 1000
	4.	SPECVARIABLE STRM1 PRESSURE 4000
	5.	SOLVE
	5.	INPUTFILE THEFILENAME
	6.	CONNECT STRM1 INLET V1
	7. 


	*/

	vector<string> strs;
	boost::split(strs, thecommand, boost::is_any_of(" "));
	std::string specs;

	/*cout << "* size of the vector: " << strs.size() << endl;
	for (vector<string>::iterator it2 = strs.begin(); it2 != strs.end(); ++it2)
	{
		cout << *it2 << endl;
	}*/

	if (strs[0]=="SETUP")
	{
		CaseSetup(strs[1], strs[2].append(",DONE"));
	}
	else if (strs[0] == "ADDSTREAM")
	{
		vector<string>::iterator it = strs.begin();
		it ++;
		it++;
		for (it; it != strs.end();++it)
		{
			specs.append(*it);
			specs.append(" ");
			++it;
			specs.append(*it);
			specs.append("\n");
			cout << specs;
		}
		specs.append("DONE");
		cout << specs;
		StreamSetup(strs[1], specs);
	}

	else if (strs[0] == "ADDUNITOP")
	{
		
		
		vector<string>::iterator it = strs.begin();
		it++;
		it++;
		it++;
		specs.append("NONE\nNONE\n");
		for (it; it != strs.end();++it)
		{
			specs.append(*it);
			specs.append(" ");
			++it;
			specs.append(*it);
			specs.append("\n");
			cout << specs;
		}
		specs.append("DONE");
		cout << specs;
		UnitOpSetup(strs[1],strs[2], specs);
	}
	else if (strs[0] == "CONNECT")
	{

		ConnectionType contype;
		if (strs[2] == "INLET")
		{
			contype = INLET;
		}
		else if (strs[2] == "OUTLET")
		{
			contype = OUTLET;
		}
		else if (strs[2]=="VAPOUROUTLET")
		{
			contype = VAPOUROUTLET;
		}
		else if (strs[2] == "LIQUIDOUTLET")
		{
			contype = LIQUIDOUTLET;
		}
		_activecase->GetUnitOp(strs[1])->Connect(_activecase->GetStream(strs[3]),contype);
		
	}

	else if (strs[0] == "SOLVE")
	{
		_activecase->Solve();
		_activecase->Output();


	}

	else if (strs[0] == "SPECIFYVARIABLE")
	{
		string specs;
		specs.append(strs[3]);
		specs.append(" ");
		specs.append(strs[4]);
		specs.append("\nDONE");
		if (strs[1] == "STREAM")
		{
			

			StreamSetup(strs[2], specs);
		}
		else
		{
			UnitOpSetup(strs[1], strs[2], specs);
		}


	}
	if (!lastline)
	{
		goto readcommandfile;
	}
}



void CommandInterpreter::SendCommand(string thecommand)
{


	if (thecommand == "TEST")
	{
		cout << "SendCommand received";
		return ;
	}
	else
	{
		altSendCommand(thecommand);
		return;
	}

	boost::to_upper(thecommand);

	string myreply;
	string strname;
	if (thecommand == "ADDSTREAM")
	{
		StreamSetup("","");
	}
	else if (thecommand == "SETUP")
	{
		CaseSetup("", "");
	}
	else if (thecommand == "OUTPUT")
	{
		OutputAll();
	}
	else if (thecommand == "SOLVE")
	{

		_activecase->Solve();
	}
	else if (thecommand == "ADDUNITOP")
	{
		UnitOpSetup("", "", "");
	}
	else if (thecommand == "EDITSTREAM")
	{
		std::cout << "WHICH STREAM? \n" ;
		cin >> myreply;
		StreamSetup(myreply, "");
	}


	else if (thecommand == "HELP")
	{
		std::cout << "COMMANDS AVAILABLE ARE: ADDSTREAM, ADDUNITOP, SOLVE, OUTPUT, EDITSTREAM \n";
	}
	else
	{
		std::cout << thecommand << "? DOES NOT COMPUTE.\n";
	}
}


void CommandInterpreter::ReadInputFile(string thefilepath)
{

}

std::string CommandInterpreter::GetStreamJSON(std::string thestream)
{
	std::string json = _jsongenerator->GetStream(_activecase->GetStream(thestream));
	return json;
}

std::string CommandInterpreter::GetUnitOpJSON(std::string theunitop)
{
	std::string json = _jsongenerator->GetUnitOp(_activecase->GetUnitOp(theunitop));
	return json;
}

void CommandInterpreter::tempDoMore()
{
	RealVariable* thetarg = _activecase->GetStream("STRM5")->Temperature();
	thetarg->SetValue(290);
	thetarg->IsDirty(true);
	thetarg->IsCalculated(false);

	/*thetarg = _activecase->GetStream("STRM1")->VapourFraction();
	thetarg->SetValue(0.6);
	thetarg->IsDirty(true);
	thetarg->IsCalculated(false);*/

	_activecase->Solve();
	_activecase->Output();


}
void CommandInterpreter::OutputAll()
{
	_activecase->Output();

}


void CommandInterpreter::CaseSetup(string theflash, string thecomps)
{
	
	string reply;

	//create new case by default
	//make option to load case
	//string* compnames;
	string compnames[20];
	std::istringstream  mypartstream(thecomps);
	int ncomps;
	//std::istringstream  mypartstream(thesetupcmd);
	for (int k = 0; k < 20; k++)
	{
		compnames[k] = "none";
	}

	thePPBuilder->BuildPackage();

	_activecase = new SimCase("Case1");
	bool issetup = false;
	std::cout << "Setting up property package.\n";
	
	while (!issetup)
	{
		if (theflash == "")
		{
			std::cout << "Select IDEAL or REFPROP: \n";
			cin >> theflash;
		}

		if (theflash == "IDEAL")
		{
			std::cout << "IDEAL selected.\n";
			thePPBuilder->SetFlashMethod(IDEAL);
			issetup = true;
		}
		else if (theflash == "REFPROP")
		{
			std::cout << "REFPROP selected.\n";
			thePPBuilder->SetFlashMethod(REFPROP);
			issetup = true;

		}
		else if (reply == "exit")
		{
			std::cout << "I give up.\n";
			issetup = true;
		}

		else
		{
			std::cout << "Does not compute.\n";
		}
	}

	issetup = false;
	ncomps = 0;
	while (!issetup)
	{
		
		if (thecomps == "")
		{
			std::cout << "Add a component. All caps please. \n";
			cin >> reply;
		}
		else
		{
			getline(mypartstream, reply,',');
		}

		if (reply == "DONE")
		{
			issetup = true;
		}
		else
		{ 
			thePPBuilder->AddComponent(reply);
		ncomps = ncomps + 1;
		std::cout << reply << " has been added. Add another component or enter DONE to finish \n";
		}
	}

	_activecase->SetPropPack(thePPBuilder->GetPackage());
	std::cout << "Case has been setup. \n";
}


void CommandInterpreter::StreamSetup(string thename, string thespecs)
{
	int myncomps;
	
	int i;
	bool issetup;
	RealVariable* thetarg=0;

	double tempdb;
	std::istringstream  mypartstream(thespecs);
	
	string param;
	string thevar;
	
	issetup = false;
	//set stream name
	if (thename == "")
	{
		std::cout << "Enter stream name \n";
		cin >> thename;
	}


	_activecase->AddStream(thename); //default proppack will be used
	myncomps = _activecase->GetStream(thename)->NComps();
	double* molecomps = new double[myncomps];
	
	while (issetup==false)
	{
		if (thespecs != "")
		{
			getline(mypartstream, param, ' ');
		}
		else
		{
			std::cout << "Enter specs: PRESSURE, TEMPERATURE, COMPOSITION, VAPOURFRACTION, ENTHALPY, MASSFLOW, MOLARFLOW OR DONE \n";
			cin >> param;

		}

		if (param == "PRESSURE")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter pressure in kPa \n";
				cin >> thevar;
			}
		
			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->Pressure();
			
		}
		else if (param == "TEMPERATURE")
		{	
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter temperature in Kelvin \n";
				cin >> thevar;
			}
			
			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->Temperature();

		}
		else if (param == "VAPOURFRACTION")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter vapour fraction (molar) (0 - 1) \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->VapourFraction();

		}
		else if (param == "COMPOSITION")
		{	
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter molar composition. eg 0.2,0.3,0.5 \n";
				cin >> thevar;
			}
			tempdb = 0; // this value will be checked for -32767 to see if a var is being emptied
			std::istringstream  compstream(thevar);
			i = 0;
				while (compstream.good())
				{
					getline(compstream, thevar,',');
					molecomps[i] = stod(thevar);
					i = i + 1;
				}
				thetarg = _activecase->GetStream(thename)->Composition();
		}
		else if (param == "ENTHALPY")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter molar enthalpy in J/mol \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->MolarEnthalpy();
		}
		else if (param == "ENTROPY")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter molar entropy in J/mol \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->MolarEntropy();
		}
		else if (param == "MASSFLOW")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter mass flow kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->MassFlow();
		}
		else if (param == "MOLARFLOW")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter molar flow kmol/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			thetarg = _activecase->GetStream(thename)->MolarFlow();
		}
		else if (param == "DONE")
		{
			issetup = true;
		}

		if (param != "DONE")
		{
			if (param == "COMPOSITION")
			{
				thetarg->SetValues(myncomps, molecomps);
				thetarg->IsDirty(true);
				/*for (int j = 0; j < 3; j++)
				{
					std::cout << _activecase->GetStream(thename)->Composition()->GetValue(j);
				}*/
				
				_activecase->GetStream(thename)->Normalise();
			}
			else
			{
				thetarg->SetValue(tempdb);
				thetarg->IsDirty(true);
				
			}
			if (tempdb == -32767) //check if its being emptied
			{
				thetarg->IsCalculated(true);
			}
			else
			{
				thetarg->IsCalculated(false);
			}
			
		}
		
	}
	std::cout << thename << " has been added.\n";

	


}

void CommandInterpreter::UnitOpSetup(string theop, string thename, string thespecs)
{
	//string myreply;
	//string strname;
	std::istringstream  streamstreami, streamstreamo;
	string nozzle;
	if (theop == "")
	{
		std::cout << "Enter unit operation : VALVE, HEATER,  MIXER, SPLITTER, COMPRESSOR \n";
		cin >> theop;
	}

	if (theop == "VALVE")
	{
		_theuobuilder->BuildUnitOp(VALVE);
	}
	else if (theop == "HEATER")
	{
		_theuobuilder->BuildUnitOp(HEATER);
	}
	else if (theop == "MIXER")
	{
		_theuobuilder->BuildUnitOp(MIXER);
	}
	else if (theop == "SPLITTER")
	{
		_theuobuilder->BuildUnitOp(SPLITTER);
	}
	else if (theop == "COMPRESSOR")
	{
		_theuobuilder->BuildUnitOp(COMPRESSOR);
	}
	else if (theop == "TWOPHASESEPARATOR")
	{
		_theuobuilder->BuildUnitOp(TWOPHASESEPARATOR);
	}
	else if (theop == "HEATEXCHANGER")
	{
		_theuobuilder->BuildUnitOp(HEATEXCHANGER);
	}
	bool issetup;

	double tempdb;
	std::istringstream  mypartstream(thespecs);

	string param;
	string thevar;

	issetup = false;
	//set stream name
	if (thename == "")
	{
		std::cout << "Enter unit op name \n";
		cin >> thename;
	}


	_theuobuilder->SetName(thename);
	//connect inlet
	if (thespecs != "")
	{
		getline(mypartstream, param, '\n');
	}
	else
	{
		std::cout << "Enter inlet stream(s) name. eg. Strm1,Strm2 \n";
		cin >> param;
	}

	  

	  if (param == "NONE")
	  {
		  goto skipconnectinlet;

	  }
	streamstreami= std::istringstream(param);
		while (streamstreami.good())
		{
			getline(streamstreami, param, ',');
			_theuobuilder->Connect(_activecase->GetStream(param), INLET);
		}
	
	skipconnectinlet:


	//connect outlet

	if (thespecs != "")
	{
		getline(mypartstream, param, '\n');
	}
	else 

	{
		std::cout << "Enter outlet stream(s) name. eg. Strm1,Strm2  \n";
		cin >> param;
	}
	  if (param == "NONE")
	  {
		  goto skipconnectoutlet;

	  }

	streamstreamo= std::istringstream(param);
	


	if (theop == "TWOPHASESEPARATOR")
	{
		while (streamstreamo.good())
		{
			getline(streamstreamo, param, ',');
			std::istringstream streamnozze(param);
			getline(streamnozze, nozzle, ' ');
			getline(streamnozze, param, ' ');
			if (nozzle == "LIQUID")
			{
				_theuobuilder->Connect(_activecase->GetStream(param), LIQUIDOUTLET);
			}
			else if (nozzle == "VAPOUR")
			{
				_theuobuilder->Connect(_activecase->GetStream(param), VAPOUROUTLET);
			}
			
		}
	}
	else
	{
		while (streamstreamo.good())
		{
			getline(streamstreamo, param, ',');
			_theuobuilder->Connect(_activecase->GetStream(param), OUTLET);
		}
	}
skipconnectoutlet:

	while (issetup == false)
	{

		if (thespecs != "")
		{
			getline(mypartstream, param, ' ');
		}
		else
		{
			if (theop == "VALVE")
			{
				std::cout << "Enter specs: K, PRESSUREDROP OR DONE \n";
			}
			else if (theop == "HEATER")
			{
				std::cout << "Enter specs: K, PRESSUREDROP, HEATINPUT OR DONE \n";
			}
			else if (theop == "COMPRESSOR")
			{
				std::cout << "Enter specs: DELTAPRESSURE, ENERGYINPUT, ISENTROPICEFFICIENCY OR DONE \n";
			}

			cin >> param;
		}

		if (param == "K")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter k in kpa-kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);

			_theuobuilder->SpecifyVariable(K_RESISTANCE, tempdb);
		}
		else if (param == "PRESSUREDROP")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter k in kpa-kg/h \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(DELTAPRESSURE, tempdb);
		}
		else if (param == "HEATINPUT")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter Q in W \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(ENERGYINPUT, tempdb);
		}
		else if (param == "ENERGYINPUT")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter Q in W \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(ENERGYINPUT, tempdb);
		}
		else if (param == "UA")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter UA in W/C \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(TYPEUA, tempdb);
		}
		else if (param == "SHELL_PRESSUREDROP")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter Shell side dP in kPa \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(SHELL_PRESSUREDROP, tempdb);
		}
		else if (param == "TUBE_PRESSUREDROP")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter Tube side dP in kPa \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(TUBE_PRESSUREDROP, tempdb);
		}
		else if (param == "ISENTROPICEFFICIENCY")
		{
			if (thespecs != "")
			{
				getline(mypartstream, thevar);
			}
			else
			{
				std::cout << "Enter isentropic efficiency in fraction eg 0.75 is 75 % \n";
				cin >> thevar;
			}

			tempdb = stod(thevar);
			_theuobuilder->SpecifyVariable(ISENTROPICEFFICIENCY, tempdb);
		}
		else if (param == "DONE")
		{
			issetup = true;
		}
	}
	_activecase->AddUnitOp(_theuobuilder->GetUnitOp());

	std::cout << thename << " has been added.\n";


}

void CommandInterpreter::tempsetup()
{
	_initfrominput("testDemoCase.txt");
}

void CommandInterpreter::_initfrominput(string theinputfile)
{
	string mystring;
	string str1, str2, str3, str4;

	fstream myfile;
	string mylongstring;
	OutputLogger* op = OutputLogger::Instance();

	bool isdone;
	isdone = false;
	//std::stringstream  mypartstream;
	myfile.open(theinputfile);
	while (myfile.good())
	{
		getline(myfile, mystring);
		if (mystring == "PROPPACK") //go into parsing for proppack setup
		{
			getline(myfile, str1);//this will be flash method
			getline(myfile, str2);//this will be components
			str2.append(",DONE");
			CaseSetup(str1, str2);
		}

		else if (mystring == "STREAM")
		{
			getline(myfile, str1);//this will be the name
			do
			{
				getline(myfile, str2);
				if (str3 != "")
				{
					str3.append("\n");
				}
				str3.append(str2);

			} while (str2 != "");
			str3.append("DONE");
			StreamSetup(str1, str3);
			str3 = "";

		}
		else if (mystring == "VALVE" || mystring == "HEATER" || mystring == "MIXER" || mystring == "SPLITTER" || mystring == "COMPRESSOR" || mystring == "TWOPHASESEPARATOR" || mystring == "HEATEXCHANGER")
		{
			getline(myfile, str1);//this will be the name
			do
			{
				getline(myfile, str2);
				if (str3 != "")
				{
					str3.append("\n");
				}
				str3.append(str2);

			} while (str2 != "");
			str3.append("DONE");
			UnitOpSetup(mystring, str1, str3);
			str3 = "";

		}
	}
	std::cout << "pre solve \n";
	//std::cout << "Stream _vapourfraction " << _activecase->GetStream("STRM1")->VapourFraction() << "\n";
	//std::cout << "Vapour PhaseFraction " << _activecase->GetStream("STRM1")->Phases(VAPOUR)->PhaseMoleFraction() << "\n";
	_activecase->Solve();
	_activecase->Output();
	myfile.close();
}
