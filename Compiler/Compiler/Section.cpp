#include "Section.h"
#include <vector>

Section::Section(SectionType sectionType) : Block(40, sectionType) // по умолчанию размер секции 40 байт
{
}

bool Section::writeToFile(ofstream* fout)
{
    BYTE align = 0x0;
    if (fout->is_open()) {
        fout->write(reinterpret_cast<const char*>(name_.c_str()), sizeof(BYTE)*8);
        fout->write(reinterpret_cast<const char*>(&virtualSize_), sizeof(virtualSize_));
        fout->write(reinterpret_cast<const char*>(&virtualAddress_), sizeof(virtualAddress_));
        fout->write(reinterpret_cast<const char*>(&sizeOfRawData_), sizeof(sizeOfRawData_));
        fout->write(reinterpret_cast<const char*>(&pointerToRawData_), sizeof(pointerToRawData_));
        fout->write(reinterpret_cast<const char*>(&pointerToRelocations_), sizeof(pointerToRelocations_));
        fout->write(reinterpret_cast<const char*>(&pointerToLinenumbers_), sizeof(pointerToLinenumbers_));
        fout->write(reinterpret_cast<const char*>(&numberOfRelocations_), sizeof(numberOfRelocations_));
        fout->write(reinterpret_cast<const char*>(&numberOfLineNumbers_), sizeof(numberOfLineNumbers_));
        fout->write(reinterpret_cast<const char*>(&characteristics_), sizeof(characteristics_));
    }
    return false;
}

bool Section::initSection(
    string name,
    DWORD32 virtualSize,
    DWORD32 virtualAddress,
    DWORD32 sizeOfRawData,
    DWORD32 pointerToRawData,
    DWORD32 pointerToRelocations,
    DWORD32 pointerToLinenumbers,
    WORD numberOfRelocations,
    WORD numberOfLineNumbers,
    DWORD32 characteristics)
{
    name_ = name;
    virtualSize_ = virtualSize;
    virtualAddress_ = virtualAddress;
    sizeOfRawData_ = sizeOfRawData;
    pointerToRawData_ = pointerToRawData;
    pointerToRelocations_ = pointerToRelocations;
    pointerToLinenumbers_ = pointerToLinenumbers;
    numberOfRelocations_ = numberOfRelocations;
    numberOfLineNumbers_ = numberOfLineNumbers;
    characteristics_ = characteristics;
    return true;
}

void Section::writeRawData(ofstream* fout)
{
    if (sizeOfRawData_ != 0) {
        for (auto el : rawData_) {
            BYTE fByte = el->getInstructionCode().firstByte;
            BYTE sByte = el->getInstructionCode().secondByte;
            int data = el->getData();
            BYTE prefix = 0x66;
            if (el->getPrefixFlag()) {
                fout->write(reinterpret_cast<const char*>(&prefix), sizeof(prefix));
            }
            fout->write(reinterpret_cast<const char*>(&fByte), sizeof(fByte));
            if (el->getInstructionCode().secondByte != 0) {
                fout->write(reinterpret_cast<const char*>(&sByte), sizeof(sByte));
            }
            if (el->getDataFlag()) {
                if (el->getSourceReciver() == REG_MEM) {
                    fout->write(reinterpret_cast<const char*>(&data), sizeof(BYTE));
                }
                if (el->getSourceReciver() == REG_DATA) {
                    fout->write(reinterpret_cast<const char*>(&data), sizeof(int));
                }
            }
        }
    }
}

void Section::setName(string name)
{
    name_ = name;
}

void Section::setPointerToRawData(DWORD32 pointerToRawData)
{
    pointerToRawData_ = pointerToRawData;
}

void Section::setSizeOfRawData(DWORD32 sizeOfRawData)
{
    sizeOfRawData_ = sizeOfRawData;
}

void Section::addRawDataElement(Instruction* element)
{
    rawData_.push_back(element);
}

void Section::setVirtualSize(DWORD32 value)
{
    virtualSize_ = value;
}

string Section::getName()
{
    return name_;
}

DWORD32 Section::getSizeOfRawData()
{
    return sizeOfRawData_;
}

WORD Section::getNumberOfRelocations()
{
    return numberOfRelocations_;
}

WORD Section::getNumberOfLineNumber()
{
    return numberOfLineNumbers_;
}
