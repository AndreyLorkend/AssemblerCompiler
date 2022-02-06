#pragma once
#include "Operand.h"

class MemoryOperand : public Operand
{
private:
	string name_;
	BYTE memoryCode_;
	BYTE memoryLength_;
	BYTE offset_;
public:
	MemoryOperand(string name, BYTE memoryCode, BYTE memoryLength, BYTE offset);
	BYTE getCode();
	BYTE getLength();
	BYTE getOffset();
};

