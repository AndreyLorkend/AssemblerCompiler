#pragma once
#include "Operand.h"
#include <fstream>
#include <iostream>

using namespace std;

enum SourceReciver {
	NO_SOURCE_RECIVER = 0,
	REG_DATA = 1,
	REG_REG = 2,
	REG_MEM = 3,
	MEM_REG = 4,
	MEM_DATA = 5
};

class Instruction
{
private:
	BYTE prefix16bits_;
	bool isPrefixUsed_;
	bool isDataFlag_;
	SourceReciver sourceReciver_;
public:
	Instruction();
	Instruction(bool flag, SourceReciver sr);
	Instruction(bool flag, bool dataFlag, SourceReciver sr);
	void setPrefixFlag(bool flag);
	void setDataFlag(bool flag);
	bool getPrefixFlag();
	bool getDataFlag();
	virtual ~Instruction();
	virtual int getInstructionSize() = 0;
	virtual void showInstructionCode() = 0;
	virtual void writeToFile(ofstream* fout) = 0;
	void setSourceReciver(SourceReciver sr);
	SourceReciver getSourceReciver();
	BYTE getPrefix();
};

