#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionXor : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionXor();
	InstructionXor(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr); //REG-REG
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

