#include "stdafx.h"
#include "JSONGenerator.h"






JSONGenerator::JSONGenerator()
{
}


JSONGenerator::~JSONGenerator()
{
}

std::string JSONGenerator::GetStream(Stream * thestream)
{
	ptree stream_pt;
	ptree phase_pt;
	ptree comps_pt;
	ptree variable_pt;

	//do stream properties
	stream_pt.put("Name", thestream->Name());

	//component names
	for (int i = 0;i < thestream->NComps();i++)
	{
		comps_pt.put(std::to_string(i).c_str(), thestream->GetPropertyPackage()->GetComponent(i).Name);
	}
	stream_pt.add_child("Components", comps_pt);
	comps_pt.clear();
	variable_pt.clear();

	//stream variables
	//pressure
	variable_pt.put("Value", thestream->Pressure()->GetValue());
	variable_pt.put("CanModify", !thestream->Pressure()->IsCalculated());
	stream_pt.add_child("Pressure", variable_pt);
	variable_pt.clear();

	//temperature
	variable_pt.put("Value", thestream->Temperature()->GetValue());
	variable_pt.put("CanModify", !thestream->Temperature()->IsCalculated());
	stream_pt.add_child("Temperature", variable_pt);
	variable_pt.clear();

	//massflow
	variable_pt.put("Value", thestream->MassFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->MassFlow()->IsCalculated());
	stream_pt.add_child("MassFlow", variable_pt);
	variable_pt.clear();

	//molarflow
	variable_pt.put("Value", thestream->MolarFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->MolarFlow()->IsCalculated());
	stream_pt.add_child("MolarFlow", variable_pt);
	variable_pt.clear();

	//molarenthalpy
	variable_pt.put("Value", thestream->MolarEnthalpy()->GetValue());
	variable_pt.put("CanModify", !thestream->MolarEnthalpy()->IsCalculated());
	stream_pt.add_child("MolarEnthalpy", variable_pt);
	variable_pt.clear();

	//PhasesPresent
	//vap
	if (thestream->Phases(VAPOUR) == NULL)
	{
		variable_pt.put("Vapour", false);
	}
	else
	{
		variable_pt.put("Vapour", true);
	}
	//liq
	if (thestream->Phases(HCLIQUID) == NULL)
	{
		variable_pt.put("Liquid", false);
	}
	else
	{
		variable_pt.put("Liquid", true);
	}
	//aq
	if (thestream->Phases(AQUEOUS) == NULL)
	{
		variable_pt.put("Aqueous", false);
	}
	else
	{
		variable_pt.put("Aqueous", true);
	}

	stream_pt.add_child("PhasesPresent", variable_pt);
	variable_pt.clear();

	//composition
	for (int i = 0;i < thestream->NComps();i++)
	{
		comps_pt.put(std::to_string(i), thestream->Composition()->GetValue(i));
	}
	variable_pt.add_child("Value", comps_pt);
	comps_pt.clear();
	variable_pt.put("CanModify", !thestream->Composition()->IsCalculated());
	stream_pt.add_child("Composition", variable_pt);
	variable_pt.clear();

	//do phases
	//vapour
	//massflow
	variable_pt.put("Value", thestream->Phases(0)->MassFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(0)->MassFlow()->IsCalculated());
	phase_pt.add_child("MassFlow", variable_pt);
	variable_pt.clear();

	//MolarFlow
	variable_pt.put("Value", thestream->Phases(0)->MolarFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(0)->MolarFlow()->IsCalculated());
	phase_pt.add_child("MolarFlow", variable_pt);
	variable_pt.clear();

	//molefrac
	variable_pt.put("Value", thestream->Phases(0)->PhaseMoleFraction()->GetValue());
	variable_pt.put("CanModify", thestream->Phases(0)->PhaseMoleFraction()->IsCalculated());
	phase_pt.add_child("MoleFraction", variable_pt);
	variable_pt.clear();

	//molarenthalpy
	variable_pt.put("Value", thestream->Phases(0)->MolarEnthalpy()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(0)->MolarEnthalpy()->IsCalculated());
	phase_pt.add_child("MolarEnthalpy", variable_pt);
	variable_pt.clear();

	//composition
	for (int i = 0;i < thestream->NComps();i++)
	{
		comps_pt.put(std::to_string(i), thestream->Phases(0)->Composition()->GetValue(i));
	}
	variable_pt.add_child("Value", comps_pt);
	comps_pt.clear();
	variable_pt.put("CanModify", !thestream->Phases(0)->Composition()->IsCalculated());
	phase_pt.add_child("Composition", variable_pt);
	variable_pt.clear();

	stream_pt.add_child("Vapour", phase_pt);
	phase_pt.clear();

	//liquid
	//massflow
	variable_pt.put("Value", thestream->Phases(1)->MassFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(1)->MassFlow()->IsCalculated());
	phase_pt.add_child("MassFlow", variable_pt);
	variable_pt.clear();

	//molefrac
	variable_pt.put("Value", thestream->Phases(1)->PhaseMoleFraction()->GetValue());
	variable_pt.put("CanModify", thestream->Phases(1)->PhaseMoleFraction()->IsCalculated());
	phase_pt.add_child("MoleFraction", variable_pt);
	variable_pt.clear();

	//MolarFlow
	variable_pt.put("Value", thestream->Phases(1)->MolarFlow()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(1)->MolarFlow()->IsCalculated());
	phase_pt.add_child("MolarFlow", variable_pt);
	variable_pt.clear();

	//molarenthalpy
	variable_pt.put("Value", thestream->Phases(1)->MolarEnthalpy()->GetValue());
	variable_pt.put("CanModify", !thestream->Phases(1)->MolarEnthalpy()->IsCalculated());
	phase_pt.add_child("MolarEnthalpy", variable_pt);
	variable_pt.clear();

	//composition
	for (int i = 0;i < thestream->NComps();i++)
	{
		comps_pt.put(std::to_string(i), thestream->Phases(1)->Composition()->GetValue(i));
	}
	variable_pt.add_child("Value", comps_pt);
	comps_pt.clear();
	variable_pt.put("CanModify", !thestream->Phases(1)->Composition()->IsCalculated());
	phase_pt.add_child("Composition", variable_pt);
	variable_pt.clear();


	stream_pt.add_child("Liquid", phase_pt);
	phase_pt.clear();


	std::ostringstream buf;
	write_json(buf, stream_pt, true);
	std::string json = buf.str();
	//std::cout << json;



	return json;
}

std::string JSONGenerator::GetUnitOp(UnitOp * theunitop)
{
	std::string json;


	//this part should be templatized or make it such that we can obtain type from base pointer
	Valve* vlvptr = dynamic_cast<Valve *>(theunitop);
	if (vlvptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
	{
		json = _getvalve(vlvptr);
		return json;
	}	

	Heater* heaterptr = dynamic_cast<Heater*> (theunitop);
	if (heaterptr != NULL)// this is a bad workaround// come up with a better way to typecast to proper class pointer
	{
		json = _getheater(heaterptr);
		return json;
	}
	
}


std::string JSONGenerator::_getvalve(Valve* thevalve)
{
	ptree valve_pt;

	ptree variable_pt;

	valve_pt.put("Name", thevalve->Name());

	variable_pt.put("Value", thevalve->K_Resistance()->GetValue());
	variable_pt.put("CanModify", !thevalve->K_Resistance()->IsCalculated());
	valve_pt.add_child("K_Resistance", variable_pt);
	variable_pt.clear();

	variable_pt.put("Value", thevalve->PressureDrop()->GetValue());
	variable_pt.put("CanModify", !thevalve->PressureDrop()->IsCalculated());
	valve_pt.add_child("PressureDrop", variable_pt);
	variable_pt.clear();

	std::ostringstream buf;
	write_json(buf, valve_pt, true);
	std::string json = buf.str();
	return json;
}

std::string JSONGenerator::_getheater(Heater * thevalve)
{
	return "asdas";
}

////is this specialised correctly
//template<class T> std::string JSONGenerator::_getspecificunitop(T theunitop)
//{
//	std::string json = "im dunno what i am";
//	return json;
//}
//
//
//template<> std::string JSONGenerator<Valve>::_getspecificunitop(Valve theunitop)
//{
//	std::string json = "im a valve";
//	return json;
//}
//
//template<> std::string JSONGenerator<Heater>::_getspecificunitop(Heater theunitop)
//{
//	std::string json = "im a heater";
//	return json;
//}