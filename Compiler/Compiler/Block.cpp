#include "Block.h"

Block::Block(DWORD size, SectionType sectionType)
{
	size_ = size;
	sectionType_ = sectionType;
}

void Block::setSize(DWORD size)
{
	size_ = size;
}

DWORD Block::getSize()
{
	return size_;
}

SectionType Block::getSectionType()
{
	return sectionType_;
}

Block::~Block()
{
}
