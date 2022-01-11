#pragma once
#include "Exception.h"

using namespace std;

class CompilerException : public Exception
{
public:
	CompilerException(int exceptionNumber, string exceptionString);
	void displayException();
};

