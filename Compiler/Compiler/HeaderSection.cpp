#include "HeaderSection.h"
#include <time.h>
#include <iostream>

HeaderSection::HeaderSection() : Block(20, HEADER_SECTION) // по умолчанию header секция занимает 20 байт
{

}

HeaderSection::~HeaderSection()
{
}

bool HeaderSection::initSection()
{
	machine_ = 0;
	numberOfSections_ = 0;
	timeDateStamp_ = time(0);
	pointerToSymbolTable_ = 0;
	numberOfSymbols_ = 0;
	sizeOfOptionalHeaders_ = 0;
	characteristics_ = 0;
	return true;
}

bool HeaderSection::writeToFile(ofstream* fout)
{
	if (fout->is_open()) {
		fout->write(reinterpret_cast<const char*>(&machine_), sizeof(machine_));
		fout->write(reinterpret_cast<const char*>(&numberOfSections_), sizeof(numberOfSections_));
		fout->write(reinterpret_cast<const char*>(&timeDateStamp_), sizeof(timeDateStamp_));
		fout->write(reinterpret_cast<const char*>(&pointerToSymbolTable_), sizeof(pointerToSymbolTable_));
		fout->write(reinterpret_cast<const char*>(&numberOfSymbols_), sizeof(numberOfSymbols_));
		fout->write(reinterpret_cast<const char*>(&sizeOfOptionalHeaders_), sizeof(sizeOfOptionalHeaders_));
		fout->write(reinterpret_cast<const char*>(&characteristics_), sizeof(characteristics_));
	}
	return false;
}

void HeaderSection::setMachine(WORD machine)
{
	machine_ = machine;
}

void HeaderSection::setNumberOfSections(WORD numberOfSections)
{
	numberOfSections_ = numberOfSections;
}

void HeaderSection::setTimeDateStamp(__time32_t timeDateStamp)
{
	timeDateStamp_ = timeDateStamp;
}

void HeaderSection::setPointerToSymbolTable(DWORD32 pointerToSymbolTable)
{
	pointerToSymbolTable_ = pointerToSymbolTable;
}

void HeaderSection::setNumberOfSymbols(DWORD32 numberOfSymbols)
{
	numberOfSymbols_ = numberOfSymbols;
}

void HeaderSection::setSizeOfOptionalHeaders(WORD sizeOfOptionalHeaders)
{
	sizeOfOptionalHeaders_ = sizeOfOptionalHeaders;
}

void HeaderSection::setCharacteristics(WORD characteristics)
{
	characteristics_ = characteristics;
}
