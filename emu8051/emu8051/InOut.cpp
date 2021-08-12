#include "InOut.h"

InOut::InOut()
{
	
}

InOut::~InOut()
{
}

void InOut::print(const uchar data, const char mode)
{
	if (mode != 0)
	{
		if (mode == 'c') {
			printf("%c", data);
		}
		if (mode == 'd') {
			printf("%d", data);
		}
	}
}

bool InOut::getInput(char& character)
{
	if (_kbhit())
	{
		character = _getch();
		return true;
	}
	return false;
}
