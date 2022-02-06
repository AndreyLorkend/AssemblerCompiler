#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionRcl : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionRcl();
	InstructionRcl(BYTE firstByte, BYTE secondByte, BYTE wFlag, BYTE modFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataPrefix, SourceReciver sr); //REG-DATA
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

