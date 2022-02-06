#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionMov : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionMov();
	InstructionMov(BYTE firstByte, BYTE secondByte, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataPrefix, SourceReciver sr); // REG-DATA
	InstructionMov(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr); // REG-REG
	InstructionMov(BYTE firstByte, BYTE secondByte, BYTE wFlag, Operand* firstOperand, BYTE modFlag, Operand* secondOperand, bool isPrefix, SourceReciver sr); // REG-MEM
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

