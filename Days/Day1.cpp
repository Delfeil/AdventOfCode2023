#include "pch.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

AdventOfCode23::Day1::Day1(int stepNumber)
{
	_stepNumber = stepNumber;
}

void AdventOfCode23::Day1::Resolve(char* fileName)
{
	_fileName = fileName;
	std::cout << _fileName << std::endl;
	_stream.open(fileName);
	std::string line;
	int total = 0;
	while (std::getline(_stream, line))
	{
		int lineValue = 0;
		if (_stepNumber == 1)
		{
			lineValue = GetLineValueV1(line);
		}
		else if (_stepNumber == 2) {
			lineValue = GetLineValueV2(line);

		}
		else {
			lineValue = -1;
		}
		if (lineValue < 0)
			continue;
		
		total += lineValue;
		std::cout << total << std::endl;
	}
}

int AdventOfCode23::Day1::GetLineValueV1(std::string line)
{
	int firtNbPos = line.find_first_of("0123456789");
	if (firtNbPos == -1)
	{
		return -1;
	}
	std::stringstream sStream;
	int lastNbPos = line.find_last_of("0123456789");
	sStream << line.at(firtNbPos);
	sStream << line.at(lastNbPos);

	int lineNb = std::stoi(sStream.str());

	std::cout << line << " ==== > " << firtNbPos << " | " << lastNbPos << " ====> " << lineNb << " ==== ";
	return lineNb;
}

int AdventOfCode23::Day1::GetLineValueV2(std::string line)
{
	std::string patternFirst("(one|two|three|four|five|six|seven|eight|nine|[1-9])");

	std::smatch match;
	std::regex pattern(patternFirst);
	std::regex_search(line, match, pattern);
	int firstValue = GetValue(match.str());
	if (firstValue == -1) {
		return -1;
	}

	std::string lastMatch;
	while (std::regex_search(line, match, pattern))
	{
		lastMatch = match.str();
		line = line.substr(match.position() + 1);
	}
	int lastValue = GetValue(lastMatch);

	int lineValue = (firstValue * 10) + lastValue;
	std::cout << line << " == > " << firstValue << " | " << lastValue << " ====> " << lineValue << " ==== ";
	return lineValue;
}

int AdventOfCode23::Day1::GetValue(std::string sValue)
{
	std::cout << "Get Value: " << sValue << std::endl;
	int value = -1;
	if (!sValue.compare("one"))
		value = 1;
	else if (!sValue.compare("two"))
		value = 2;
	else if (!sValue.compare("three"))
		value = 3;
	else if (!sValue.compare("four"))
		value = 4;
	else if (!sValue.compare("five"))
		value = 5;
	else if (!sValue.compare("six"))
		value = 6;
	else if (!sValue.compare("seven"))
		value = 7;
	else if (!sValue.compare("eight"))
		value = 8;
	else if (!sValue.compare("nine"))
		value = 9;
	else {
		value = std::stoi(sValue);
	}
	return value;
}
