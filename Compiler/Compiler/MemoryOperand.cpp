#include "MemoryOperand.h"

MemoryOperand::MemoryOperand(string name, BYTE memoryCode, BYTE memoryLength, BYTE mod, BYTE offset)
{
	name_ = name;
	memoryCode_ = memoryCode;
	memoryLength_ = memoryLength;
	mod_ = mod;
	offset_ = offset;
}
