#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <sstream>
#include <deque>
#include <queue>
#include <vector>
namespace AdventOfCode23 {

	namespace D7 {
		enum HandType {
			HIGHT_CARD = 1,
			ONE_PAIR = 2,
			TWO_PAIR = 3,
			THREE_OF_A_KIND = 4,
			FULL_HOUSE = 5,
			FOUR_OF_A_KIND = 6,
			FIVE_OF_A_KIND = 7
		};
		enum CardType {
			NONE = 0,
			TWO = 1,
			THREE = 2,
			FOUR = 3,
			FIVE = 4,
			SIX = 5,
			SEVEN = 6,
			EIGHT = 7,
			NINE = 8,
			T = 9,
			J = 10,
			Q = 11,
			K = 12,
			A = 13
		};

		namespace Cards2 {
			enum CardType2 {
				NONE = 0,
				J = 1,
				TWO = 2,
				THREE = 3,
				FOUR = 4,
				FIVE = 5,
				SIX = 6,
				SEVEN = 7,
				EIGHT = 8,
				NINE = 9,
				T = 10,
				Q = 11,
				K = 12,
				A = 13
			};
			static CardType2 GetCardType2(char card);
		}

		static std::vector<char> CardsList{ 'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J' };

		static CardType GetCardType(char card);

		class Hand {
		public:
			Hand(std::string hand, int bet, int cardSet);
		
		protected:
			std::string _hand;
			int _bet;
			int _cardSet;
			HandType _handType;
			std::map<char, int> _cardsAmount;
			CardType* _cardsByCardType;
			Cards2::CardType2* _cardsByCardType2;

		public:
			bool operator>(Hand h);
			std::string GetHand() { return _hand; };
			int GetBet() { return _bet; };
			int GetCardSet() { return _cardSet; };
			HandType GetHandType() { return _handType; };
			CardType* GetCardsByCardType() { return _cardsByCardType; }
			Cards2::CardType2* GetCardsByCardType2() { return _cardsByCardType2; }
		protected:
			HandType CalculateHandType();
		};
		bool operator>(Hand& hl, Hand& hr);
		bool operator<(Hand& hl, Hand& hr);

		bool CompareHands(Hand hl, Hand hr);
	}

	class Day7 : Day
	{
	public:
		Day7(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		std::list<D7::Hand> _hands;
	};
}
