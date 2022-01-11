#pragma once
#include "Block.h"

using namespace std;

class HeaderSection : public Block
{
private:
	WORD machine_;
	WORD numberOfSections_;
	__time32_t timeDateStamp_;
	DWORD32 pointerToSymbolTable_; //offset
	DWORD32 numberOfSymbols_;
	WORD sizeOfOptionalHeaders_;
	WORD characteristics_;
public:
	HeaderSection();
	~HeaderSection();
	bool initSection();
	bool writeToFile(ofstream* fout);
	//setters
	void setMachine(WORD machine);
	void setNumberOfSections(WORD numberOfSections);
	void setTimeDateStamp(__time32_t timeDateStamp);
	void setPointerToSymbolTable(DWORD32 pointerToSymbolTable);
	void setNumberOfSymbols(DWORD32 numberOfSymbols);
	void setSizeOfOptionalHeaders(WORD sizeOfOptionalHeaders);
	void setCharacteristics(WORD characteristics);
};

