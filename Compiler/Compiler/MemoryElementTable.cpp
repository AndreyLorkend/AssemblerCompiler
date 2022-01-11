#include "MemoryElementTable.h"

void MemoryElementTable::addElement(string key, BYTE offset, BYTE length)
{
	MemoryElementParams params;
	params.offset = offset;
	params.length = length;
	table.insert(make_pair(key, params));
}

bool MemoryElementTable::findElementByKey(string key)
{
	map<string, MemoryElementParams>::iterator it = table.find(key);
	if (it == table.end() && table[key].offset == NULL) {
		return false;
	} else {
		return true;
	}
}

BYTE MemoryElementTable::getOffsetByKey(string key)
{
	return table[key].offset;
}

BYTE MemoryElementTable::getLengthByKey(string key)
{
	return table[key].length;
}
