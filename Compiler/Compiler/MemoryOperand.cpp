#include "MemoryOperand.h"

MemoryOperand::MemoryOperand(string name, BYTE memoryCode, BYTE memoryLength, BYTE offset)
{
	name_ = name;
	memoryCode_ = memoryCode;
	memoryLength_ = memoryLength;
	offset_ = offset;
}

BYTE MemoryOperand::getCode()
{
	return memoryCode_;
}

BYTE MemoryOperand::getLength()
{
	return memoryLength_;
}

BYTE MemoryOperand::getOffset()
{
	return offset_;
}
