#include "Day1Implementation.h"
#include <iostream>
#include <string>

void Day1Implementation::Resolve(char* fileName, int stepNumber)
{
	Day1 d1(stepNumber);
	d1.Resolve(fileName);
}

int main(int argc, char* argv[])
{
	if (argc != 3)
		return 1;
	
	Day1Implementation d1;
	std::string step(argv[2]);
	d1.Resolve(argv[1], std::stoi(step));
	return 0;
}
