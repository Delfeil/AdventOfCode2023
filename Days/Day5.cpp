#include "pch.h"
#include "Day5.h"

void AdventOfCode23::Day5::Resolve()
{
	return;
}

int AdventOfCode23::d5::Range::GetPositionInRange(int value)
{
	if (value >= _min && value <= _max)
	{
		return value - _min;
	}
	return -1;
}