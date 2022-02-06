#include "InstructionJmp.h"

InstructionJmp::InstructionJmp() : SingleOperandInstruction()
{
}

InstructionJmp::InstructionJmp(BYTE firstByte, BYTE disp8, Operand* operand, bool isPrefix, SourceReciver sr)
	: SingleOperandInstruction(operand, isPrefix, sr)
{
	firstByte_ = firstByte;
	disp8_ = disp8;
}

int InstructionJmp::getInstructionSize()
{
	return sizeof(firstByte_) + sizeof(disp8_);
}

void InstructionJmp::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << endl;
}

void InstructionJmp::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
	fout->write(reinterpret_cast<const char*>(&disp8_), sizeof(disp8_));
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << disp8_ + 0x0 << endl;
}

SingleOperandInstruction* InstructionJmp::clone()
{
	InstructionJmp* ptr = new InstructionJmp();
	ptr->firstByte_ = firstByte_;
	ptr->disp8_ = disp8_;
	ptr->setOperand(NULL);
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	if (getSourceReciver() == REG_DATA) {
		ptr->setDataFlag(true);
	}
	return ptr;
}
