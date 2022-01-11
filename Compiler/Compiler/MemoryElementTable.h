#pragma once
#include <map>
#include <string>
#include <windows.h>

using namespace std;

struct MemoryElementParams {
	BYTE offset;
	BYTE length;
};

class MemoryElementTable
{
private:
	map<string, MemoryElementParams> table; //string - key element, int - offset
public:
	void addElement(string key, BYTE offset, BYTE length);
	bool findElementByKey(string key);
	BYTE getOffsetByKey(string key);
	BYTE getLengthByKey(string key);
};

