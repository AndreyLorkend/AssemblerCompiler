#include "Instruction.h"

Instruction::Instruction(InstructionCode instructionCode, bool flag, bool dataFlag, int data, SourceReciver sr)
{
    instructionCode_ = instructionCode;
    prefix16bits_ = 0x66;
    isPrefixUsed = flag;
    data_ = data;
    isData_ = dataFlag;
    sourceReciver = sr;
}

void Instruction::setPrefixFlag(bool flag)
{
    isPrefixUsed = flag;
}

bool Instruction::getPrefixFlag()
{
    return isPrefixUsed;
}

void Instruction::setSecondByte(BYTE sbyte)
{
    instructionCode_.secondByte = sbyte;
}

InstructionCode Instruction::getInstructionCode()
{
    return instructionCode_;
}

Instruction::~Instruction()
{
}

int Instruction::getData()
{
    return data_;
}

bool Instruction::getDataFlag()
{
    return isData_;
}

void Instruction::setSourceReciver(SourceReciver sr)
{
    sourceReciver = sr;
}

SourceReciver Instruction::getSourceReciver()
{
    return sourceReciver;
}
