#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
namespace AdventOfCode23 {
	class Day9 : Day
	{
	public:
		Day9(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void BuildData();
		void Resolve();
		int GetNextValue(std::vector<int> prevValues);
		bool SequenceAtZero(std::vector<int> values);
	protected:
		std::vector<std::vector<int>*> _values;
	};
}
