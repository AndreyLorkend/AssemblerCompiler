#pragma once
#include <windows.h>
#include <map>
#include <string>

using namespace std;

struct labelParams {
	int fromAddr;
	int toAddr;
};

class LabelTable
{
private:
	map<string, labelParams> table;
public:
	void addElement(string name, int fromAddr, int toAddr);
	int getFromAddrByKey(string key);
	int getToAddrByKey(string key);
	bool findElementByKey(string key);
	map<string, labelParams> getTable();
	void setFromAddrByKey(string key, int value);
	void setToAddrByKey(string key, int value);
};

