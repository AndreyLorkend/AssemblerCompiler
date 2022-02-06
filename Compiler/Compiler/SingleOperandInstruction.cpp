#include "SingleOperandInstruction.h"

SingleOperandInstruction::SingleOperandInstruction() : Instruction()
{
}

SingleOperandInstruction::SingleOperandInstruction(Operand* operand, bool flag, SourceReciver sr) : Instruction(flag, sr)
{
	operand_ = operand;
}

SingleOperandInstruction::~SingleOperandInstruction()
{
	if (operand_ != NULL) {
		//delete operand_;
	}
}

Operand* SingleOperandInstruction::getOperand()
{
	return operand_;
}

void SingleOperandInstruction::setOperand(Operand* operand)
{
	operand_ = operand;
}

SingleOperandInstruction* SingleOperandInstruction::clone()
{
	return NULL;
}

void SingleOperandInstruction::setDisp(BYTE disp)
{
	disp8_ = disp;
}
