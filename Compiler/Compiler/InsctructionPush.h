#pragma once
#include "SingleOperandInstruction.h"

using namespace std;

class InsctructionPush : public SingleOperandInstruction
{
private:
	BYTE firstByte_;
public:
	InsctructionPush();
	InsctructionPush(BYTE firstByte, Operand* operand, bool prefixFlag, SourceReciver sr); // if operand register
	//InsctructionPush(const InsctructionPush& element);
	int getInstructionSize();
	virtual void showInstructionCode() override final;
	virtual void writeToFile(ofstream* fout) override final;
	virtual SingleOperandInstruction* clone();
};

