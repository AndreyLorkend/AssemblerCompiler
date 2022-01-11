#pragma once
#include "AuxiliarySymbolRecord.h"
#define UNUSED_BYTES 3

using namespace std;

class AuxiliarySectionFormatRecord : public AuxiliarySymbolRecord
{
private:
	DWORD32 length_;
	WORD numberOfRelocations_;
	WORD numberOfLinenumbers_;
	DWORD32 checkSum_;
	WORD number_;
	BYTE selection_;
	BYTE unused_[UNUSED_BYTES];
public:
	AuxiliarySectionFormatRecord(DWORD length, WORD numberOfRelocations, WORD numberOfLinenumbers, DWORD32 checkSum, WORD number, BYTE selection);
	void writeToFile(ofstream* fout);
};

