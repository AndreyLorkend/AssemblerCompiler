#include "CompilerException.h"

CompilerException::CompilerException(int exceptionNumber, string exceptionString)
{
	setExceptionNumber(exceptionNumber);
	setExceptionString(exceptionString);
}

void CompilerException::displayException()
{
	cout << "Compiler error " << getExceptionNumber() << " : " << getExceptionString() << endl;
}
