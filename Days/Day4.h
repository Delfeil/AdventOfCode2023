#pragma once
#include "Day.h"
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <regex>
#include <stack>

namespace AdventOfCode23
{
	class Day4 : Day
	{

		struct Card {
		public:
			int cardId = 0;
			std::list<int>* validNumbers;
			std::list<int>* cardNumbers;
			int nbMatchingNumbers = 0;
			int score = 0;
			int* cardsCopied;
		};

	public:
		Day4(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();

	protected:
		std::map<int, std::pair<int, Card*>> _cards;
		std::stack<Card*> _cardsStack;
	};
}