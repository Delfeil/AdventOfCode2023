#include "Day1Implementation.h"
#include <iostream>
#include <string>

void DayImplementation::Resolve(char* fileName, int dayNumber, int stepNumber)
{
	if (dayNumber == 1)
	{
		Day1 d1(stepNumber);
		d1.Resolve(fileName);
	}
	else if (dayNumber == 2)
	{
		Day2 d2(fileName, stepNumber);
		d2.Resolve();
	} 
	else if (dayNumber == 3) {
		Day3 d3(fileName, stepNumber);
		d3.Resolve();
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
		return 1;
	
	std::string dayNumber(argv[2]);
	std::string step(argv[3]);
	DayImplementation dayImplementation;
	dayImplementation.Resolve(argv[1], std::stoi(dayNumber), std::stoi(step));
	return 0;
}
