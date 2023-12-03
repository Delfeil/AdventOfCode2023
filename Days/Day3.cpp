#include "pch.h"
#include "Day3.h"

void AdventOfCode23::Day3::Resolve()
{
	std::string patternNumber("[0-9]+");
	std::regex rPatternNumber(patternNumber);
	std::string patternSymbol("[^a-zA-Z0-9\s:\.]");
	std::regex rPatternSymbol(patternSymbol);
	std::string line;

	std::regex_iterator<std::string::iterator> rend;
	int lineId = 0;
	while (std::getline(_stream, line))
	{
		std::cout << line << std::endl;
		_linesSize[lineId] = line.size();
		std::regex_iterator<std::string::iterator> ritNumber(line.begin(), line.end(), rPatternNumber);
		while (ritNumber != rend)
		{
			Number* num = new Number;
			num->line = lineId;
			num->column = ritNumber->position();
			num->length = ritNumber->length();
			num->value = std::stoi(ritNumber->str());
			num->verified = false;
			_numbers.push_back(num);
			for (int i = num->column; i < num->column + num->length; i++)
			{
				_numbersMatrix[lineId][i] = num;
			}

			std::cout << "Number found: " << num->value << "[" << num->line << ", " << num->column << "] length: " << num->length << std::endl;
			ritNumber++;
		}

		std::regex_iterator<std::string::iterator> ritSymbols(line.begin(), line.end(), rPatternSymbol);
		while (ritSymbols != rend)
		{
			Symbol symbol(lineId, ritSymbols->position(), ritSymbols->str());
			_symbols.push_back(symbol);
			std::cout << "Symbol found: " << symbol.Value << "[" << symbol.Line << ", " << symbol.Column << "]" << std::endl;
			ritSymbols++;
		}
		lineId++;
	}

	std::cout << "Nb Symbols Found: " << _symbols.size() << std::endl;

	int sum = 0;
	int sumGearRatio = 0;
	for (std::list<Symbol>::iterator itSymbol = _symbols.begin(); itSymbol != _symbols.end(); itSymbol++)
	{
		Symbol symbol = *itSymbol;
		std::cout << "Symbol: " << symbol.Value << " [" << symbol.Line << ", " << symbol.Column << "]" << std::endl;
		AddNumberNearSymbol(symbol, sum, sumGearRatio);
	}

	std::cout << "Total sum = " << sum << " Total sum gears = " << sumGearRatio << std::endl;
}

bool AdventOfCode23::Day3::AddNumberNearSymbol(Symbol symbol, int& sum, int& sumGearRatio)
{
	std::map<int, std::map<int, Number*>>::iterator itLine;
	std::map<int, Number*>::iterator itColumn;
	bool numberFound = false;
	std::list<int> gearNumbers;

	for (int i = symbol.Line -1; i <= symbol.Line + 1; i++)
	{
		if (i < 0 || i >= _linesSize.size())
			continue;

		for (int j = symbol.Column - 1; j <= symbol.Column + 1; j++)
		{
			if (j < 0 || j >= _linesSize.find(i)->second)
				continue;
			
			itLine = _numbersMatrix.find(i);
			if (itLine != _numbersMatrix.end())
			{
				itColumn = _numbersMatrix[i].find(j);
				if (itColumn != _numbersMatrix[i].end())
				{
					int number = itColumn->second->value;
					if (!symbol.Value.compare("*"))
					{
						if (gearNumbers.empty() || gearNumbers.back() != number)
						{
							std::cout << "Potential Gear * at position [" << i << ", " << j << "] add number: " << number << std::endl;
							gearNumbers.push_back(number);
						}
					}
					if (itColumn->second->verified)
						continue;
					itColumn->second->verified = true;
					sum += number;
					std::cout << "Number near symbol: " << number << " at position [" << i << ", " << j << "] ===> somme = " << sum << std::endl;
					

					numberFound = true;
				}
			}
		}
	}

	if (gearNumbers.size() == 2)
	{
		sumGearRatio += (gearNumbers.front() * gearNumbers.back());
		std::cout << "Symbol Was a gear adgacent to numbers: " << gearNumbers.front() << " * " << gearNumbers.back()
			<< " = " << (gearNumbers.front() * gearNumbers.back()) << " sum = " << sumGearRatio << std::endl;
	}

	return numberFound;
}

AdventOfCode23::Day3::~Day3()
{
	_stream.close();

	for (std::list<Number*>::iterator it = _numbers.begin(); it != _numbers.end(); ++it)
		delete *it;

	/*std::map<int, std::map<int, Number*>>::iterator itLine;
	std::map<int, Number*>::iterator itColumn;
	for (itLine = _numbersMatrix.begin(); itLine != _numbersMatrix.end(); itLine++)
	{
		for (itColumn = _numbersMatrix.find(itLine->first)->second.begin(); itColumn != _numbersMatrix.find(itLine->first)->second.end(); itColumn++) {
			delete itColumn->second;
		}
	}*/
}
