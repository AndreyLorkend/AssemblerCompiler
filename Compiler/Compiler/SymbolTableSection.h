#pragma once
#include "Block.h"
#include "AuxiliarySymbolRecord.h"
#include "AuxiliaryFileFormatRecord.h"
#include "AuxiliarySectionFormatRecord.h"

class SymbolTableSection : public Block
{
private:
	string name_; // write only 8 bytes
	DWORD32 value_;
	WORD sectionNumber_;
	WORD type_;
	BYTE storageClass_;
	BYTE numberOfAuxSymbols_;
	AuxiliarySymbolRecord* auxiliarySymbolRecord;
public:
	SymbolTableSection();
	SymbolTableSection(string name, DWORD32 value, WORD sectionNumber, WORD type, BYTE storageClass, BYTE numbersOfAuxSymbols);
	SymbolTableSection(string name, DWORD32 value, WORD sectionNumber, WORD type, BYTE storageClass, BYTE numbersOfAuxSymbols, AuxiliarySymbolRecord* record);
	~SymbolTableSection();
	bool writeToFile(ofstream* fout);
	void addAux(AuxiliarySymbolRecord* record);
	string getName();
	BYTE getNumberOfAuxSymbols();
};
