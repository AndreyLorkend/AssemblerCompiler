#include "InsctructionPush.h"
#include "RegisterOperand.h"

InsctructionPush::InsctructionPush() : SingleOperandInstruction()
{
}

InsctructionPush::InsctructionPush(BYTE firstByte, Operand* operand, bool prefixFlag, SourceReciver sr)
	: SingleOperandInstruction(operand, prefixFlag, sr)
{
	firstByte_ = firstByte;
}

int InsctructionPush::getInstructionSize()
{
	int size = sizeof(firstByte_);
	if (getPrefixFlag()) {
		size += 1;
	}
	return size;
}

void InsctructionPush::showInstructionCode()
{
	cout << hex << getPrefix() + 0x0 << " " << firstByte_ + 0x0 << endl;
}

void InsctructionPush::writeToFile(ofstream* fout)
{
	Operand* op = getOperand();
	BYTE code = (dynamic_cast<RegisterOperand&>(*op)).getCode();
	BYTE instr = firstByte_ | code;
	if (getPrefixFlag()) {
		BYTE prefix = getPrefix();
		fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
	}
	fout->write(reinterpret_cast<const char*>(&instr), sizeof(instr));
	cout << hex << getPrefix() + 0x0 << " " << (instr + 0x0) << endl;
}

SingleOperandInstruction* InsctructionPush::clone()
{
	InsctructionPush* ptr = new InsctructionPush();
	ptr->firstByte_ = firstByte_;
	ptr->setOperand(NULL);
	ptr->setPrefixFlag(false);
	ptr->setSourceReciver(getSourceReciver());
	if (getSourceReciver() == REG_DATA) {
		ptr->setDataFlag(true);
	}
	return ptr;
}
