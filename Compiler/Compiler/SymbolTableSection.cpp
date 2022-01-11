#include "SymbolTableSection.h"

SymbolTableSection::SymbolTableSection() : Block(0, SYMBOL_TABLE_SECTION)
{
    auxiliarySymbolRecord = NULL;
}

SymbolTableSection::SymbolTableSection(string name, DWORD32 value, WORD sectionNumber, WORD type, BYTE storageClass, BYTE numbersOfAuxSymbols)
    : Block(0, SYMBOL_TABLE_SECTION)
{
    name_ = name;
    value_ = value;
    sectionNumber_ = sectionNumber;
    type_ = type;
    storageClass_ = storageClass;
    numberOfAuxSymbols_ = numbersOfAuxSymbols;
    auxiliarySymbolRecord = NULL;
}

SymbolTableSection::SymbolTableSection(string name, DWORD32 value, WORD sectionNumber, WORD type, BYTE storageClass, BYTE numbersOfAuxSymbols, AuxiliarySymbolRecord* record)
    : Block(0, SYMBOL_TABLE_SECTION)
{
    name_ = name;
    value_ = value;
    sectionNumber_ = sectionNumber;
    type_ = type;
    storageClass_ = storageClass;
    numberOfAuxSymbols_ = numbersOfAuxSymbols;
    auxiliarySymbolRecord = record;
}

bool SymbolTableSection::writeToFile(ofstream* fout)
{
    if (fout->is_open()) {
        fout->write(reinterpret_cast<const char*>(name_.c_str()), sizeof(BYTE) * 8);
        fout->write(reinterpret_cast<const char*>(&value_), sizeof(value_));
        fout->write(reinterpret_cast<const char*>(&sectionNumber_), sizeof(sectionNumber_));
        fout->write(reinterpret_cast<const char*>(&type_), sizeof(type_));
        fout->write(reinterpret_cast<const char*>(&storageClass_), sizeof(storageClass_));
        fout->write(reinterpret_cast<const char*>(&numberOfAuxSymbols_), sizeof(numberOfAuxSymbols_));
        if (auxiliarySymbolRecord != NULL) {
            auxiliarySymbolRecord->writeToFile(fout);
        }
    }
    return false;
}

void SymbolTableSection::addAux(AuxiliarySymbolRecord* record)
{
    auxiliarySymbolRecord = record;
}

string SymbolTableSection::getName()
{
    return name_;
}

BYTE SymbolTableSection::getNumberOfAuxSymbols()
{
    return numberOfAuxSymbols_;
}

SymbolTableSection::~SymbolTableSection()
{
    if (auxiliarySymbolRecord == NULL) {
        delete auxiliarySymbolRecord;
    }
}
