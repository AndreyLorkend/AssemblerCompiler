#pragma once
#include "Instruction.h"

class NoOperandInstruction : public Instruction
{
private:
public:
	NoOperandInstruction();
	NoOperandInstruction(bool flag, SourceReciver sr);
	virtual ~NoOperandInstruction();
	virtual int getInstructionSize() = 0;
	virtual void showInstructionCode() = 0;
	virtual void writeToFile(ofstream* fout) = 0;
	virtual NoOperandInstruction* clone();
};

