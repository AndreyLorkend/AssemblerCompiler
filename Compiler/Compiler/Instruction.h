#pragma once
#include "InstructionCode.h"
#include "Operand.h"
#include "InstructionsTable.h"

class Instruction
{
private:
	InstructionCode instructionCode_;
	BYTE prefix16bits_;
	bool isPrefixUsed;
	bool isData_;
	int data_;
	SourceReciver sourceReciver;
public:
	Instruction(InstructionCode instructionCode, bool flag, bool dataFlag, int data, SourceReciver sr);
	void setPrefixFlag(bool flag);
	bool getPrefixFlag();
	void setSecondByte(BYTE sbyte);
	InstructionCode getInstructionCode();
	virtual ~Instruction();
	int getData();
	bool getDataFlag();
	void setSourceReciver(SourceReciver sr);
	SourceReciver getSourceReciver();
};

