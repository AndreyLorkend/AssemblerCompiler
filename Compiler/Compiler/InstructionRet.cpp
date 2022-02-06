#include "InstructionRet.h"

InstructionRet::InstructionRet() : NoOperandInstruction()
{
}

InstructionRet::InstructionRet(BYTE firstByte, bool isPrefix, SourceReciver sr)
	: NoOperandInstruction(isPrefix, sr)
{
	firstByte_ = firstByte;
	secondByte_ = 0;
}

InstructionRet::InstructionRet(BYTE firstByte, BYTE secondByte, bool isPrefix, SourceReciver sr)
	: NoOperandInstruction(isPrefix, sr)
{
	firstByte_ = firstByte;
	secondByte_ = secondByte;
}

int InstructionRet::getInstructionSize()
{
	return sizeof(firstByte_) + sizeof(secondByte_);
}

void InstructionRet::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

void InstructionRet::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
	fout->write(reinterpret_cast<const char*>(&secondByte_), sizeof(secondByte_));
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << secondByte_ + 0x0 << endl;
}

NoOperandInstruction* InstructionRet::clone()
{
	InstructionRet* ptr = new InstructionRet();
	ptr->firstByte_ = firstByte_;
	ptr->secondByte_ = secondByte_;
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	return ptr;
}
