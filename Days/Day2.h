#pragma once

#define DAY2 __declspec(dllexport)

#include <iostream>
#include <fstream>
#include <string>
#include <regex>
namespace AdventOfCode23
{
	class Day2
	{
	public:
		Day2(char* fileName, int stepNumber);
	protected:
		std::string _fileName;
		int _stepNumber;
		std::ifstream _stream;
	protected: // Params
		int _nbRed = 12;
		int _nbGreen = 13;
		int _nbBlue = 14;
	public:
		void Resolve();

	};
}
