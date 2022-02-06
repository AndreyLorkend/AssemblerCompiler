#include "InstructionRcl.h"
#include "DataOperand.h"
#include "RegisterOperand.h"

InstructionRcl::InstructionRcl() : TwoOperandInstruction()
{
}

InstructionRcl::InstructionRcl(BYTE firstByte, BYTE secondByte, BYTE wFlag, BYTE modFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, isDataPrefix, sr, NULL, wFlag, NULL, modFlag)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionRcl::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getSourceReciver() == REG_DATA) {
		size += 1;
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* op = getSecondOperand();
		size += reinterpret_cast<DataOperand&>(op).getOperandSize();
	}
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionRcl::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionRcl::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | getFlagW();
		secondByte_ = secondByte_ | (getFlagMod() << 6) | (dynamic_cast<RegisterOperand&>(*fop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(BYTE)){
			BYTE data = dynamic_cast<DataOperand&>(*sop).getByteData();
			fout->write(reinterpret_cast<const char*>(&data), sizeof(BYTE));
		}
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(WORD)) {
			WORD data = dynamic_cast<DataOperand&>(*sop).getWordData();
			fout->write(reinterpret_cast<const char*>(&data), sizeof(BYTE));
		}
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(DWORD32)) {
			DWORD32 data = dynamic_cast<DataOperand&>(*sop).getDwordData();
			fout->write(reinterpret_cast<const char*>(&data), sizeof(BYTE));
		}
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << " " << dynamic_cast<DataOperand&>(*sop).getByteData() + 0x0 << endl;
	}
}

TwoOperandInstruction* InstructionRcl::clone()
{
	InstructionRcl* ptr = new InstructionRcl();
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
