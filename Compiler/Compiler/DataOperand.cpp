#include "DataOperand.h"

DataOperand::DataOperand(BYTE data)
{
	data_ = data;
}

BYTE DataOperand::getDataOperand()
{
	return data_;
}
