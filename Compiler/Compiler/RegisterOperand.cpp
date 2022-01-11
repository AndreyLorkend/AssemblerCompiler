#include "RegisterOperand.h"

RegisterOperand::RegisterOperand(string name, BYTE registerCode, BYTE registerLength)
{
	name_ = name;
	registerCode_ = registerCode;
	registerLength_ = registerLength;
}
