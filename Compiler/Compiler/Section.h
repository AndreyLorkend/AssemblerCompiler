#pragma once
#include "Block.h"
#include <vector>
#include <string>
#include "Instruction.h"

using namespace std;

class Section : public Block
{
private:
	// Section headers
	string name_; // записывать только 8 байт
	DWORD32 virtualSize_; // размер raw data сегмента .code 
	DWORD32 virtualAddress_;
	DWORD32 sizeOfRawData_;
	DWORD32 pointerToRawData_;
	DWORD32 pointerToRelocations_;
	DWORD32 pointerToLinenumbers_;
	WORD numberOfRelocations_;
	WORD numberOfLineNumbers_;
	DWORD32 characteristics_;
	// Raw data
	vector <Instruction*> rawData_;
public:
	Section(SectionType sectionType);
	bool writeToFile(ofstream* fout);
	bool initSection(
		string name, 
		DWORD32 virtualSize,
		DWORD32 virtualAddress,
		DWORD32 sizeOfRawData,
		DWORD32 pointerToRawData,
		DWORD32 pointerToRelocations,
		DWORD32 pointerToLinenumbers,
		WORD numberOfRelocations,
		WORD numberOfLineNumbers,
		DWORD32 characteristics
	);
	void writeRawData(ofstream* fout);
	void setName(string name);
	void setPointerToRawData(DWORD32 pointerToRawData);
	void setSizeOfRawData(DWORD32 sizeOfRawData);
	void addRawDataElement(Instruction* element);
	void setVirtualSize(DWORD32 value);
	string getName();
	DWORD32 getSizeOfRawData();
	WORD getNumberOfRelocations();
	WORD getNumberOfLineNumber();
};

