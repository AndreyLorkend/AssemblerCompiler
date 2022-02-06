#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionSbb : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionSbb();
	InstructionSbb(BYTE firstByte, BYTE secondByte, BYTE sFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataFlag, SourceReciver sr); //REG-DATA
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

