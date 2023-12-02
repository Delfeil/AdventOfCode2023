#pragma once

#define DAY1 __declspec(dllexport)
//#define DAY1 __declspec(dllimport)

#include <string>
#include <fstream>
namespace AdventOfCode23
{
	class Day1
	{
	public:
		Day1(int stepNumber);
	protected:
		std::string _fileName;
		int _stepNumber;
		std::ifstream _stream;
	public:
		void Resolve(char* fileName);
	protected:
		int GetLineValueV1(std::string line);
		int GetLineValueV2(std::string line);

		int GetValue(std::string sValue);
	};
}

