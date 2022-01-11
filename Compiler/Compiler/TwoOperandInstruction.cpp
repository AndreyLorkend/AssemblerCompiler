#include "TwoOperandInstruction.h"

TwoOperandInstruction::TwoOperandInstruction(InstructionCode instructionCode, Operand* firstOperand, Operand* secondOperand, bool flag, int data, bool dataFlag, SourceReciver sr)
	: Instruction(instructionCode, flag, dataFlag, data, sr)
{
	firstOperand_ = firstOperand;
	secondOperand_ = secondOperand;
}
