#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionCmp : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionCmp();
	InstructionCmp(BYTE firstByte, BYTE secondByte, BYTE wFlag, BYTE modFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr); // REG-MEM
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

