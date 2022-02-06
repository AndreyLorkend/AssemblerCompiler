#pragma once
#include "Operand.h"

class RegisterOperand : public Operand
{
private:
	string name_;
	BYTE registerCode_;
	BYTE registerLength_;
public:
	RegisterOperand(string name, BYTE registerCode, BYTE registerLength);
	BYTE getCode();
	BYTE getLength();
};

