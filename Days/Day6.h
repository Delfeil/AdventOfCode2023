#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace AdventOfCode23
{
	class Day6 :Day
	{
	public: 
		Day6(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	public:
		int GetNbBeatBestDistance(int time, int bestDistance);
		long long GetNbBeatBestDistance(long long time, long long bestDistance);
	protected:
		std::vector<int> _raceTime;
		long long bigRaceTime;
		std::vector<int> _raceBestDistance;
		long long bigRaceBestDistance;
	};
}
