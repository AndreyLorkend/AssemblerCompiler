#include "InstructionJcc.h"

InstructionJcc::InstructionJcc() : SingleOperandInstruction()
{
}

InstructionJcc::InstructionJcc(BYTE firstByte, BYTE tttnFlag, BYTE disp8, Operand* operand, bool isPrefix, SourceReciver sr)
	: SingleOperandInstruction(operand, isPrefix, sr)
{
	firstByte_ = firstByte;
	tttnFlag_ = tttnFlag;
	disp8_ = disp8;
}

int InstructionJcc::getInstructionSize()
{
	return sizeof(firstByte_) + sizeof(disp8_);
}

void InstructionJcc::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << endl;
}

void InstructionJcc::writeToFile(ofstream* fout)
{
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	firstByte_ = firstByte_ | tttnFlag_;
	fout->write(reinterpret_cast<const char*>(&firstByte_), sizeof(firstByte_));
	fout->write(reinterpret_cast<const char*>(&disp8_), sizeof(disp8_));
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << " " << disp8_ + 0x0 << endl;
}

SingleOperandInstruction* InstructionJcc::clone()
{
	InstructionJcc* ptr = new InstructionJcc();
	ptr->firstByte_ = firstByte_;
	ptr->tttnFlag_ = tttnFlag_;
	ptr->disp8_ = disp8_;
	ptr->setOperand(NULL);
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	if (getSourceReciver() == REG_DATA) {
		ptr->setDataFlag(true);
	}
	return ptr;
}
