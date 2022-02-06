#pragma once
#include <string>
#include <map>
#include "InstructionAdd.h"
#include "InsctructionPush.h"
#include "InstructionMov.h"
#include "InstructionLodsw.h"
#include "InstructionJcc.h"
#include "InstructionJmp.h"
#include "InstructionRcl.h"
#include "InstructionRet.h"
#include "InstructionSbb.h"
#include "InstructionXor.h"
#include "InstructionCmp.h"
#define DATA_SOURCE 1
#define REG_SOURCE 2
#define MEM_SOURCE 3
#define REG_RECIVER 0
#define MEM_RECIVER 3

using namespace std;

enum TableType {
	NO_OPERAND_TABLE = 0,
	ONE_OPERAND_TABLE,
	TWO_OPERAND_TABLE
};

class InstructionsTable
{
private:
	multimap<string, NoOperandInstruction*> noOperandInstructions;
	multimap<string, SingleOperandInstruction*> oneOperandInstructions;
	multimap<string, TwoOperandInstruction*> twoOperandInstructions;
	void initTables();
	void addNoOperandInstruction(string name, NoOperandInstruction* instruction);
	void addSingleOperandInstruction(string name, SingleOperandInstruction* instruction);
	void addTwoOperandInstruction(string name, TwoOperandInstruction* instruction);
public:
	InstructionsTable();
	bool findElementByKey(string name, TableType type);
	NoOperandInstruction* getNoOperandInstructionByKey(string name, SourceReciver sr);
	SingleOperandInstruction* getSingleOperandInstructionByKey(string name, SourceReciver sr);
	TwoOperandInstruction* getTwoOperandInstructionByKey(string name, SourceReciver sr);
};

