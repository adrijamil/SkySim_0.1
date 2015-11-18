#include "stdafx.h"
#include "OutputLogger.h"


OutputLogger::OutputLogger()
{
}
//
//OutputLogger* OutputLogger::_instance = 0;

OutputLogger::~OutputLogger()
{
}
OutputLogger* OutputLogger::Instance()
{
	if (_instance == 0)
	{
		_instance = new OutputLogger;

	}
	return _instance;

}