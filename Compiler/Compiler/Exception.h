#pragma once
#include <string>
#include <iostream>

using namespace std;

class Exception
{
private:
	int exceptionNumber_;
	string exceptionString_;
public:
	virtual ~Exception();
	virtual void displayException() = 0;
	void setExceptionNumber(int exceptionNumber);
	void setExceptionString(string exceptionString);
	int getExceptionNumber();
	string getExceptionString();
};

