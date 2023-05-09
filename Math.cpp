#include "Math.h"

int Repeat(int value, const int& max)
{
	if (value > max)
		return Repeat(value - (max + 1), max);
	else if (0 > value)
		return Repeat(max + (value + 1), max);

	return value;
}