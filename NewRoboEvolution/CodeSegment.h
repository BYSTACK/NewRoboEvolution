#pragma once
#include <vector>
#include "Globals.h"
#include <cstdlib>

class CodeSegment
{
private:
	std::vector<Command> Commands;
	std::vector<Command>::iterator iter;
public:
	CodeSegment();
	void Mutate();
	void ResetIterator();
	void Clear();
	void PushBack(Command);
	bool IsEOC();
	Command GetNext();
	~CodeSegment();
};

