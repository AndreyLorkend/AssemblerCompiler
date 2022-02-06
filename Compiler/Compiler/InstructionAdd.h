#pragma once
#include "TwoOperandInstruction.h"

using namespace std;

class InstructionAdd : public TwoOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE secondByte_;
public:
	InstructionAdd();
	InstructionAdd(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool prefixFlag, SourceReciver sr); // REG-REG
	InstructionAdd(BYTE firstByte, BYTE secondByte, BYTE sFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool prefixFlag, bool dataFlag, SourceReciver sr); // REG-DATA
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual TwoOperandInstruction* clone();
};

