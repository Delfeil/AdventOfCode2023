#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
#include <utility>
namespace AdventOfCode23 {
	namespace D10 {
		enum PipeType {
			START,
			NS,
			WE,
			NE,
			NW,
			SW,
			SE,
			NONE
		};

		enum StartDirection {
			N,
			E,
			S,
			W
		};

		PipeType GetPipeType(char pipe);

		char GetPipeTypeChar(PipeType pipeType);

		class Pipe {
		public :
			Pipe(char pipe, int x, int y);// , PipeMap* map);
		protected:
			PipeType _type;
			std::pair<int, int> _coordinates;
			std::vector<std::pair<int, int>> _neighborsCoordinates;
			//std::vector<Pipe*> _neighborsPipes;
			int _stepValue;
			//PipeMap* _map;
		public:
			PipeType GetType() { return _type; }
			std::pair<int, int> GetCoordinates() { return _coordinates; }
			std::vector<std::pair<int, int>> GetNeighborsCoordinates() { return _neighborsCoordinates; }
			int GetStepValue() { return _stepValue; }
			int SetStepValue(int stepValue);
			void DetermineNeighbors();
			std::pair<int, int>* GetNeighbor(std::pair<int, int> coordinates);
			std::pair<int, int>* GetNeighbor(int x, int y);
			std::pair<int, int>* GetNeighbor(StartDirection direction);
			bool AreCoordinatesANeighbor(int x, int y);
			bool AreCoordinatesANeighbor(std::pair<int, int> coordinates) { return AreCoordinatesANeighbor(coordinates.first, coordinates.second); }
		};
		
		class Path;

		class PipeMap {
		public:
			PipeMap();
			PipeMap(std::string filemap);
		protected:
			std::vector<std::vector<Pipe*>> _pipesMap;
			Pipe* _startPipe = nullptr;
			std::vector<Path*> _pathFromStart;
		public:
			Pipe* GetPipe(int x, int y);
			Pipe* GetPipe(std::pair<int, int> coordinates);
			void DeterminePathsFormStart();
			int GetFarthestStepFromStart();
			void DebugPipe(int x, int y);
		};

		class Path {
		public:
			Path(StartDirection startdirection, Pipe* start, PipeMap* map);
		protected:
			StartDirection _startDirection;
			PipeMap* _map;
			Pipe* _start;
			std::vector<Pipe*> _path;
			bool _loop = false;
			int _farthestStepNumber;
		public:
			StartDirection GetStartDirection() { return _startDirection; }
			std::vector<Pipe*> GetPath() { return _path; }
			int GetFarthestStepNumber() { return _farthestStepNumber; }
			bool IsLooping() { return _loop; }
			void FollowPathRecursive();
			void FollowPathRecursive(Pipe* previousPipe, Pipe* currentPipe, int stepNumber);
			void FollowPath();
		};
	}
	class Day10 : Day
	{
	public:
		//Day10(char* fileName, int stepNumber);
		Day10(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
	protected:
		D10::PipeMap _pipeMap;
	};
}
