#include "InstructionCmp.h"
#include "RegisterOperand.h"
#include "MemoryOperand.h"

InstructionCmp::InstructionCmp() : TwoOperandInstruction()
{
}

InstructionCmp::InstructionCmp(BYTE firstByte, BYTE secondByte, BYTE wFlag, BYTE modFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, sr, NULL, wFlag, NULL, modFlag)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionCmp::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getSourceReciver() == REG_MEM) {
		size += 1;
	}
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionCmp::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionCmp::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	if (getSourceReciver() == REG_MEM) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | (getFlagD() << 1) | getFlagW();
		secondByte_ = secondByte_ | (getFlagMod() << 6) | (dynamic_cast<RegisterOperand&>(*fop).getCode() << 3) | (dynamic_cast<MemoryOperand&>(*sop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		BYTE offset = dynamic_cast<MemoryOperand&>(*sop).getOffset();
		fout->write(reinterpret_cast<const char*>(&offset), sizeof(BYTE));
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << " " << dynamic_cast<MemoryOperand&>(*sop).getOffset() + 0x0 << endl;
	}
}

TwoOperandInstruction* InstructionCmp::clone()
{
	InstructionCmp* ptr = new InstructionCmp();
	ptr->firstByte_ = firstByte_;
	ptr->secondByte_ = secondByte_;
	ptr->setFirstOperand(NULL);
	ptr->setSecondOperand(NULL);
	ptr->setFlagD(NULL);
	ptr->setFlagW(NULL);
	ptr->setFlagS(NULL);
	ptr->setFlagMod(1);
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	if (getSourceReciver() == REG_DATA) {
		ptr->setDataFlag(true);
	}
	return ptr;
}
