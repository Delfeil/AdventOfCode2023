#pragma once
#include "Day.h"

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cstdlib>

namespace AdventOfCode23 {
	namespace D11 {
		class Galaxy {
		public:
			Galaxy(int x, int y) : _x(x), _y(y) {};
		protected:
			int _x;
			int _y;
		public:
			void AddTimeExpansion(int timeExpansion);
			void AddLineTimeExpansion(int timeExpansion);
			void AddColumnTimeExpansion(int timeExpansion);
			std::pair<int, int> GetCoordinates() { return std::pair<int, int>(_x, _y); }
			int Distance(Galaxy* galaxy);
		};

		std::ostream& operator<<(std::ostream& os, Galaxy* galaxy);
		
		class GalaxyMap {
		public:
			GalaxyMap(std::string filemap, int timeExpansion);
		protected:
			int _timeExpansion;
			std::map<int, int> _nbGalaxiesPerLines;
			std::map<int, int> _nbGalaxiesPerColumns;
			std::vector<int> _linesIdTimeExpanded;
			std::vector<int> _columnsIdTimeExpanded;
			std::vector<Galaxy*> _galaxies;
		public:
			void ApplyTimeExpansionForGalaxy(Galaxy* galaxy);
			long long DistanceBetweenGalaxies();
		};
	}

	class Day11 : Day
	{
	public:
		Day11(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		D11::GalaxyMap* _galaxyMap;
	};

}