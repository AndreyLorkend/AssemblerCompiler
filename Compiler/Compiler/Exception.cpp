#include "Exception.h"

Exception::~Exception()
{
}

void Exception::setExceptionNumber(int exceptionNumber)
{
	exceptionNumber_ = exceptionNumber;
}

void Exception::setExceptionString(string exceptionString)
{
	exceptionString_ = exceptionString;
}

int Exception::getExceptionNumber()
{
	return exceptionNumber_;
}

string Exception::getExceptionString()
{
	return exceptionString_;
}
