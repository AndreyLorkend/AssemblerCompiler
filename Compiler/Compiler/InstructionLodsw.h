#pragma once
#include "NoOperandInstruction.h"

using namespace std;

class InstructionLodsw : public NoOperandInstruction
{
private:
	BYTE firstByte_;
public:
	InstructionLodsw();
	InstructionLodsw(BYTE firstByte, bool isPrefix, SourceReciver sr);
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual NoOperandInstruction* clone();
};

