#pragma once
#include <fstream>
#include <string>

namespace AdventOfCode23
{
	class Day
	{
		public:
			explicit Day(char* fileName, int stepNumber);
			void Resolve();

		protected:
			std::string _fileName;
			int _stepNumber;
			std::ifstream _stream;

		public:
			~Day();
	};
}
