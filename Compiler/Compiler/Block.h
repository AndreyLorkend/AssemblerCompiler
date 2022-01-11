#pragma once
#include <windows.h>
#include <fstream>
#include "SectionTypeTable.h"

using namespace std;

class Block
{
private:
	DWORD size_;
	SectionType sectionType_;
public:
	Block(DWORD size, SectionType sectionType);
	void setSize(DWORD size);
	DWORD getSize();
	SectionType getSectionType();
	virtual ~Block();
	virtual bool writeToFile(ofstream* fout) = 0;
	//virtual bool initSection();
};

