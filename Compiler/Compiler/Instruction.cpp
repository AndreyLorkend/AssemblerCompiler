#include "Instruction.h"

Instruction::Instruction()
{
}

Instruction::Instruction(bool flag, SourceReciver sr)
{
    prefix16bits_ = 0;
    sourceReciver_ = sr;
    isPrefixUsed_ = flag;
    isDataFlag_ = false;
    if (isPrefixUsed_) {
        prefix16bits_ = 0x66;
    }
}

Instruction::Instruction(bool flag, bool dataFlag, SourceReciver sr)
{
    prefix16bits_ = 0;
    sourceReciver_ = sr;
    isPrefixUsed_ = flag;
    isDataFlag_ = dataFlag;
    if (isPrefixUsed_) {
        prefix16bits_ = 0x66;
    }
}

void Instruction::setPrefixFlag(bool flag)
{
    isPrefixUsed_ = flag;
    if (flag) {
        prefix16bits_ = 0x66;
    }
}

void Instruction::setDataFlag(bool flag)
{
    isDataFlag_ = flag;
}

bool Instruction::getPrefixFlag()
{
    return isPrefixUsed_;
}

bool Instruction::getDataFlag()
{
    return isDataFlag_;
}

Instruction::~Instruction()
{
}

void Instruction::writeToFile(ofstream* fout)
{
}

void Instruction::setSourceReciver(SourceReciver sr)
{
    sourceReciver_ = sr;
}

SourceReciver Instruction::getSourceReciver()
{
    return sourceReciver_;
}

BYTE Instruction::getPrefix()
{
    return prefix16bits_;
}
