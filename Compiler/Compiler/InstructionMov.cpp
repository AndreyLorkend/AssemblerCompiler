#include "InstructionMov.h"
#include "DataOperand.h"
#include "RegisterOperand.h"
#include "MemoryOperand.h"

InstructionMov::InstructionMov() : TwoOperandInstruction()
{
}

InstructionMov::InstructionMov(BYTE firstByte, BYTE secondByte, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, bool isDataPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, isDataPrefix, sr, NULL, wFlag, NULL, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

InstructionMov::InstructionMov(BYTE firstByte, BYTE secondByte, BYTE dFlag, BYTE wFlag, Operand* firstOperand, Operand* secondOperand, bool isPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, sr, dFlag, wFlag, NULL, NULL)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

InstructionMov::InstructionMov(BYTE firstByte, BYTE secondByte, BYTE wFlag, Operand* firstOperand, BYTE modFlag, Operand* secondOperand, bool isPrefix, SourceReciver sr)
	: TwoOperandInstruction(firstOperand, secondOperand, isPrefix, sr, NULL, wFlag, NULL, modFlag)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionMov::getInstructionSize()
{
	int size = sizeof(firstByte_) + sizeof(secondByte_);
	if (getSourceReciver() == REG_MEM) {
		size += 1;
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* op = getSecondOperand();
		size += 4;
	}
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionMov::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionMov::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	if (getSourceReciver() == REG_DATA) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		firstByte_ = firstByte_ | getFlagW();
		secondByte_ = secondByte_ | (dynamic_cast<RegisterOperand&>(*fop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(BYTE)) {
			DWORD32 data = static_cast<DWORD32>(dynamic_cast<DataOperand&>(*sop).getByteData());
			fout->write(reinterpret_cast<const char*>(&data), sizeof(DWORD32));
		}
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(WORD)) {
			WORD data = dynamic_cast<DataOperand&>(*sop).getWordData();
			fout->write(reinterpret_cast<const char*>(&data), sizeof(WORD));
		}
		if ((dynamic_cast<DataOperand&>(*sop).getOperandSize()) == sizeof(DWORD32)) {
			DWORD32 data = dynamic_cast<DataOperand&>(*sop).getDwordData();
			fout->write(reinterpret_cast<const char*>(&data), sizeof(DWORD));
		}
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << " " << dynamic_cast<DataOperand&>(*sop).getByteData() + 0x0 << endl;
	}
	if (getSourceReciver() == REG_REG) {
		Operand* fop = getFirstOperand();
		Operand* sop = getSecondOperand();
		BYTE dFlag = getFlagD();
		BYTE wFlag = getFlagW();
		firstByte_ = firstByte_ | (dFlag << 1) | wFlag;
		secondByte_ = secondByte_ | (dynamic_cast<RegisterOperand&>(*fop).getCode() << 3) | (dynamic_cast<RegisterOperand&>(*sop).getCode());
		fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
		fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
		cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
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

TwoOperandInstruction* InstructionMov::clone()
{
	InstructionMov* ptr = new InstructionMov();
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
