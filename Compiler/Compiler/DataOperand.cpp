#include "DataOperand.h"

DataOperand::DataOperand(BYTE data)
{
	byteData_ = data;
	wordData_ = NULL;
	dwordData_ = NULL;
}

DataOperand::DataOperand(WORD data)
{
	byteData_ = NULL;
	wordData_ = data;
	dwordData_ = NULL;
}

DataOperand::DataOperand(DWORD32 data)
{
	byteData_ = NULL;
	wordData_ = NULL;
	dwordData_ = data;
}

BYTE DataOperand::getDataOperand()
{
	return byteData_;
}

int DataOperand::getOperandSize()
{
	if (byteData_ != NULL) {
		return sizeof(BYTE);
	}
	if (wordData_ != NULL) {
		return sizeof(WORD);
	}
	if (dwordData_ != NULL) {
		return sizeof(DWORD32);
	}
}

BYTE DataOperand::getCode()
{
	return 0;
}

BYTE DataOperand::getByteData()
{
	return byteData_;
}

BYTE DataOperand::getWordData()
{
	return wordData_;
}

BYTE DataOperand::getDwordData()
{
	return dwordData_;
}
