#include "CodeSegment.h"



CodeSegment::CodeSegment()
{
	iter = Commands.begin();
}

void CodeSegment::Mutate()
{
	if (Commands.size() != 0)
	{
		for (int i = 0; i < mutationRate; i++)
		{
			int pos = rand() % Commands.size();
			Commands[pos] = (Command)(rand() % CommandSize);
		}
	}
}

void CodeSegment::ResetIterator()
{
	iter = Commands.begin();
}

Command CodeSegment::GetNext()
{
	if (iter == Commands.end())
	{
		return DONOTHING;
	}
	Command temp = *iter;
	iter++;
	return temp;
}

bool CodeSegment::IsEOC()
{
	return iter == Commands.end();
}

void CodeSegment::Clear()
{
	iter = Commands.begin();
	Commands.clear();
}

void CodeSegment::PushBack(Command cmd)
{
	Commands.push_back(cmd);
}

CodeSegment::~CodeSegment()
{
}
