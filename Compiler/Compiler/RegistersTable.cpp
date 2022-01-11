#include "RegistersTable.h"

void RegistersTable::initTable()
{
	//32bits registers
	addRegister("eax", 0x0, 32);
	addRegister("ecx", 0x1, 32);
	addRegister("edx", 0x2, 32);
	addRegister("ebx", 0x3, 32);
	addRegister("esp", 0x4, 32);
	addRegister("ebp", 0x5, 32);
	addRegister("esi", 0x6, 32);
	addRegister("edi", 0x7, 32);
	//16bits registers
	addRegister("ax", 0x0, 16);
	addRegister("cx", 0x1, 16);
	addRegister("dx", 0x2, 16);
	addRegister("bx", 0x3, 16);
	addRegister("sp", 0x4, 16);
	addRegister("bp", 0x5, 16);
	addRegister("si", 0x6, 16);
	addRegister("di", 0x7, 16);
	//8bits registers
	addRegister("al", 0x0, 8);
	addRegister("cl", 0x1, 8);
	addRegister("dl", 0x2, 8);
	addRegister("bl", 0x3, 8);
	addRegister("ah", 0x4, 8);
	addRegister("ch", 0x5, 8);
	addRegister("dh", 0x6, 8);
	addRegister("bh", 0x7, 8);
}

void RegistersTable::addRegister(string name, BYTE code, BYTE length)
{
	RegisterParams tempParams;
	tempParams.code = code;
	tempParams.length = length;
	table.insert(make_pair(name, tempParams));
}

RegistersTable::RegistersTable()
{
	initTable();
}

bool RegistersTable::findRegisterElementByKey(string key)
{
	if (table.find(key) == table.end()) {
		return false;
	} else {
		return true;
	}
}

BYTE RegistersTable::getCodeByKey(string key)
{
	return table[key].code;
}

BYTE RegistersTable::getLengthByKey(string key)
{
	return table[key].length;
}
