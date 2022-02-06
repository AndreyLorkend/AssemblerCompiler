#pragma once
#include "SingleOperandInstruction.h"

using namespace std;

class InstructionJmp : public SingleOperandInstruction
{
private:
	BYTE firstByte_;
public:
	InstructionJmp();
	InstructionJmp(BYTE firstByte, BYTE disp8, Operand* operand, bool isPrefix, SourceReciver sr); // for short jump
	int getInstructionSize();
	void showInstructionCode() override final;
	void writeToFile(ofstream* fout);
	virtual SingleOperandInstruction* clone();
};

