#pragma once
#include "Instruction.h"

class NoOperandInstruction : public Instruction
{
private:
public:
	NoOperandInstruction(InstructionCode instructionCode, bool flag, SourceReciver sr);
};

