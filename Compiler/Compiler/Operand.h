#pragma once
#include <string>
#include <windows.h>

using namespace std;

class Operand
{
private:
public:
	virtual ~Operand();
	virtual BYTE getCode() = 0;
};

