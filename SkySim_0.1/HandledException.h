#pragma once
#include <exception>
using namespace std;

class HandledException :
	public exception
{
	
	string _message;
public:
	HandledException();
	HandledException(string message);
	~HandledException();
	virtual const char* what() const throw()
	{
		return _message.c_str();
	}
};

