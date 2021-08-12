#include "helpFunctions.h"

ushort getCharToInt(const char code) {
	ushort value = 0;
	switch (code)
	{
	case '1':
		value = 1;
		break;
	case '2':
		value = 2;
		break;
	case '3':
		value = 3;
		break;
	case '4':
		value = 4;
		break;
	case '5':
		value = 5;
		break;
	case '6':
		value = 6;
		break;
	case '7':
		value = 7;
		break;
	case '8':
		value = 8;
		break;
	case '9':
		value = 9;
		break;
	case 'A':
		value = 10;
		break;
	case 'B':
		value = 11;
		break;
	case 'C':
		value = 12;
		break;
	case 'D':
		value = 13;
		break;
	case 'E':
		value = 14;
		break;
	case 'F':
		value = 15;
		break;
	default:
		break;
	}
	return value;
}

uchar stringToByte(const std::string hexcode)
{
	uchar byte = 0x00;
	uchar high = (uchar)getCharToInt(hexcode[2]);
	high <<= 4;
	byte = high;
	uchar low = (uchar)getCharToInt(hexcode[3]);
	byte |= low;
	return byte;
}

std::string getFilename(const int argc, char* argv[])
{
	std::string filename = "helloworld.hex";
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i],"-i")) {
			filename = argv[++i];
		}
	}
	return filename;
}

