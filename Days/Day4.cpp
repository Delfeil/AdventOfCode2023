#include "pch.h"
#include "Day4.h"

void AdventOfCode23::Day4::Resolve()
{
	std::string patternNumber("[0-9]+");
	std::regex rPatternNumber(patternNumber);
	std::smatch matchNumber;
	std::string line;

	int sumPoints = 0;
	int lineId = 0;
	while (std::getline(_stream, line))
	{
		std::cout << line << std::endl;
		Card* currentCard = new Card();
		currentCard->cardId = lineId;
		std::istringstream iss(line);
		std::string number;
		std::list<int>* validNumbers = new std::list<int>();
		//std::pair<int, Card*>* cardInstance = new std::pair<int, Card*>(1, currentCard);
		while (iss >> number)
		{
			std::cout << "is number a number?: " << number << std::endl;
			if (!number.compare("|"))
				break;
			if (number.back() == ':')
				continue;
			if (std::regex_search(number, matchNumber, rPatternNumber))
			{
				std::cout << "Add valid Number: " << matchNumber.str() << std::endl;
				validNumbers->push_back(std::stoi(matchNumber.str()));
			}
		}
		currentCard->validNumbers = validNumbers;

		std::list<int>* cardNumbers = new std::list<int>();
		while (iss >> number)
		{
			if (number.empty())
				break;
			std::cout << "Add my Number: " << number << std::endl;
			cardNumbers->push_back(std::stoi(number));
		}
		currentCard->cardNumbers = cardNumbers;
		
		_cards[lineId].second = currentCard;
		_cardsStack.push(currentCard);
		lineId++;
	}

	for (int i = 0; i < _cards.size(); i++)
	{
		int cardScore = 0;
		Card* card = _cards[i].second;
		for (std::list<int>::iterator itMyCard = card->cardNumbers->begin(); itMyCard != card->cardNumbers->end(); itMyCard++)
		{
			std::list<int>::iterator findIter = std::find(card->validNumbers->begin(), card->validNumbers->end(), *itMyCard);
			if (findIter != card->validNumbers->end())
			{
				card->nbMatchingNumbers++;
				if (cardScore == 0)
				{
					cardScore = 1;
				}
				else
				{
					cardScore *= 2;
				}
				std::cout << "Card " << i << " number match : " << *itMyCard << " Card Score = " << cardScore << std::endl;
			}
		}
		card->score = cardScore;
		sumPoints += cardScore;

		card->cardsCopied = new int[card->nbMatchingNumbers];
		for (int i = 0; i < card->nbMatchingNumbers; i++)
		{
			int cardIdToCopy = (card->cardId + (i + 1));
			card->cardsCopied[i] = cardIdToCopy;
			_cards[cardIdToCopy].first += 1;
		}
		std::cout << "Total Score = " << sumPoints << std::endl;
	}


	int totalNbCards = 0;
	while (!_cardsStack.empty()) {
		totalNbCards += 1;
		Card* card = _cardsStack.top();
		_cardsStack.pop();
		//std::cout << "Card " << card->cardId << " Copy cards: ";
		for (int j = 0; j < card->nbMatchingNumbers; j++)
		{
			int cardIdToDuplicate = card->cardsCopied[j];
			_cardsStack.push(_cards[cardIdToDuplicate].second);
			//std::cout << cardIdToDuplicate << ", ";
		}
		//std::cout << std::endl;

	}
	std::cout << "Total Cards: " << totalNbCards << std::endl;
}

