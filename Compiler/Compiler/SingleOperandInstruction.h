#pragma once
#include "Instruction.h"

class SingleOperandInstruction : public Instruction
{
private:
	Operand* operand_;
public:
	SingleOperandInstruction(InstructionCode instructionCode, Operand* operand, bool flag, SourceReciver sr);
};

