#pragma once
#include "pch.h"
#include "day.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>

namespace AdventOfCode23
{
	namespace d5 {

		class Range {
		public:
			Range(int min, int range) : _min(min), _max(min + range), _range(range) {}

		protected:
			int _min;
			int _max;
			int _range;
		public:
			int GetPositionInRange(int value);
		};

		class Converter {
		public:
			std::string GetName() { return _name; }
		protected:
			std::string _name;
			std::list<std::pair<Range*, Range*>*> _convertiblesValues; // pair<min, max>
		};
	}

	class Day5 : Day
	{
	public:
		Day5(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		std::list<int> _seeds;
		
		d5::Converter* _nextConverter;
	};

}

