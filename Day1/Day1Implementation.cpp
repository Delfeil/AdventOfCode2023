#include "Day1Implementation.h"
#include <iostream>
#include <string>

void DayImplementation::Resolve(char* fileName, int dayNumber, int stepNumber)
{
	switch (dayNumber)
	{
	case 1: {
		Day1 d1(stepNumber);
		d1.Resolve(fileName);
		break;
	}
	case 2: {
		Day2 d2(fileName, stepNumber);
		d2.Resolve();
		break;
	}
	case 3: {
		Day3 d3(fileName, stepNumber);
		d3.Resolve();
		break;
	}
	case 4: {
		Day4 d4(fileName, stepNumber);
		d4.Resolve();
		break;
	}
	case 5: {
		Day5 d5(fileName, stepNumber);
		d5.Resolve();
		break;
	}
	case 6: {
		Day6 d6(fileName, stepNumber);
		d6.Resolve();
		break;
	}
	case 7: {
		Day7 d7(fileName, stepNumber);
		d7.Resolve();
		break;
	}
	case 8: {
		Day8 d8(fileName, stepNumber);
		d8.Resolve();
		break;
	}case 9: {
		Day9 d9(fileName, stepNumber);
		d9.Resolve();
		break;
	}
	default:
		break;
	}

	/*if (dayNumber == 1)
	{
	}
	else if (dayNumber == 2)
	{
	} 
	else if (dayNumber == 3) {
	}
	else if (dayNumber == 4) {
	}*/
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
