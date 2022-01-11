#pragma once
#include "Operand.h"

class DataOperand : public Operand
{
private:
	BYTE data_;
public:
	DataOperand(BYTE data);
	BYTE getDataOperand();
};



