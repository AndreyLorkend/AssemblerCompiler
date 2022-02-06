#include "InstructionAdd.h"
#include "DataOperand.h"
#include "RegisterOperand.h"

InstructionAdd::InstructionAdd() : TwoOperandInstruction()
{
}

InstructionAdd::InstructionAdd(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool prefixFlag, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, prefixFlag, sr, dFlag, wFlag, NULL, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

InstructionAdd::InstructionAdd(BYTE firstByte, BYTE secondByte, BYTE sFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool prefixFlag, bool dataFlag, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, prefixFlag, sr, NULL, wFlag, sFlag, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionAdd::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getSourceReciver() == REG_DATA) {
		Operand* op = getSecondOperand();
		size += reinterpret_cast<DataOperand&>(op).getOperandSize();
	}
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionAdd::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionAdd::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	if (getSourceReciver() == REG_REG) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | (getFlagD() << 1) | getFlagW();
		secondByte_ = secondByte_ | (dynamic_cast<RegisterOperand&>(*fop).getCode() << 3) | (dynamic_cast<RegisterOperand&>(*sop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | (getFlagS() << 1) | getFlagW();
		secondByte_ = secondByte_ | (dynamic_cast<RegisterOperand&>(*fop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(BYTE)) {
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

TwoOperandInstruction* InstructionAdd::clone()
{
	InstructionAdd* ptr = new InstructionAdd();
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
