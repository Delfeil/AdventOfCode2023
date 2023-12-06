#include "pch.h"
#include "Day6.h"

void AdventOfCode23::Day6::Resolve()
{
	std::string patternNumber("[0-9]+");
	std::regex rPatternNumber(patternNumber);
	std::smatch matchNumber;
	std::string line;
	int lineNumber = 0;
	while (std::getline(_stream, line))
	{
		std::vector<int>* currentListToComplete = nullptr;
		long long* currentNumber = nullptr;
		if (lineNumber == 0)
		{
			currentListToComplete = &_raceTime;
			currentNumber = &bigRaceTime;
		}
		else if (lineNumber == 1)
		{
			currentListToComplete = &_raceBestDistance;
			currentNumber = &bigRaceBestDistance;
		}

		std::istringstream iss(line);
		std::string number;
		std::string bigRace;
		while (iss >> number)
		{
			std::cout << number << std::endl;
			if (std::regex_search(number, matchNumber, rPatternNumber))
			{
				bigRace = bigRace + number;
				if (currentListToComplete != nullptr)
				{
					currentListToComplete->push_back(std::stoi(number));
				}
			}
		}
		std::cout << "Big Race value: " << bigRace << std::endl;
		if (currentNumber != nullptr)
		{
			*currentNumber = std::stoll(bigRace);
		}
		std::cout << "Big Race Time: " << bigRaceTime << ", BestDistance: " << bigRaceBestDistance << std::endl;
		lineNumber++;
	}

	std::cout << "Big Race Time: " << bigRaceTime << ", BestDistance: " << bigRaceBestDistance << std::endl;
	int bigRaceNbBeat = GetNbBeatBestDistance(bigRaceTime, bigRaceBestDistance);

	std::cout << " nb Beat Best Distance: " << bigRaceNbBeat << std::endl;

	int totalRecords = 1;
	for (int i = 0; i < _raceTime.size(); i++)
	{
		int raceTime = _raceTime[i];
		int raceBestDistance = _raceBestDistance[i];
		int nbBeatBestDistance = 0;
		nbBeatBestDistance = GetNbBeatBestDistance(raceTime, raceBestDistance);
		/*for (int heldTime = 0; heldTime <= raceTime; heldTime++)
		{
			int remaningTime = raceTime - heldTime;
			int distance = remaningTime * heldTime;

			if (distance > raceBestDistance)
			{
				nbBeatBestDistance++;
			}
		}*/
		if (nbBeatBestDistance > 0)
		{
			totalRecords *= nbBeatBestDistance;
		}
		std::cout << "Race " << i << " nb beat distance ====> " << nbBeatBestDistance << " total: " << totalRecords << std::endl;
	}

	std::cout << "Total Record: " << totalRecords << std::endl;
}

int AdventOfCode23::Day6::GetNbBeatBestDistance(int time, int bestDistance)
{
	std::cout << "ici" << std::endl;
	int nbBeatBestDistance = 0;
	for (int heldTime = 0; heldTime <= time; heldTime++)
	{
		int remaningTime = time - heldTime;
		int distance = remaningTime * heldTime;

		if (distance > bestDistance)
		{
			nbBeatBestDistance++;
		}
	}
	return nbBeatBestDistance;
}

long long AdventOfCode23::Day6::GetNbBeatBestDistance(long long time, long long bestDistance)
{
	std::cout << "ici long long" << std::endl;
	long long nbBeatBestDistance = 0;
	for (long long heldTime = 0; heldTime <= time; heldTime++)
	{
		long long remaningTime = time - heldTime;
		long long distance = remaningTime * heldTime;

		if (distance > bestDistance)
		{
			nbBeatBestDistance++;
		}
	}
	return nbBeatBestDistance;
}
