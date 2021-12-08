#pragma once

#include "Block.h"

class HeaderSection : public Block
{
private:
	WORD machine;
	BYTE numberOfSections;
	__time32_t timeDateStamp;
	DWORD32 pointerToSymbolTable; //offset
	DWORD32 numberOfSymbols;
	WORD sizeOfOptionalHeaders;
	WORD characteristics;
public:
};

