#pragma once
#include "Block.h"

using namespace std;

class Section : public Block
{
private:
	// Section headers
	char name[8]; // поменять
	DWORD32 virtualSize;
	DWORD32 virtualAddress;
	DWORD32 sizeOfRawData;
	DWORD32 pointerToRawData;
	DWORD32 pointerToRelocations;
	WORD numberOfRelocations;
	WORD numberOfLinenumbers;
	DWORD32 characteristics;
	// Section flags
	// 
	// Raw data
	vector<BYTE> rawData;
public:
	Section();
};

