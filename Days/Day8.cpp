#include "pch.h"
#include "Day8.h"

void AdventOfCode23::Day8::Resolve()
{
	std::string line;
	std::getline(_stream, line);
	for (int i = 0; i < line.size(); i++)
	{
		_directions.push_back(AdventOfCode23::D8::GetDirection(line[i]));
	}

	std::string patternPathNames("[A-Z]+");
	std::regex rPatternPathNames(patternPathNames);

	while (std::getline(_stream, line))
	{
		if (line.empty())
		{
			continue;
		}
		std::regex_iterator<std::string::iterator> ritPathName(line.begin(), line.end(), rPatternPathNames);
		std::regex_iterator<std::string::iterator> rend;
		
		int regexId = 0;
		std::string pathName;
		std::string pathLeftName;
		std::string pathRightName;
		while (ritPathName != rend)
		{
			switch (regexId)
			{
			case 0:
				pathName = ritPathName->str();
			case 1:
				pathLeftName = ritPathName->str();
			case 2:
				pathRightName = ritPathName->str();
			default:
				break;
			}

			regexId++;
			ritPathName++;
		}
		//std::cout << pathName << ": (" << pathLeftName << ", " << pathRightName << ")\n";
		D8::Path* currentPath = GetPath(pathName);
		D8::Path* leftPath = GetPath(pathLeftName);
		D8::Path* rightPath = GetPath(pathRightName);
		currentPath->SetPath(D8::Directions::L, leftPath);
		currentPath->SetPath(D8::Directions::R, rightPath);

		std::cout << currentPath << "\n";

		if (pathName[pathLeftName.size()-1] == 'A')
		{
			_APathes.push_back(currentPath);
		}

	}
	int nbInstructionFollowed = FollowInstructions();
	std::cout << "Nb instruction followed: " << nbInstructionFollowed << std::endl;
	//int nbInstructionFollowedForAPathes = FollowInstructionsForEachAPath();
	//std::cout << "Nb instruction followed for each Pathes To end: " << nbInstructionFollowedForAPathes << std::endl;

	for (int APathId = 0; APathId < _APathes.size(); APathId++)
	{
		D8::Path* aPath = _APathes[APathId];
		std::cout << aPath << std::endl;
		int nbInstructions = FollowInstructionsForEachsinglePath(aPath);
		std::cout << "nb Instructions to go to end: " << nbInstructions << std::endl;
	}
}

int AdventOfCode23::Day8::FollowInstructions()
{
	int NbInstructions = 0;
	D8::Path* currentPath = GetPath("AAA");
	bool endFound = false;
	while (!endFound)
	{
		endFound = !currentPath->GetName().compare("ZZZ");
		if (endFound)
		{
			break;
		}

		for (int directionId = 0; directionId < _directions.size(); directionId++)
		{
			D8::Directions direction = _directions[directionId];
			//std::cout << "move to direction : " << direction << std::endl;
			D8::Path* nextPath = currentPath->GetPath(direction);
			NbInstructions++;
			//std::cout << currentPath->ToString() << " ---> " << nextPath->ToString() << "Nb Instructions: " << NbInstructions << std::endl;
			currentPath = nextPath;
			endFound = !currentPath->GetName().compare("ZZZ");
			if (endFound)
			{
				break;
			}
		}
		if (endFound)
		{
			break;
		}
	}

	return NbInstructions;
}

int AdventOfCode23::Day8::FollowInstructionsForEachAPath()
{
	int NbInstructions = 0;
	bool endFound = false;
	while (!endFound)
	{
		endFound = EachAPathAtEnd();
		if (endFound)
		{
			break;
		}
		for (int directionId = 0; directionId < _directions.size(); directionId++)
		{
			D8::Directions direction = _directions[directionId];
			ApplyDirectionToAPathes(direction);
			NbInstructions++;
			endFound = EachAPathAtEnd();
			if (endFound)
			{
				break;
			}
		}
		if (endFound)
		{
			break;
		}
	}
	return NbInstructions;
}

int AdventOfCode23::Day8::FollowInstructionsForEachsinglePath(D8::Path* path)
{
	int NbInstructions = 0;
	bool endFound = false;
	D8::Path* currentPath = path;
	while (!endFound)
	{
		endFound = currentPath->CanBeEnding();
		if (endFound)
		{
			break;
		}
		for (int directionId = 0; directionId < _directions.size(); directionId++)
		{
			D8::Directions direction = _directions[directionId];
			D8::Path* nextPath = currentPath->GetPath(direction);
			currentPath = nextPath;
			NbInstructions++;
			endFound = currentPath->CanBeEnding();
			if (endFound)
			{
				break;
			}
		}
		if (endFound)
		{
			break;
		}
	}
	return NbInstructions;
}


AdventOfCode23::D8::Path* AdventOfCode23::Day8::GetPath(std::string pathName)
{
	D8::Path* path;
	path = _pathes[pathName];
	if (path == nullptr)
	{
		std::cout << "Create Path: " << pathName << std::endl;
		path = new D8::Path(pathName);
		_pathes[pathName] = path;
	}
	
	return path;
}

bool AdventOfCode23::Day8::EachAPathAtEnd()
{
	int nbAtEnd = 0;
	for (int pathId = 0; pathId < _APathes.size(); pathId++)
	{
		if (_APathes[pathId]->CanBeEnding())
		{
			nbAtEnd++;
		}
	}
	//std::cout << "nb at end " << nbAtEnd << " = " << _APathes.size() << std::endl;
	if (nbAtEnd == _APathes.size())
	{
		return true;
	}
	return false;
}

void AdventOfCode23::Day8::ApplyDirectionToAPathes(D8::Directions direction)
{
	//std::cout << "-----> " << direction << "\n";
	for (int pathId = 0; pathId < _APathes.size(); pathId++)
	{
		D8::Path* nextPath = _APathes[pathId]->GetPath(direction);
		//std::cout << "Apath " << pathId << " : " << _APathes[pathId] << " =move to= " << nextPath << std::endl;
		_APathes[pathId] = nextPath;
	}
	//std::cout << "-----\n";
}

AdventOfCode23::D8::Path::Path(std::string name)
{
	_name = name;
	if (name[name.size()-1] == 'Z')
	{
		_canBeEnding = true;
	}
	else {
		_canBeEnding = false;
	}

	_leftPath = nullptr;
	_rightPath = nullptr;
}

AdventOfCode23::D8::Path::Path(std::string name, Path* leftPath, Path* rightPath)
{
	_name = name;
	if (name[name.size() - 1] == 'Z')
	{
		_canBeEnding = true;
	}
	else {
		_canBeEnding = false;
	}

	_leftPath = leftPath;
	_rightPath = rightPath;
}

AdventOfCode23::D8::Path* AdventOfCode23::D8::Path::GetPath(Directions direction)
{
	switch (direction)
	{
	case AdventOfCode23::D8::L:
		return _leftPath;
		break;
	case AdventOfCode23::D8::R:
		return _rightPath;
		break;
	default:
		return	nullptr;
		break;
	}
}

void AdventOfCode23::D8::Path::SetPath(Directions direction, Path* path)
{
	if (direction == Directions::L)
		_leftPath = path;
	else if (direction == Directions::R)
		_rightPath = path;
}

AdventOfCode23::D8::Directions AdventOfCode23::D8::GetDirection(char dir)
{
	switch (dir)
	{
	case 'L':
		return Directions::L;
		break;
	case 'R':
		return Directions::R;
		break;
	default:
		return Directions::NONE;
		break;
	}
}

std::ostream& AdventOfCode23::D8::operator<<(std::ostream& os, Path* path)
{
	os << path->GetName() << " ";
	D8::Path* pathLeft = path->GetPath(D8::Directions::L);
	if (pathLeft != nullptr)
	{
		os << "(" + pathLeft->GetName();
	}
	else
	{
		os << "(_";
	}

	D8::Path* pathRight = path->GetPath(D8::Directions::R);
	if (pathRight != nullptr)
	{
		os << ", " + pathRight->GetName() + ")";
	}
	else
	{
		os << ",_)";
	}

	if (path->CanBeEnding())
	{
		os << " Can be an end";
	}
	else {
		os << " not an end";
	}
	return os;
}
