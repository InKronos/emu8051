#include "Memory.h"



Memory::Memory(const ushort size) : size(size)
{
	memory = new uchar[size];
}

Memory::~Memory()
{
}

void Memory::setMemoryCell(const size_t index, const uchar value)
{
	if (size <= index) throw std::exception("Wrong index");
	memory[index] = value;
}



uchar Memory::operator [] (const size_t index) const {
	if (size <= index) throw std::exception("Wrong index");
	return memory[index];
}


uchar& Memory::operator [] (const size_t index) {
	if (size <= index) throw std::exception("Wrong index");
	return memory[index];
}