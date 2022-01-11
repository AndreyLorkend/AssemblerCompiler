#include "AuxiliaryFileFormatRecord.h"

AuxiliaryFileFormatRecord::AuxiliaryFileFormatRecord(string fileName)
{
	fileName_ = fileName;
}

void AuxiliaryFileFormatRecord::writeToFile(ofstream* fout)
{
	if (fout->is_open()) {
		fout->write(reinterpret_cast<const char*>(fileName_.c_str()), sizeof(BYTE) * 18);
	}
}
