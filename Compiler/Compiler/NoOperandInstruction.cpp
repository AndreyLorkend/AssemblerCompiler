#include "NoOperandInstruction.h"

NoOperandInstruction::NoOperandInstruction() : Instruction()
{
}

NoOperandInstruction::NoOperandInstruction(bool flag, SourceReciver sr) : Instruction(flag, sr)
{
}

NoOperandInstruction::~NoOperandInstruction()
{
}

NoOperandInstruction* NoOperandInstruction::clone()
{
    return NULL;
}
