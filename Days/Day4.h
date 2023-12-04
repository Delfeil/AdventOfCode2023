#pragma once
#include "Day.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <regex>

namespace AdventOfCode23
{
	class Day4 : Day
	{

		struct Card {
		public:
			int cardId = 0;
			bool copy = false;
			std::list<int>* validNumbers;
			std::list<int>* cardNumbers;
			int nbMatchinNumbers = 0;
			int score = 0;
		};

	public:
		Day4(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();

	protected:
		std::map<int, Card*> _cards;
	};
}