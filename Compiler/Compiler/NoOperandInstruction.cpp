#include "NoOperandInstruction.h"

NoOperandInstruction::NoOperandInstruction(InstructionCode instructionCode, bool flag, SourceReciver sr) : Instruction(instructionCode, flag, false, 0, sr)
{
}
