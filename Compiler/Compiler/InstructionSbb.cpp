#include "InstructionSbb.h"
#include "DataOperand.h"
#include "RegisterOperand.h"

InstructionSbb::InstructionSbb() : TwoOperandInstruction()
{
}

InstructionSbb::InstructionSbb(BYTE firstByte, BYTE secondByte, BYTE sFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataFlag, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, isDataFlag, sr, NULL, wFlag, sFlag, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionSbb::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getPrefixFlag()) {
		size += 1;
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* op = getSecondOperand();
		size += reinterpret_cast<DataOperand&>(op).getOperandSize();
	}
	return size;
}

void InstructionSbb::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionSbb::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
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

TwoOperandInstruction* InstructionSbb::clone()
{
	InstructionSbb* ptr = new InstructionSbb();
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
