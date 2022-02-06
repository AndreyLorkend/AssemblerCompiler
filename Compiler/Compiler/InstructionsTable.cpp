#include "InstructionsTable.h"

void InstructionsTable::initTables()
{
	//No operand instructions
	addNoOperandInstruction("lodsw", new InstructionLodsw(0xAD, true, NO_SOURCE_RECIVER));
	addNoOperandInstruction("ret", new InstructionRet(0xC9, 0xC3, false, NO_SOURCE_RECIVER));
	//One operand instructions
	addSingleOperandInstruction("jg", new InstructionJcc(0x70, 0x0F, 0x00, NULL, false, NO_SOURCE_RECIVER));
	addSingleOperandInstruction("jmp", new InstructionJmp(0xEB, 0x00, NULL, false, NO_SOURCE_RECIVER));
	addSingleOperandInstruction("push", new InsctructionPush(0x50, NULL, false, NO_SOURCE_RECIVER));
	//Two operand instructions
	addTwoOperandInstruction("mov", new InstructionMov(0xC6, 0xC0, 0, NULL, NULL, false, true, REG_DATA));
	addTwoOperandInstruction("mov", new InstructionMov(0x88, 0xC0, (BYTE)0, (BYTE)0, NULL, NULL, false, REG_REG));
	addTwoOperandInstruction("mov", new InstructionMov(0x8A, 0x00, 0, NULL, 1, NULL, false, REG_MEM));
	addTwoOperandInstruction("xor", new InstructionXor(0x30, 0xC0, 0, 0, NULL, NULL, false, REG_REG));
	addTwoOperandInstruction("rcl", new InstructionRcl(0xC0, 0x10, 0, 3, NULL, NULL, false, true, REG_DATA));
	addTwoOperandInstruction("sbb", new InstructionSbb(0x80, 0xD8, 0, 0, NULL, NULL, false, true, REG_DATA));
	addTwoOperandInstruction("add", new InstructionAdd(0x00, 0xC0, 0, 0, NULL, NULL, false, REG_REG));
	addTwoOperandInstruction("add", new InstructionAdd(0x80, 0xC0, 0, 0, NULL, NULL, false, true, REG_DATA));
	addTwoOperandInstruction("cmp", new InstructionCmp(0x3A, 0x00, 0, 1, NULL, NULL, false, REG_MEM));
}

void InstructionsTable::addNoOperandInstruction(string name, NoOperandInstruction* instruction)
{
	noOperandInstructions.insert(make_pair(name, instruction));
}

void InstructionsTable::addSingleOperandInstruction(string name, SingleOperandInstruction* instruction)
{
	oneOperandInstructions.insert(make_pair(name, instruction));
}

void InstructionsTable::addTwoOperandInstruction(string name, TwoOperandInstruction* instruction)
{
	twoOperandInstructions.insert(make_pair(name, instruction));
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

NoOperandInstruction* InstructionsTable::getNoOperandInstructionByKey(string name, SourceReciver sr)
{
	for (auto el : noOperandInstructions) {
		if (el.second->getSourceReciver() == sr && el.first == name) {
			return el.second;
		}
	}
	return NULL;
}

SingleOperandInstruction* InstructionsTable::getSingleOperandInstructionByKey(string name, SourceReciver sr)
{
	for (auto el : oneOperandInstructions) {
		if (el.second->getSourceReciver() == sr && el.first == name) {
			return el.second;
		}
	}
	return NULL;
}

TwoOperandInstruction* InstructionsTable::getTwoOperandInstructionByKey(string name, SourceReciver sr)
{
	for (auto el : twoOperandInstructions) {
		if (el.second->getSourceReciver() == sr && el.first == name) {
			return el.second;
		}
	}
	return NULL;
}
