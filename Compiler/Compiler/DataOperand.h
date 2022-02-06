#pragma once
#include "Operand.h"

class DataOperand : public Operand
{
private:
	BYTE byteData_;
	WORD wordData_;
	DWORD32 dwordData_;
public:
	DataOperand(BYTE data);
	DataOperand(WORD data);
	DataOperand(DWORD32 data);
	BYTE getDataOperand();
	int getOperandSize();
	BYTE getCode();
	BYTE getByteData();
	BYTE getWordData();
	BYTE getDwordData();
};



