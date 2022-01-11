#pragma once
#include <string>
#include <map>
#include "InstructionCode.h"
#define DATA_SOURCE 1
#define REG_SOURCE 2
#define MEM_SOURCE 3
#define REG_RECIVER 0
#define MEM_RECIVER 3

using namespace std;

enum SourceReciver {
	NO_SOURCE_RECIVER = 0,
	REG_DATA = 1,
	REG_REG = 2,
	REG_MEM = 3,
	MEM_REG = 4,
	MEM_DATA = 5
};


enum TableType {
	NO_OPERAND_TABLE = 0,
	ONE_OPERAND_TABLE,
	TWO_OPERAND_TABLE
};

struct InstructionParams {
	BYTE firstByteCode;
	BYTE secondByteCode;
	SourceReciver sourceReciverType;
};

class InstructionsTable
{
private:
	multimap<string, InstructionParams> noOperandInstructions;
	multimap<string, InstructionParams> oneOperandInstructions;
	multimap<string, InstructionParams> twoOperandInstructions;
	void initTables();
	void addInstruction(string name, BYTE fbcode, BYTE sbcode, SourceReciver sourceReciverType, multimap<string, InstructionParams>& table);
public:
	InstructionsTable();
	bool findElementByKey(string name, TableType type);
	InstructionCode getInstrucrionCode(string name, TableType type, SourceReciver sourceReciverType);
};

