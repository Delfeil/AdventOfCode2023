#include "pch.h"
#include "Day7.h"

void AdventOfCode23::Day7::Resolve()
{
	std::string line;
	while (std::getline(_stream, line))
	{
		std::istringstream iss(line);
		std::string handStr;
		std::string bet;
		iss >> handStr;
		iss >> bet;
		D7::Hand hand(handStr, std::stoi(bet), _stepNumber);
		_hands.push_back(hand);
	}

	_hands.sort(D7::CompareHands);

	int total = 0;
	int handPosition = 1;
	for (std::list<D7::Hand>::iterator handsIt = _hands.begin(); handsIt != _hands.end(); handsIt++)
	{
		total = total + (handPosition * handsIt->GetBet());
		std::cout << "Hand " << handPosition << " => " << handsIt->GetHand() << " bet: " << handsIt->GetBet()
			<< " HandType: " << handsIt->GetHandType() << " Total = " << total << std::endl;
		handPosition++;
	}
	std::cout << " Total = " << total << std::endl;
}

AdventOfCode23::D7::Hand::Hand(std::string hand, int bet, int cardsSet)
{
	_hand = hand;
	_bet = bet;
	_cardSet = cardsSet;
	CalculateHandType();
}

bool AdventOfCode23::D7::Hand::operator>(Hand h)
{
	if (this->_handType > h.GetHandType())
		return true;
	else if (this->_handType < h.GetHandType())
		return false;
	for (int i = 0; i < 5; i++)
	{
		if (this->_cardsByCardType[i] > h._cardsByCardType[i])
			return true;
		else if (this->_cardsByCardType[i] < h._cardsByCardType[i])
			return false;
	}
}

bool AdventOfCode23::D7::operator>(Hand& hl, Hand& hr)
{
	if (hl.GetHandType() > hr.GetHandType())
		return true;
	else if (hl.GetHandType() < hr.GetHandType())
		return false;
	if (hl.GetCardSet() == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			if (hl.GetCardsByCardType2()[i] < hr.GetCardsByCardType2()[i])
				return true;
			else if (hl.GetCardsByCardType2()[i] > hr.GetCardsByCardType2()[i])
				return false;
		}
	}
	else {
		for (int i = 0; i < 5; i++)
		{
			if (hl.GetCardsByCardType()[i] < hr.GetCardsByCardType()[i])
				return true;
			else if (hl.GetCardsByCardType()[i] > hr.GetCardsByCardType()[i])
				return false;
		}
	}
}

bool AdventOfCode23::D7::operator<(AdventOfCode23::D7::Hand& hl, AdventOfCode23::D7::Hand& hr)
{
	return !(&hl > &hr);
}

bool AdventOfCode23::D7::CompareHands(Hand hl, Hand hr)
{
	if (hl.GetHandType() < hr.GetHandType())
		return true;
	else if (hl.GetHandType() > hr.GetHandType())
		return false;
	if (hl.GetCardSet() == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			if (hl.GetCardsByCardType2()[i] < hr.GetCardsByCardType2()[i])
				return true;
			else if (hl.GetCardsByCardType2()[i] > hr.GetCardsByCardType2()[i])
				return false;
		}
	}
	else {
		for (int i = 0; i < 5; i++)
		{
			if (hl.GetCardsByCardType()[i] < hr.GetCardsByCardType()[i])
				return true;
			else if (hl.GetCardsByCardType()[i] > hr.GetCardsByCardType()[i])
				return false;
		}
	}
}

AdventOfCode23::D7::HandType AdventOfCode23::D7::Hand::CalculateHandType()
{
	_handType = HandType::HIGHT_CARD;
	_cardsByCardType = new CardType[5];
	_cardsByCardType2 = new Cards2::CardType2[5];
	int jCount = 0;
	for (int cardId = 0; cardId < _hand.size(); cardId++)
	{
		char card = _hand[cardId];

		_cardsByCardType[cardId] = GetCardType(card);

		_cardsByCardType2[cardId] = Cards2::GetCardType2(card);
		if (_cardSet == 2 && card == 'J')
		{
			jCount++;
		}
		else {
			if(_cardsAmount.find(card) == _cardsAmount.end())
				_cardsAmount[card] = 1;
			else
				_cardsAmount[card] += 1;
		}

		if (_cardsAmount[card] == 5)
		{
			_handType = HandType::FIVE_OF_A_KIND;
		}
		else if (_cardsAmount[card] == 4)
		{
			_handType = HandType::FOUR_OF_A_KIND;
		}
		else if (_cardsAmount[card] == 3)
		{
			_handType = HandType::THREE_OF_A_KIND;
		}
	}

	if (_cardSet == 2)
	{
		char charWithGreatestNbCards = _cardsAmount.begin()->first;
		for (std::map<char, int>::iterator cardsIt = (_cardsAmount.begin()); cardsIt != _cardsAmount.end(); cardsIt++) {
			if (cardsIt->second > _cardsAmount[charWithGreatestNbCards])
			{
				charWithGreatestNbCards = cardsIt->first;
			}
		}
		_cardsAmount[charWithGreatestNbCards] += jCount;
		if (_cardsAmount[charWithGreatestNbCards] == 5)
		{
			_handType = HandType::FIVE_OF_A_KIND;
		}
		else if (_cardsAmount[charWithGreatestNbCards] == 4)
		{
			_handType = HandType::FOUR_OF_A_KIND;
		}
		else if (_cardsAmount[charWithGreatestNbCards] == 3)
		{
			_handType = HandType::THREE_OF_A_KIND;
		}
	}

	int pairsNumber = 0;
	for (std::map<char, int>::iterator cardsIt = _cardsAmount.begin(); cardsIt != _cardsAmount.end(); cardsIt++)
	{
		if (cardsIt->second == 2)
		{
			pairsNumber++;
		}
	}

	if (_handType == HandType::THREE_OF_A_KIND && pairsNumber >= 1)
	{
		_handType = HandType::FULL_HOUSE;
	}
	else if (_handType == HandType::HIGHT_CARD)
	{
		if (pairsNumber == 1)
		{
			_handType = HandType::ONE_PAIR;
		}
		else if(pairsNumber >= 2)
		{
			_handType = HandType::TWO_PAIR;
		}
	}

	return _handType;
}

AdventOfCode23::D7::CardType AdventOfCode23::D7::GetCardType(char card)
{
	switch (card)
	{
	case '2':
		return CardType::TWO;
		break;
	case '3':
		return CardType::THREE;
		break;
	case '4':
		return CardType::FOUR;
		break;
	case '5':
		return CardType::FIVE;
		break;
	case '6':
		return CardType::SIX;
		break;
	case '7':
		return CardType::SEVEN;
		break;
	case '8':
		return CardType::EIGHT;
		break;
	case '9':
		return CardType::NINE;
		break;
	case 'T':
		return CardType::T;
		break;
	case 'J':
		return CardType::J;
		break;
	case 'Q':
		return CardType::Q;
		break;
	case 'K':
		return CardType::K;
		break;
	case 'A':
		return CardType::A;
		break;
	default:
		return CardType::NONE;
		break;
	}
}

AdventOfCode23::D7::Cards2::CardType2 AdventOfCode23::D7::Cards2::GetCardType2(char card)
{
	switch (card)
	{
	case '2':
		return CardType2::TWO;
		break;
	case '3':
		return CardType2::THREE;
		break;
	case '4':
		return CardType2::FOUR;
		break;
	case '5':
		return CardType2::FIVE;
		break;
	case '6':
		return CardType2::SIX;
		break;
	case '7':
		return CardType2::SEVEN;
		break;
	case '8':
		return CardType2::EIGHT;
		break;
	case '9':
		return CardType2::NINE;
		break;
	case 'T':
		return CardType2::T;
		break;
	case 'J':
		return CardType2::J;
		break;
	case 'Q':
		return CardType2::Q;
		break;
	case 'K':
		return CardType2::K;
		break;
	case 'A':
		return CardType2::A;
		break;
	default:
		return CardType2::NONE;
		break;
	}
}
