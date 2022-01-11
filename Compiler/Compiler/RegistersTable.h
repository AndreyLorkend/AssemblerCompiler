#pragma once
#include <map>
#include <string>
#include <windows.h>

using namespace std;

struct RegisterParams {

	BYTE code;
	BYTE length;
};

class RegistersTable
{
private:
	map<string, RegisterParams> table;
	void initTable();
	void addRegister(string name, BYTE code, BYTE length);
public:
	RegistersTable();
	bool findRegisterElementByKey(string key);
	BYTE getCodeByKey(string key);
	BYTE getLengthByKey(string key);
};

