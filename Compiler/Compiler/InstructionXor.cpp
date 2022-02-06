#include "InstructionXor.h"
#include "RegisterOperand.h"

InstructionXor::InstructionXor() : TwoOperandInstruction()
{
}

InstructionXor::InstructionXor(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, sr, dFlag, wFlag, NULL, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionXor::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionXor::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionXor::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	if (getSourceReciver() == REG_REG) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | (getFlagD() << 1) | getFlagW();
		BYTE fCode = (dynamic_cast<RegisterOperand&>(*fop)).getCode();
		BYTE sCode = (dynamic_cast<RegisterOperand&>(*sop)).getCode();
		secondByte_ = secondByte_ | (fCode << 3) | sCode;
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
	}
}

TwoOperandInstruction* InstructionXor::clone()
{
	InstructionXor* ptr = new InstructionXor();
	ptr->firstByte_ = firstByte_;
	ptr->secondByte_ = secondByte_;
	ptr->setFirstOperand(NULL);
	ptr->setSecondOperand(NULL);
	ptr->setFlagD(NULL);
	ptr->setFlagW(NULL);
	ptr->setFlagS(NULL);
	ptr->setFlagMod(NULL);
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	if (getSourceReciver() == REG_DATA) {
		ptr->setDataFlag(true);
	}
	return ptr;
}
