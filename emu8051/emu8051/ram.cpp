#include "ram.h"





RAM::RAM(const ushort size) : Memory(size)
{
	initialize();
}

RAM::~RAM()
{
}

void RAM::initialize()
{
	for (int i = 0; i < 256; i++) {
		setMemoryCell(i, 0x00);
	}
}



