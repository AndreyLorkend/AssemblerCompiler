#include "InstructionLodsw.h"

InstructionLodsw::InstructionLodsw() : NoOperandInstruction()
{
}

InstructionLodsw::InstructionLodsw(BYTE firstByte, bool isPrefix, SourceReciver sr)
	: NoOperandInstruction(isPrefix, sr)
{
	firstByte_ = firstByte;
}

int InstructionLodsw::getInstructionSize()
{
	int size = sizeof(firstByte_);
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InstructionLodsw::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << endl;
}

void InstructionLodsw::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << endl;
}

NoOperandInstruction* InstructionLodsw::clone()
{
	InstructionLodsw* ptr = new InstructionLodsw();
	ptr->firstByte_ = firstByte_;
	ptr->setPrefixFlag(true);
	ptr->setSourceReciver(getSourceReciver());
	return ptr;
}
