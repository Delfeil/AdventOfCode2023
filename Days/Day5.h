#pragma once
#include "pch.h"
#include "day.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <vector>
#include <regex>

namespace AdventOfCode23
{
	namespace d5 {

		class Range {
		public:
			Range(long long min, long long range, long long dest) : _min(min), _max(min + range), _range(range), _dest(dest) {}

		protected:
			long long _min;
			long long _max;
			long long _range;
			long long _dest;
		public:
			long long GetPositionInRange(long long value);
		};

		class Converter {
		public:
			Converter(std::string name) : _name(name) {}
		public:
			std::string GetName() { return _name; }
		protected:
			std::string _name;
			std::vector<Range*> _ranges;
		public:
			long long Convert(long long value);
			void AddRange(Range* range);
		};
	}

	class Day5 : Day
	{
	public:
		Day5(char* fileName, long long stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
		long long GetSeedLocation(long long seed);
	protected:
		std::vector<long long> _seeds;
		std::vector<d5::Converter*> _converters;
		d5::Converter* _nextConverter;
	};

}

