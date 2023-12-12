#include "pch.h"
#include "Day11.h"

void AdventOfCode23::D11::Galaxy::AddTimeExpansion(int timeExpansion)
{
	_x += timeExpansion;
	_y += timeExpansion;
}

void AdventOfCode23::D11::Galaxy::AddLineTimeExpansion(int timeExpansion)
{
	_x += timeExpansion;
}

void AdventOfCode23::D11::Galaxy::AddColumnTimeExpansion(int timeExpansion)
{
	_y += timeExpansion;
}

int AdventOfCode23::D11::Galaxy::Distance(Galaxy* galaxy)
{
	std::pair<int, int> galaxyCoordinates = galaxy->GetCoordinates();
	return (std::abs(_x - galaxyCoordinates.first) + std::abs(_y - galaxyCoordinates.second));
}

AdventOfCode23::D11::GalaxyMap::GalaxyMap(std::string filemap, int timeExpansion)
{
	_timeExpansion = timeExpansion;
	std::ifstream stream;
	stream.open(filemap);
	std::string line;
	int x = 0;
	while (std::getline(stream, line))
	{
		_nbGalaxiesPerLines[x] = 0;
		int y = 0;
		for (char lineChar : line)
		{
			if (x == 0)
			{
				_nbGalaxiesPerColumns[y] = 0;
			}
			if (lineChar == '#')
			{
				D11::Galaxy* galaxy = new Galaxy(x, y);
				_galaxies.push_back(galaxy);
				_nbGalaxiesPerLines[x] += 1;
				_nbGalaxiesPerColumns[y] += 1;
			}
			y++;
		}
		x++;
	}

	std::cout << "Empty lines: [";
	for (int x = 0; x < _nbGalaxiesPerLines.size(); x++)
	{
		if (_nbGalaxiesPerLines[x] == 0)
		{
			std::cout << x << ", ";
			_linesIdTimeExpanded.push_back(x);
		}
	}
	std::cout << " ] " << _linesIdTimeExpanded.size() << "\n";

	std::cout << "Empty columns: [";
	for (int y = 0; y < _nbGalaxiesPerColumns.size(); y++)
	{
		if (_nbGalaxiesPerColumns[y] == 0)
		{
			std::cout << y << ", ";
			_columnsIdTimeExpanded.push_back(y);
		}
	}
	std::cout << " ] " << _columnsIdTimeExpanded.size() << "\n";

	int galaxyId = 1;
	for (Galaxy* galaxy : _galaxies)
	{
		std::cout << "Galaxy: " << galaxyId << galaxy;
		ApplyTimeExpansionForGalaxy(galaxy);
		std::cout << "-> " << galaxy << std::endl;
		galaxyId++;
	}
}

void AdventOfCode23::D11::GalaxyMap::ApplyTimeExpansionForGalaxy(Galaxy* galaxy)
{
	int totalLinesTimeExpansion	= 0;
	int totalColumnTimeExpansion = 0;
	std::pair<int, int> galaxyCordinates = galaxy->GetCoordinates();

	int nbLinesBeforeGalaxy = 0;
	int nbColumnsBeforeGalaxy = 0;

	for (int x : _linesIdTimeExpanded)
	{
		if (galaxyCordinates.first > x)
		{
			nbLinesBeforeGalaxy++;
		}
	}

	if (nbLinesBeforeGalaxy > 0)
	{
		galaxy->AddLineTimeExpansion(nbLinesBeforeGalaxy * (_timeExpansion - 1));
	}

	for (int y : _columnsIdTimeExpanded)
	{
		if (galaxyCordinates.second > y)
		{
			nbColumnsBeforeGalaxy++;
		}
	}

	if (nbColumnsBeforeGalaxy > 0)
	{
		galaxy->AddColumnTimeExpansion(nbColumnsBeforeGalaxy * (_timeExpansion - 1));
	}
}

long long AdventOfCode23::D11::GalaxyMap::DistanceBetweenGalaxies()
{
	long long distanceBetweenGalaxies = 0;
	for (int firstGalaxyId = 0; firstGalaxyId < _galaxies.size()-1; firstGalaxyId++)
	{

		Galaxy* firstGalaxy = _galaxies[firstGalaxyId];

		for (int secondGalaxyId = firstGalaxyId + 1; secondGalaxyId < _galaxies.size(); secondGalaxyId++)
		{
			Galaxy* secondGalaxy = _galaxies[secondGalaxyId];
			int distanceBetween2Galaxies = firstGalaxy->Distance(secondGalaxy);
			distanceBetweenGalaxies += long long(distanceBetween2Galaxies);
			//std::cout << "Distance between: " << firstGalaxy << " - " << secondGalaxy << " = " << distanceBetween2Galaxies << " total: " << distanceBetweenGalaxies << std::endl;
		}
	}
	return distanceBetweenGalaxies;
}

void AdventOfCode23::Day11::Resolve()
{

	_galaxyMap = new D11::GalaxyMap(_fileName, _stepNumber);
	int distanceBetweenGalaxies = _galaxyMap->DistanceBetweenGalaxies();
	std::cout << distanceBetweenGalaxies << std::endl;
}

std::ostream& AdventOfCode23::D11::operator<<(std::ostream& os, Galaxy* galaxy)
{
	std::pair<int, int> galaxyCoordinates = galaxy->GetCoordinates();
	os << "# (" << galaxyCoordinates.first << ", " << galaxyCoordinates.second << ")";
	return os;
}