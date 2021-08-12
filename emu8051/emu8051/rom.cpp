#include "rom.h"

ROM::ROM(const ushort size) : Memory(size), instructionSize(0)
{
}

ROM::~ROM()
{
}



void ROM::getInstructionsFormFIle(const std::string namefile)
{
    std::string stringByte;
	std::ifstream file;
	file.open(namefile);
    int i = 0;
    while (file.good())
    {
        file >> stringByte;
        setMemoryCell(i, stringToByte(stringByte));
        i++;
    }
    file.close();
    instructionSize = i;
}

int ROM::getInstructionSize() const
{
    return instructionSize;
}
