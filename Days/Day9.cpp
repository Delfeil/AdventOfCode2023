#include "pch.h"
#include "Day9.h"

void AdventOfCode23::Day9::BuildData()
{
	std::string line;
	while (std::getline(_stream, line))
	{
		if (line.empty())
			continue;
		std::vector<int>* lineValues = new std::vector<int>();
		std::istringstream iss(line);
		std::string number;
		while (iss >> number)
		{
			lineValues->push_back(std::stoi(number));
		}
		_values.push_back(lineValues);
	}
}

void AdventOfCode23::Day9::Resolve()
{
	BuildData();

	int Total = 0;
	for (std::vector<int>* values : _values) {
		int nextVal = GetNextValue(*values);
		Total += nextVal;
		std::cout << "Next val => " << nextVal << " Total: " << Total << std::endl;
	}
	std::cout << "Total: " << Total << std::endl;
}

int AdventOfCode23::Day9::GetNextValue(std::vector<int> prevValues)
{
	if (SequenceAtZero(prevValues))
		return 0;
	std::vector<int> nextValues;
	for (int valId = 0; valId < (prevValues.size()-1); valId++)
	{
		int currentVal = prevValues[valId];
		int nextVal = prevValues[valId + 1];
		nextValues.push_back(nextVal - currentVal);
	}
	if (_stepNumber == 1)
	{
		return prevValues[prevValues.size() - 1] + GetNextValue(nextValues);

	}
	else {
		return prevValues[0] - GetNextValue(nextValues);
	}
}

bool AdventOfCode23::Day9::SequenceAtZero(std::vector<int> values)
{
	for (int val : values)
	{
		if (val != 0)
		{
			return false;
		}
	}
	return true;
}
