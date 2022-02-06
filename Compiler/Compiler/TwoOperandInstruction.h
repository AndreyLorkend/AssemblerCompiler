#pragma once
#include "Instruction.h"

class TwoOperandInstruction : public Instruction
{
private:
	Operand* firstOperand_;
	Operand* secondOperand_;
	BYTE dFlag_;
	BYTE wFlag_;
	BYTE sFlag_;
	BYTE modFlag_;
public:
	TwoOperandInstruction();
	TwoOperandInstruction(Operand* firstOperand, Operand* secondOperand, bool flag, SourceReciver sr, BYTE dFlag, BYTE wFlag, BYTE sFlag, BYTE modFlag);
	TwoOperandInstruction(Operand* firstOperand, Operand* secondOperand, bool flag, bool dataFlag, SourceReciver sr, BYTE dFlag, BYTE wFlag, BYTE sFlag, BYTE modFlag);
	~TwoOperandInstruction();
	//getters
	BYTE getFlagD();
	BYTE getFlagW();
	BYTE getFlagS();
	BYTE getFlagMod();
	virtual int getInstructionSize() = 0;
	//setters
	void setFlagD(BYTE flag);
	void setFlagW(BYTE flag);
	void setFlagS(BYTE flag);
	void setFlagMod(BYTE flag);
	void setFirstOperand(Operand* fop);
	void setSecondOperand(Operand* sop);
	Operand* getFirstOperand();
	Operand* getSecondOperand();
	virtual void showInstructionCode() = 0;
	virtual void writeToFile(ofstream* fout) = 0;
	virtual TwoOperandInstruction* clone();
};

