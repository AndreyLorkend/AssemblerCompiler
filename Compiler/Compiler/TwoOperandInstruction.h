#pragma once
#include "Instruction.h"

class TwoOperandInstruction : public Instruction
{
private:
	Operand* firstOperand_;
	Operand* secondOperand_;
public:
	TwoOperandInstruction(InstructionCode instructionCode, Operand* firstOperand, Operand* secondOperand, bool flag, int data, bool dataFlag, SourceReciver sr);
};

