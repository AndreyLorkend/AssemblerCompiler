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
	for (auto el : table) {
		if (el.first == key) {
			return true;
		}
	}
	return false;
}

BYTE MemoryElementTable::getOffsetByKey(string key)
{
	return table[key].offset;
}

BYTE MemoryElementTable::getLengthByKey(string key)
{
	return table[key].length;
}
