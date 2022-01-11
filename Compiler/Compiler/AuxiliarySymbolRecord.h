#pragma once
#include <windows.h>
#include <string>
#include <fstream>
//base class

using namespace std;

class AuxiliarySymbolRecord
{
private:
public:
	virtual void writeToFile(ofstream* fout) = 0;
	virtual ~AuxiliarySymbolRecord();
};

