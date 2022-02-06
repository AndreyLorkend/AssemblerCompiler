#pragma once
#include "Instruction.h"

class SingleOperandInstruction : public Instruction
{
private:
	Operand* operand_;
protected:
	BYTE disp8_;
public:
	SingleOperandInstruction();
	SingleOperandInstruction(Operand* operand, bool flag, SourceReciver sr);
	virtual ~SingleOperandInstruction();
	virtual int getInstructionSize() = 0;
	Operand* getOperand();
	void setOperand(Operand* operand);
	virtual void showInstructionCode() = 0;
	virtual void writeToFile(ofstream* fout) = 0;
	virtual SingleOperandInstruction* clone();
	void setDisp(BYTE disp);
};

