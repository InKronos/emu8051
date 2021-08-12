#include "stdafx.h"
#include "CPU.h"

int main(int argc, char* argv[])
{
	CPU cpu(getFilename(argc, argv));
	cpu.run();
}