#include "pch.h"
#include "Day5.h"

void AdventOfCode23::Day5::Resolve()
{
	std::string line;
	std::string patternNumbers("[0-9]+");
	std::regex rPatternNumbers(patternNumbers);
	std::string patternConverterName("([a-z]|[A-Z]|-)+ ");
	std::regex rPatternConverterName(patternConverterName);
		// Seeds line
	std::getline(_stream, line);
	std::istringstream iss(line);
	std::string number;
	while (iss >> number)
	{
		std::smatch matchNumber;
		if (std::regex_search(number, matchNumber, rPatternNumbers))
		{
			std::cout << "add seed: " << number << std::endl;
			_seeds.push_back(std::stoll(number));
		}
	}

	long long converterId = -1;
	while (std::getline(_stream, line))
	{
		std::smatch matchConverterName;
		if (std::regex_search(line, matchConverterName, rPatternConverterName))
		{
			converterId += 1;
			_converters.push_back(new d5::Converter(matchConverterName.str()));
			continue;
		}
		if (line.empty())
		{
			continue;
		}

		std::istringstream iss(line);
		std::string outputMin;
		std::string inputputMin;
		std::string rangevalue;
		iss >> outputMin;
		iss >> inputputMin;
		iss >> rangevalue;
		d5::Range* range = new d5::Range(std::stoll(inputputMin), std::stoll(rangevalue), std::stoll(outputMin));
		_converters[converterId]->AddRange(range);
	}

	long long nearestLocation = LLONG_MAX;
	for (int seedId = 0; seedId < _seeds.size(); seedId++)
	{
		long long seedLocation = GetSeedLocation(_seeds[seedId]);
		if (seedLocation <= nearestLocation)
		{
			nearestLocation = seedLocation;
		}
	}
	std::cout << "nearestLocation = " << nearestLocation << std::endl;
}

long long AdventOfCode23::Day5::GetSeedLocation(long long seed)
{
	long long currentValue = seed;
	for (int converterId = 0; converterId < _converters.size(); converterId++)
	{
		d5::Converter* converter = _converters[converterId];
		currentValue = converter->Convert(currentValue);
	}
	return currentValue;
}

long long AdventOfCode23::d5::Range::GetPositionInRange(long long value)
{
	if (value >= _min && value <= _max)
	{
		return _dest +(value - _min);
	}
	return -1;
}

long long AdventOfCode23::d5::Converter::Convert(long long value)
{
	long long valueConverted = 0;
	for (int rangeId = 0; rangeId < _ranges.size(); rangeId++)
	{
		valueConverted = _ranges[rangeId]->GetPositionInRange(value);
		if (valueConverted != -1)
		{
			return valueConverted;
		}
	}
	return value;
}

void AdventOfCode23::d5::Converter::AddRange(Range* range)
{
	_ranges.push_back(range);
}
