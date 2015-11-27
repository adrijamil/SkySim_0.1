#pragma once

#include <string>
#include "Stream.h"
#include "UnitOp.h"
//these includes are for json conversion
#include <fstream>
#include <sstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

#include "Valve.h"
#include "Heater.h"
#include "Mixer.h"

class JSONGenerator
{
public:
	JSONGenerator();
	~JSONGenerator();
	std::string GetStream(Stream* thestream);
	std::string GetUnitOp(UnitOp* theunitop);
private:
	std::string _getvalve(Valve* thevalve);
	std::string _getheater(Heater* thevalve);
	std::string _getmixer(Mixer * theunitop);
	/*template <class T> std::string _getspecificunitop(T theunitop);
	template <> std::string  _getspecificunitop(Valve theunitop);
	template <> std::string  _getspecificunitop(Heater theunitop);*/

};

