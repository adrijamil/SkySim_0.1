#pragma once
#include "ErrorLogger.h"
#include <stdio.h>
#include "HandledException.h"
#include <string>
using namespace std;

class ErrorLogger
{
	static ErrorLogger *s_instance;
	bool _verbose;
	std::string _logs;

public:
	ErrorLogger(){ _logs = ""; };
	~ErrorLogger();
	void Handle(HandledException& e)
	{
		//cout << "Exception encountered: " << e.what();
		_logs.append(e.what());
		_logs.append("\n");
	}
	static ErrorLogger *Instance()
	{
		if (!s_instance)
			s_instance = new ErrorLogger;
		return s_instance;
	}
	void Spit()
	{
		std::cout << _logs;
	}
};
