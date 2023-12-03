#include "pch.h"
#include "Day.h"

AdventOfCode23::Day::Day(char* fileName, int stepNumber)
{
	_stepNumber = stepNumber;
	_fileName = fileName;
	std::cout << "Day2 open file" << _fileName << " step: " << _stepNumber << std::endl;
	_stream.open(fileName);
}

void AdventOfCode23::Day::Resolve()
{
}

AdventOfCode23::Day::~Day()
{
	_stream.close();
}
