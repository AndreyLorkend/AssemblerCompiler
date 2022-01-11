#include "LabelTable.h"

void LabelTable::addElement(string name, int fromAddr, int toAddr)
{
	labelParams params;
	params.fromAddr = fromAddr;
	params.toAddr = toAddr;
	table.insert(make_pair(name, params));
}

int LabelTable::getFromAddrByKey(string key)
{
	return table[key].fromAddr;
}

int LabelTable::getToAddrByKey(string key)
{
	return table[key].toAddr;
}

bool LabelTable::findElementByKey(string key)
{
	if (table.find(key) == table.end()) {
		return false;
	} else {
		return true;
	}
}

map<string, labelParams> LabelTable::getTable()
{
	return table;
}

void LabelTable::setFromAddrByKey(string key, int value)
{
	table[key].fromAddr = value;
}

void LabelTable::setToAddrByKey(string key, int value)
{
	table[key].toAddr = value;
}
