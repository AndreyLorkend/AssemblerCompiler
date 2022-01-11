#include "SingleOperandInstruction.h"

SingleOperandInstruction::SingleOperandInstruction(InstructionCode instructionCode, Operand* operand, bool flag, SourceReciver sr) : Instruction(instructionCode, flag, false, 0, sr)
{
	operand_ = operand;
}
