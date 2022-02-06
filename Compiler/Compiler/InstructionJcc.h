#pragma once
#include "SingleOperandInstruction.h"

using namespace std;

class InstructionJcc : public SingleOperandInstruction
{
private:
	BYTE firstByte_;
	BYTE tttnFlag_;
public:
	InstructionJcc();
	InstructionJcc(BYTE firstByte, BYTE tttnFlag, BYTE disp8, Operand* operand, bool isPrefix, SourceReciver sr); // for short jump
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual SingleOperandInstruction* clone();
};

