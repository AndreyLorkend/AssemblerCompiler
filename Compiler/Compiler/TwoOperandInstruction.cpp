#include "TwoOperandInstruction.h"

TwoOperandInstruction::TwoOperandInstruction() : Instruction()
{
}

TwoOperandInstruction::TwoOperandInstruction(Operand* firstOperand, Operand* secondOperand, bool flag, SourceReciver sr, BYTE dFlag, BYTE wFlag, BYTE sFlag, BYTE modFlag)
	: Instruction(flag,  sr)
{
	firstOperand_ = firstOperand;
	secondOperand_ = secondOperand;
	dFlag_ = dFlag;
	wFlag_ = wFlag;
	sFlag_ = sFlag;
	modFlag_ = modFlag;
}

TwoOperandInstruction::TwoOperandInstruction(Operand* firstOperand, Operand* secondOperand, bool flag, bool dataFlag, SourceReciver sr, BYTE dFlag, BYTE wFlag, BYTE sFlag, BYTE modFlag)
	: Instruction(flag, dataFlag, sr)
{
	firstOperand_ = firstOperand;
	secondOperand_ = secondOperand;
	dFlag_ = dFlag;
	wFlag_ = wFlag;
	sFlag_ = sFlag;
	modFlag_ = modFlag;
}

TwoOperandInstruction::~TwoOperandInstruction()
{
	if (firstOperand_ != NULL) {
		//delete firstOperand_;
	}
	if (secondOperand_ != NULL) {
		//delete secondOperand_;
	}
}

BYTE TwoOperandInstruction::getFlagD()
{
	return dFlag_;
}

BYTE TwoOperandInstruction::getFlagW()
{
	return wFlag_;
}

BYTE TwoOperandInstruction::getFlagS()
{
	return sFlag_;
}

BYTE TwoOperandInstruction::getFlagMod()
{
	return modFlag_;
}

void TwoOperandInstruction::setFlagD(BYTE flag)
{
	dFlag_ = flag;
}

void TwoOperandInstruction::setFlagW(BYTE flag)
{
	wFlag_ = flag;
}

void TwoOperandInstruction::setFlagS(BYTE flag)
{
	sFlag_ = flag;
}

void TwoOperandInstruction::setFlagMod(BYTE flag)
{
	modFlag_ = flag;
}

void TwoOperandInstruction::setFirstOperand(Operand* fop)
{
	firstOperand_ = fop;
}

void TwoOperandInstruction::setSecondOperand(Operand* sop)
{
	secondOperand_ = sop;
}

Operand* TwoOperandInstruction::getFirstOperand()
{
	return firstOperand_;
}

Operand* TwoOperandInstruction::getSecondOperand()
{
	return secondOperand_;
}

TwoOperandInstruction* TwoOperandInstruction::clone()
{
	return NULL;
}
