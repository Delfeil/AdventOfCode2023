#pragma once
#include "Day.h"
#include <string>
namespace AdventOfCode23 {
	class Day13 : Day
	{
	public:
		Day13(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		std::vector<std::string*> _lines;
		std::vector<std::string*> _columns;
	public:
		void FillData();
		int VerifyMirroring(std::vector<std::string*> stringVector);
		bool VerifyMirroring(std::vector<std::string*> stringVector, int index);
		bool VerifyMirroring(std::string* leftString, std::string* rightString);
	};
}
