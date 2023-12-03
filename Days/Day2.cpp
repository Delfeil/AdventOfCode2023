#include "pch.h"
#include "Day2.h"
#include <regex>

AdventOfCode23::Day2::Day2(char* fileName, int stepNumber)
{
	_stepNumber = stepNumber;
	_fileName = fileName;
	std::cout << "Day2 open file" << _fileName << " step: " << _stepNumber << std::endl;
	_stream.open(fileName);
}

void AdventOfCode23::Day2::Resolve()
{
	std::string line;
	int countNbGamesPossible = 0;
	int countNbRoundsPossible = 0;
	int sumIds = 0;
	int sumPower = 0;

	std::string patternGameId("[0-9]+(?=:)");
	std::regex rPatternGameId(patternGameId);
	std::string patternRound("([0-9]+ (red|green|blue)?, )*([0-9]+ (red|green|blue)(;|$))");
	std::regex rPatternRound(patternRound);
	std::string patternNumberWithColor("[0-9]+ (blue|green|red)");
	std::regex rPatternNumberWithColor(patternNumberWithColor);
	std::string patternNumber("[0-9]+");
	std::regex rPatternNumber(patternNumber);
	std::string patternColor("(blue|green|red)");
	std::regex rPatternColor(patternColor);
	while (std::getline(_stream, line))
	{
		std::smatch matchGameId;
		std::regex_search(line, matchGameId, rPatternGameId);

		int GameId = std::stoi(matchGameId.str());
		std::cout << "==== Game " << GameId << ": " << line << std::endl;


		std::regex_iterator<std::string::iterator> ritRound(line.begin(), line.end(), rPatternRound);
		std::regex_iterator<std::string::iterator> rend;

		
		bool gameIsPossible = true;

		int minBlue = 0;
		int minGreen = 0;
		int minRed  = 0;
		int power = 0;

		while (ritRound != rend)
		{
			std::string sRound = ritRound->str();
			std::regex_iterator<std::string::iterator> ritNumberWithColor(sRound.begin(), sRound.end(), rPatternNumberWithColor);

			std::smatch matchNumber;
			std::smatch matchColor;

			bool roundIsPossible = true;

			while (ritNumberWithColor != rend) {
				std::string numberColor = ritNumberWithColor->str();

				std::regex_search(numberColor, matchNumber, rPatternNumber);
				std::regex_search(numberColor, matchColor, rPatternColor);
				int number = std::stoi(matchNumber.str());
				if (!matchColor.str().compare("blue")) {
					if (minBlue < number)
						minBlue = number;
					if(number > _nbBlue)
						roundIsPossible = false;
				}
				if (!matchColor.str().compare("green")) {
					if (minGreen < number)
						minGreen = number;
					if (number > _nbGreen)
						roundIsPossible = false;
				}
				if (!matchColor.str().compare("red")) {
					if (minRed < number)
						minRed = number;
					if (number > _nbRed)
						roundIsPossible = false;
				}
				if (!roundIsPossible)
				{
					std::cout << "Round is Impossible: " << sRound << " ==> " << numberColor << std::endl;
				}
				++ritNumberWithColor;
			}
			if (!roundIsPossible)
			{
				gameIsPossible = false;
			}
			std::cout << "Round is Possible: " << sRound << std::endl;
			countNbRoundsPossible++;
			
			ritRound++;
		}
		power = minBlue * minGreen * minRed;
		sumPower += power;
		std::cout << "Min b g r values: " << minBlue << ", " << minGreen << ", " << minRed << " || power = " << power << " sum power = " << sumPower << std::endl;
		if (!gameIsPossible)
			continue;

		countNbGamesPossible++;
		sumIds += GameId;
	}
	std::cout << "Nb Rounds Possible: " << countNbRoundsPossible << " Nb Games Possible: " << countNbGamesPossible << " Sum Ids = " << sumIds << " Sum Power = " << sumPower << std::endl;
}
