#include "InstructionsTable.h"

void InstructionsTable::initTables()
{
	//No operand instructions
	addInstruction("lodsw", 0x66, 0xAD, NO_SOURCE_RECIVER, noOperandInstructions);
	addInstruction("ret", 0xC9, 0xC3, NO_SOURCE_RECIVER, noOperandInstructions);
	//One operand instructions
	addInstruction("jg", 0x7F, 0x00, NO_SOURCE_RECIVER, oneOperandInstructions);
	addInstruction("jmp", 0xEB, 0x00, NO_SOURCE_RECIVER, oneOperandInstructions);
	//Two operand instructions
	addInstruction("mov", 0xC6, 0xC0, REG_DATA, twoOperandInstructions);
	addInstruction("mov", 0x8A, 0xC0, REG_REG, twoOperandInstructions);
	addInstruction("mov", 0x8A, 0x00, REG_MEM, twoOperandInstructions);
	addInstruction("xor", 0x32, 0xC0, REG_REG, twoOperandInstructions);
	addInstruction("rcl", 0xC0, 0xD0, REG_DATA, twoOperandInstructions);
	addInstruction("sbb", 0x82, 0xD8, REG_DATA, twoOperandInstructions);
	addInstruction("add", 0x02, 0xC0, REG_REG, twoOperandInstructions);
	addInstruction("add", 0x82, 0xC0, REG_DATA, twoOperandInstructions);
	addInstruction("cmp", 0x3A, 0x00, REG_MEM, twoOperandInstructions);
	
}

void InstructionsTable::addInstruction(string name, BYTE fbcode, BYTE sbcode, SourceReciver sourceReciverType, multimap<string, InstructionParams>& table)
{
	InstructionParams params;
	params.firstByteCode = fbcode;
	params.secondByteCode = sbcode;
	params.sourceReciverType = sourceReciverType;
	table.insert(make_pair(name, params));
}

InstructionsTable::InstructionsTable()
{
	initTables();
}

bool InstructionsTable::findElementByKey(string name, TableType type)
{
	switch (type)
	{
	case NO_OPERAND_TABLE:
		if (noOperandInstructions.find(name) == noOperandInstructions.end()) {
			return false;
		} else {
			return true;
		}
		break;
	case ONE_OPERAND_TABLE:
		if (oneOperandInstructions.find(name) == oneOperandInstructions.end()) {
			return false;
		} else {
			return true;
		}
		break;
	case TWO_OPERAND_TABLE:
		if (twoOperandInstructions.find(name) == twoOperandInstructions.end()) {
			return false;
		} else {
			return true;
		}
		break;
	default:
		return false;
		break;
	}
}

InstructionCode InstructionsTable::getInstrucrionCode(string name, TableType type, SourceReciver sourceReciverType)
{
	switch (type)
	{
	case NO_OPERAND_TABLE:
		for (auto el = noOperandInstructions.begin(); el != noOperandInstructions.end(); el++) {
			if (el->first == name && el->second.sourceReciverType == sourceReciverType) {
				return InstructionCode({ el->second.firstByteCode, el->second.secondByteCode });
			}
		}
		break;
	case ONE_OPERAND_TABLE:
		for (auto el = oneOperandInstructions.begin(); el != oneOperandInstructions.end(); el++) {
			if (el->first == name && el->second.sourceReciverType == sourceReciverType) {
				return InstructionCode({ el->second.firstByteCode, el->second.secondByteCode });
			}
		}
		break;
	case TWO_OPERAND_TABLE:
		for (auto el = twoOperandInstructions.begin(); el != twoOperandInstructions.end(); el++) {
			if (el->first == name && el->second.sourceReciverType == sourceReciverType) {
				return InstructionCode({ el->second.firstByteCode, el->second.secondByteCode });
			}
		}
		break;
	default:
		break;
	}
}
