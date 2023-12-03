#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <regex>
#include <list>
#include <map>

namespace AdventOfCode23 {

	struct Number {
	public:
		int line;
		int column;
		int length;
		int value;
		bool verified = false;
	};

	class Symbol {
	public:
		Symbol(int line, int column, std::string value) : Line(line), Column(column), Value(value) {}
	public:
		int Line;
		int Column;
		std::string Value;
	};

	class Day3 : public Day
	{
	public:
		Day3(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		std::map<int, int> _linesSize;
		std::list<Symbol> _symbols;
		std::list<Number*> _numbers;
		std::map<int, std::map<int, Number*>> _numbersMatrix;

	public:
	protected:
		bool AddNumberNearSymbol(Symbol symbol, int &sum, int &sumGearRatio);

	public:
		~Day3();
	};
}