#include "pch.h"
#include "Day13.h"

void AdventOfCode23::Day13::Resolve()
{
	FillData();



}

void AdventOfCode23::Day13::FillData()
{
	int x = 0;
	std::string line;
	while (std::getline(_stream, line))
	{
		_lines.push_back( new std::string(line));
		int y = 0;
		for (char charLine : line)
		{
			if (x == 0)
			{
				_columns.push_back(new std::string(""+charLine));
			}
			else
			{
				_columns[y]->push_back(charLine);
			}
			y++;
		}
		x++;
	}
	_stream.close();
}

int AdventOfCode23::Day13::VerifyMirroring(std::vector<std::string*> stringVector)
{


	return 0;
}

bool AdventOfCode23::Day13::VerifyMirroring(std::vector<std::string*> stringVector, int index)
{
	bool isMirroring = true;

	int previousIndex = index;
	int nextIndex = index + 1;

	return isMirroring;
}

bool AdventOfCode23::Day13::VerifyMirroring(std::string* leftString, std::string* rightString)
{
	return !leftString->compare(*rightString);
}


