#pragma once
#include "NoOperandInstruction.h"

using namespace std;

class InstructionRet : public NoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionRet();
	InstructionRet(BYTE firstByte, bool isPrefix, SourceReciver sr);
	InstructionRet(BYTE firstByte, BYTE secondByte, bool isPrefix, SourceReciver sr);
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual NoOperandInstruction* clone();
};

