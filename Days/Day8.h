#pragma once
#include "Day.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ostream>
namespace AdventOfCode23 {
	namespace D8 {
		enum Directions {
			NONE,
			L,
			R
		};

		Directions GetDirection(char dir);

		class Path {
		public:
			//Path(std::string name) : _name(name), _leftPath(nullptr), _rightPath(nullptr) {};
			Path(std::string name);
			//Path(std::string name, Path* leftPath, Path* rightPath) : _name(name), _leftPath(leftPath), _rightPath(rightPath) {}
			Path(std::string name, Path* leftPath, Path* rightPath);
		private:
			std::string _name;
			Path* _leftPath;
			Path* _rightPath;
			bool _canBeEnding;
		public:
			Path* GetPath(Directions direction);
			void SetPath(Directions direction, Path* path);
			std::string GetName() { return _name; }
			bool CanBeEnding() { return _canBeEnding; }
		};

		std::ostream& operator<<(std::ostream& os, Path* path);

	}
	class Day8 : Day
	{
	public:
		Day8(char* fileName, int stepNumber) : Day(fileName, stepNumber) {};
		void Resolve();
		int FollowInstructions();
		int FollowInstructionsForEachAPath();
		int FollowInstructionsForEachsinglePath(D8::Path* path);
		D8::Path* GetPath(std::string pathName);

		bool EachAPathAtEnd();
		void ApplyDirectionToAPathes(D8::Directions direction);
	protected:
		std::vector<D8::Directions> _directions;
		std::vector<D8::Path*> _APathes;
		std::map<std::string, D8::Path*> _pathes;
	};
}
