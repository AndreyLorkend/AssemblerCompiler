#pragma once
#include "AuxiliarySymbolRecord.h"

using namespace std;

class AuxiliaryFileFormatRecord : public AuxiliarySymbolRecord
{
private:
	string fileName_; // write only 18 bytes
public:
	AuxiliaryFileFormatRecord(string fileName);
	void writeToFile(ofstream* fout);
};

