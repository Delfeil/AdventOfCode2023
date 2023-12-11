#include "pch.h"
#include "Day10.h"

AdventOfCode23::D10::PipeType AdventOfCode23::D10::GetPipeType(char pipe)
{
	switch (pipe)
	{
	case '|':
		return D10::NS;
	case '-':
		return D10::WE;
	case 'L':
		return D10::NE;
	case 'J':
		return D10::NW;
	case '7':
		return D10::SW;
	case 'F':
		return D10::SE;
	case '.':
		return D10::NONE;
	case 'S':
		return D10::START;
	default:
		break;
	}
}

char AdventOfCode23::D10::GetPipeTypeChar(PipeType pipeType)
{
	switch (pipeType)
	{
	case AdventOfCode23::D10::START:
		return 'S';
		break;
	case AdventOfCode23::D10::NS:
		return '|';
		break;
	case AdventOfCode23::D10::WE:
		return '-';
		break;
	case AdventOfCode23::D10::NE:
		return 'L';
		break;
	case AdventOfCode23::D10::NW:
		return 'J';
		break;
	case AdventOfCode23::D10::SW:
		return '7';
		break;
	case AdventOfCode23::D10::SE:
		return 'F';
		break;
	case AdventOfCode23::D10::NONE:
		return '.';
		break;
	default:
		return 'N';
		break;
	}
}

AdventOfCode23::D10::Pipe::Pipe(char pipe, int x, int y)//, PipeMap* map)
{
	_type = GetPipeType(pipe);
	_coordinates = std::pair <int, int>(x, y);
	_stepValue = -1;
	//_map = map;
	DetermineNeighbors();
}

int AdventOfCode23::D10::Pipe::SetStepValue(int stepValue)
{
	if (_stepValue == -1 || _stepValue > stepValue)
		_stepValue = stepValue;
	return _stepValue;
}

void AdventOfCode23::D10::Pipe::DetermineNeighbors()
{
	//std::cout << "get neighbors coordinates: current coordinates: " << _coordinates.first << ", " << _coordinates.second << std::endl;
	switch (_type)
	{
	case AdventOfCode23::D10::START:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first - 1, _coordinates.second), //N0
			std::pair<int, int>(_coordinates.first, _coordinates.second - 1), //W1
			std::pair<int, int>(_coordinates.first, _coordinates.second + 1), //E2
			std::pair<int, int>(_coordinates.first + 1, _coordinates.second)  //S3
		};
		break;
	case AdventOfCode23::D10::NS:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first - 1, _coordinates.second),
			std::pair<int, int>(_coordinates.first + 1, _coordinates.second)
		};
		break;
	case AdventOfCode23::D10::WE:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first, _coordinates.second - 1),
			std::pair<int, int>(_coordinates.first, _coordinates.second + 1),
		};
		break;
	case AdventOfCode23::D10::NE:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first - 1, _coordinates.second),
			std::pair<int, int>(_coordinates.first, _coordinates.second + 1)
		};
		break;
	case AdventOfCode23::D10::NW:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first - 1, _coordinates.second),
			std::pair<int, int>(_coordinates.first, _coordinates.second - 1)
		};
		break;
	case AdventOfCode23::D10::SW:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first, _coordinates.second - 1),
			std::pair<int, int>(_coordinates.first + 1, _coordinates.second)
		};
		break;
	case AdventOfCode23::D10::SE:
		_neighborsCoordinates = {
			std::pair<int, int>(_coordinates.first, _coordinates.second + 1),
			std::pair<int, int>(_coordinates.first + 1, _coordinates.second)
		};
		break;
	case AdventOfCode23::D10::NONE:
		break;
	default:
		break;
	}
	//for (std::pair<int, int> neighborCoordinate : _neighborsCoordinates)
	//{
	//	//std::cout << " add neighbor: " << neighborCoordinate.first << ", " << neighborCoordinate.second << std::endl;
	//	//_neighborsPipes.push_back(_map->GetPipe(neighborCoordinate));
	//}
}

std::pair<int, int>* AdventOfCode23::D10::Pipe::GetNeighbor(std::pair<int, int> coordinatesFrom)
{
	return GetNeighbor(coordinatesFrom.first, coordinatesFrom.second);
}

std::pair<int, int>* AdventOfCode23::D10::Pipe::GetNeighbor(int xFrom, int yFrom)
{
	if (_type == PipeType::START)
		return nullptr;

	bool coordinatesInputIsNeighbor = AreCoordinatesANeighbor(xFrom, yFrom);
	if (!coordinatesInputIsNeighbor)
		return nullptr;
	
	for (int neighborId = 0; neighborId < _neighborsCoordinates.size(); neighborId++)
	{
		if (_neighborsCoordinates[neighborId].first != xFrom || _neighborsCoordinates[neighborId].second != yFrom) {
			return &_neighborsCoordinates[neighborId];
		}
	}
	return nullptr;
}

std::pair<int, int>* AdventOfCode23::D10::Pipe::GetNeighbor(StartDirection direction)
{
	if (_type != PipeType::START)
	{
		return nullptr;
	}
	switch (direction)
	{
	case AdventOfCode23::D10::N:
		return &_neighborsCoordinates[0];
		break;
	case AdventOfCode23::D10::E:
		return &_neighborsCoordinates[2];
		break;
	case AdventOfCode23::D10::S:
		return &_neighborsCoordinates[3];
		break;
	case AdventOfCode23::D10::W:
		return &_neighborsCoordinates[1];
		break;
	default:
		return nullptr;
		break;
	}
}

bool AdventOfCode23::D10::Pipe::AreCoordinatesANeighbor(int x, int y)
{
	bool coordinatesInputIsNeighbor = false;
	for (std::pair<int, int> coordiantes : _neighborsCoordinates)
	{
		//std::cout << "Compare coordinates: " << x << ", " << y << " == " << coordiantes.first << ", " << coordiantes.second << std::endl;
		if ((coordiantes.first == x) && (coordiantes.second == y))
		{
			coordinatesInputIsNeighbor = true;
		}
	}
	return coordinatesInputIsNeighbor;
}

AdventOfCode23::D10::PipeMap::PipeMap()
{
}

AdventOfCode23::D10::PipeMap::PipeMap(std::string filemap)
{
	_startPipe = nullptr;
	std::ifstream stream;
	stream.open(filemap);
	std::string line;
	int x = 0;
	while (std::getline(stream, line))
	{
		//std::cout << line << std::endl;
		int y = 0;
		std::vector<Pipe*> pipeLine;
		for (char pipeChar : line)
		{
			//std::cout << "Create pipe: " << pipeChar << std::endl;
			Pipe* pipe = new Pipe(pipeChar, x, y);
			if (pipe->GetType() == D10::START)
				_startPipe = pipe;
			pipeLine.push_back(pipe);
			//_pipesMap[x][y] = pipe;// , this);
			y++;
		}
		_pipesMap.push_back(pipeLine);
		x++;
	}
	stream.close();
	std::cout << "Map created\n";

	DebugPipe(56, 45);

	DeterminePathsFormStart();
}

AdventOfCode23::D10::Pipe* AdventOfCode23::D10::PipeMap::GetPipe(int x, int y)
{
	if (x < 0 || x >= _pipesMap.size())
		return nullptr;

	if (y < 0 || y >= _pipesMap[x].size())
		return nullptr;
	return _pipesMap[x][y];
}

AdventOfCode23::D10::Pipe* AdventOfCode23::D10::PipeMap::GetPipe(std::pair<int, int> coordinates)
{
	return GetPipe(coordinates.first, coordinates.second);
}

void AdventOfCode23::D10::PipeMap::DeterminePathsFormStart()
{
	_pathFromStart.push_back(new Path(StartDirection::N, _startPipe, this));
	_pathFromStart.push_back(new Path(StartDirection::S, _startPipe, this));
	_pathFromStart.push_back(new Path(StartDirection::E, _startPipe, this));
	_pathFromStart.push_back(new Path(StartDirection::W, _startPipe, this));
}

int AdventOfCode23::D10::PipeMap::GetFarthestStepFromStart()
{
	int farthestStepNumber = INT32_MAX;
	for (Path* path : _pathFromStart)
	{
		std::cout << "Path: " << path->GetStartDirection() << " is loop: " << path->IsLooping() << " => " << path->GetFarthestStepNumber() << std::endl;

		if (path->IsLooping() && farthestStepNumber >= path->GetFarthestStepNumber())
		{
			farthestStepNumber = path->GetFarthestStepNumber();
		}
	}
	return farthestStepNumber;
}

void AdventOfCode23::D10::PipeMap::DebugPipe(int x, int y)
{
	Pipe* pipe = GetPipe(x, y);
	if (pipe == nullptr)
	{
		std::cout << "No pipe at coordiantes " << x << ", " << y << std::endl;
		return;
	}
	std::cout << "===> pipe " << GetPipeTypeChar(pipe->GetType()) << " at coordinates: " << pipe->GetCoordinates().first << ", " << pipe->GetCoordinates().second << std::endl;
	for (std::pair<int, int> neighbor : pipe->GetNeighborsCoordinates())
	{
		Pipe* neightborPipe = GetPipe(neighbor);
		if (neightborPipe == nullptr)
		{
			std::cout << "No neighbor pipe at coordiantes " << neighbor.first << ", " << neighbor.second << std::endl;

		}
		else
		{
			std::cout << "L> neighbor pipe " << GetPipeTypeChar(neightborPipe->GetType()) << " at coordinates: " << neightborPipe->GetCoordinates().first << ", " << neightborPipe->GetCoordinates().second << std::endl;

		}
	}
}

AdventOfCode23::D10::Path::Path(StartDirection startdirection, Pipe* start, PipeMap* map)
{
	_startDirection = startdirection;
	_start = start;
	_path.push_back(start);
	_map = map;
	_farthestStepNumber = 0;
	std::cout << "========\nPath direction: " << _startDirection << "\n =======" << std::endl;
	FollowPath();
}

void AdventOfCode23::D10::Path::FollowPathRecursive()
{
	_start->SetStepValue(0);
	Pipe* currentPipe = _start;
	std::pair<int, int>* nextCoordinates = _start->GetNeighbor(_startDirection);
	if (nextCoordinates == nullptr)
		return;
	Pipe* nextPipe = _map->GetPipe(nextCoordinates->first, nextCoordinates->second);
	std::cout << "next Pipe " << GetPipeTypeChar(nextPipe->GetType()) << " coordiantes: " << nextCoordinates->first << ", " << nextCoordinates->second << std::endl;
	if (nextPipe == nullptr)
	{
		return;
	}
	FollowPathRecursive(_start, nextPipe, 1);
}

void AdventOfCode23::D10::Path::FollowPathRecursive(Pipe* previousPipe, Pipe* currentPipe, int stepNumber)
{
	if (currentPipe->GetType() == PipeType::START)
	{
		_loop = true;
		return;
	}
	else if (currentPipe->GetType() == PipeType::NONE)
	{
		return;
	}
	int effectiveStepNumber = currentPipe->SetStepValue(stepNumber);
	if (effectiveStepNumber >= _farthestStepNumber)
	{
		_farthestStepNumber = effectiveStepNumber;
	}

	_path.push_back(currentPipe);

	std::pair<int, int>* nextCoordinates = currentPipe->GetNeighbor(previousPipe->GetCoordinates());
	if (nextCoordinates != nullptr)
	{

		Pipe* nextPipe = _map->GetPipe(*(nextCoordinates));
		if (nextPipe == nullptr)
		{
			std::cout << "no next Pipe for coordinates: " << nextCoordinates->first << ", " << nextCoordinates->second << std::endl;
			return;
		}
		std::cout << "next Pipe " << GetPipeTypeChar(nextPipe->GetType()) << " coordiantes: " << nextPipe->GetCoordinates().first << ", " << nextPipe->GetCoordinates().second
			<< "| Strp Number : " << stepNumber << " _farthestStepNumber: " << _farthestStepNumber << std::endl;
		FollowPathRecursive(currentPipe, nextPipe, (stepNumber + 1));
	}
}

void AdventOfCode23::D10::Path::FollowPath()
{
	int stepNumber = 0;
	_start->SetStepValue(stepNumber);
	stepNumber++;
	Pipe* currentPipe = _start;
	std::pair<int, int>* nextCoordinates = _start->GetNeighbor(_startDirection);
	if (nextCoordinates == nullptr)
		return;
	Pipe* nextPipe = _map->GetPipe(nextCoordinates->first, nextCoordinates->second);
	_map->DebugPipe(nextCoordinates->first, nextCoordinates->second);
	std::cout << "start Coordinates: " << currentPipe->GetCoordinates().first << ", " << currentPipe->GetCoordinates().second << std::endl;
	if (!nextPipe->AreCoordinatesANeighbor(_start->GetCoordinates().first, _start->GetCoordinates().second))
	{
		std::cout << "ici\n";
		return;
	}
	if (nextPipe == nullptr)
	{
		return;
	}
	std::cout << "next Pipe " << GetPipeTypeChar(nextPipe->GetType()) << " coordiantes: " << nextCoordinates->first << ", " << nextCoordinates->second << std::endl;
	Pipe* previousPipe;
	bool ended = false;
	while (!ended)
	{
		previousPipe = currentPipe;
		currentPipe = nextPipe;
		if (currentPipe->GetType() == PipeType::START)
		{
			ended = true;
			_loop = true;
			break;
		}
		else if (currentPipe->GetType() == PipeType::NONE)
		{
			ended = true;
			break;
		}

		int effectiveStepNumber = currentPipe->SetStepValue(stepNumber);
		if (effectiveStepNumber >= _farthestStepNumber)
		{
			_farthestStepNumber = effectiveStepNumber;
		}
		_path.push_back(currentPipe);

		std::pair<int, int>* nextCoordinates = currentPipe->GetNeighbor(previousPipe->GetCoordinates());
		if (nextCoordinates != nullptr)
		{
			nextPipe = _map->GetPipe(*(nextCoordinates));
			/*std::cout << "next Pipe " << GetPipeTypeChar(nextPipe->GetType()) << " coordiantes: " << nextPipe->GetCoordinates().first << ", " << nextPipe->GetCoordinates().second
				<< "| Strp Number : " << stepNumber << " _farthestStepNumber: " << _farthestStepNumber << std::endl;*/
			if (nextPipe == nullptr)
			{
				std::cout << "no next Pipe for coordinates: " << nextCoordinates->first << ", " << nextCoordinates->second << std::endl;
				ended = true;
				break;
			}
		}
		stepNumber++;
	}
}

//AdventOfCode23::Day10::Day10(char* fileName, int stepNumber) : Day(fileName, stepNumber)
//{
//	_pipeMap = D10::PipeMap(_fileName);
//}

void AdventOfCode23::Day10::Resolve()
{
	_pipeMap = D10::PipeMap(_fileName);

	int farthestStepNumber = _pipeMap.GetFarthestStepFromStart();
	std::cout << "farthestStepNumber = " << farthestStepNumber << std::endl;
}
