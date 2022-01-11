#include "AuxiliarySectionFormatRecord.h"

AuxiliarySectionFormatRecord::AuxiliarySectionFormatRecord(DWORD length, WORD numberOfRelocations, WORD numberOfLinenumbers, DWORD32 checkSum, WORD number, BYTE section)
{
	length_ = length;
	numberOfRelocations_ = numberOfRelocations;
	numberOfLinenumbers_ = numberOfLinenumbers;
	checkSum_ = checkSum;
	number_ = number;
	selection_ = section;
	for (int i = 0; i < UNUSED_BYTES; i++) {
		unused_[i] = 0;
	}
}

void AuxiliarySectionFormatRecord::writeToFile(ofstream* fout)
{
	if (fout->is_open()) {
		fout->write(reinterpret_cast<const char*>(&length_), sizeof(length_));
		fout->write(reinterpret_cast<const char*>(&numberOfRelocations_), sizeof(numberOfRelocations_));
		fout->write(reinterpret_cast<const char*>(&numberOfLinenumbers_), sizeof(numberOfLinenumbers_));
		fout->write(reinterpret_cast<const char*>(&checkSum_), sizeof(checkSum_));
		fout->write(reinterpret_cast<const char*>(&number_), sizeof(number_));
		fout->write(reinterpret_cast<const char*>(&selection_), sizeof(selection_));
		for (int i = 0; i < UNUSED_BYTES; i++) {
			fout->write(reinterpret_cast<const char*>(&unused_[i]), sizeof(unused_[i]));
		}
	}
}
