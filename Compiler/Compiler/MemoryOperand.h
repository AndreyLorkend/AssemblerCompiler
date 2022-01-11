#pragma once
#include "Operand.h"

class MemoryOperand : public Operand
{
private:
	string name_;
	BYTE memoryCode_;
	BYTE memoryLength_;
	BYTE offset_;
	BYTE mod_;
public:
	MemoryOperand(string name, BYTE memoryCode, BYTE memoryLength, BYTE mod, BYTE offset);
};

