#include "Globals.h"
#include <fstream>

sf::Vector2i screenSize;
int gridStep;
int botsNumber;
int codeSegmentSize;
int codeSegmentsNumber;
int foodSaturation;
int mutationRate;
int startSaturation;
int foodAmount;
int maxlifetime;
float mutationProbability;
sf::Vector2i fieldSize;

const int CommandSize = 11;

void setupGlobals()
{
	screenSize.x = 1280;
	screenSize.y = 720;
	gridStep = 10;
	foodSaturation = 4;
	botsNumber = 30;
	codeSegmentSize = 6;
	codeSegmentsNumber = 7;
	fieldSize.x = 64;
	fieldSize.y = 72;
	mutationRate = 1;
	mutationProbability = 0.1f;
	startSaturation = 20;
	foodAmount = 150;
	maxlifetime = 6000;

	std::ifstream fin("config.txt");
	std::string input;

	while (fin >> input)
	{
		if (input == "screenWidth:")
		{
			fin >> screenSize.x;
		}
		else if (input == "screenHeight:")
		{
			fin >> screenSize.y;
		}
		else if (input == "gridStep:")
		{
			fin >> gridStep;
		}
		else if (input == "foodSaturation:")
		{
			fin >> foodSaturation;
		}
		else if (input == "botsNumber:")
		{
			fin >> botsNumber;
		}
		else if (input == "codeSegmentSize:")
		{
			fin >> codeSegmentSize;
		}
		else if (input == "fieldWidth:")
		{
			fin >> fieldSize.x;
		}
		else if (input == "fieldHeight:")
		{
			fin >> fieldSize.y;
		}
		else if (input == "mutationRate:")
		{
			fin >> mutationRate;
		}
		else if (input == "mutationProbability:")
		{
			fin >> mutationProbability;
		}
		else if (input == "startSaturation:")
		{
			fin >> startSaturation;
		}
		else if (input == "foodAmount:")
		{
			fin >> foodAmount;
		}
		else if (input == "maxLifetime:")
		{
			fin >> maxlifetime;
		}
	}
	fin.close();
}

const bool operator < (const sf::Vector2i v1, const sf::Vector2i v2)
{
	return v1.x < v2.x && v1.y < v2.y;
}

const bool operator > (const sf::Vector2i v1, const sf::Vector2i v2)
{
	return v1.x > v2.x || v1.y > v2.y;
}

const bool operator >= (const sf::Vector2i v1, const sf::Vector2i v2)
{
	return v1.x >= v2.x || v1.y >= v2.y;
}

sf::Vector2i operator << (const sf::Vector2i pos, const Direction dir) //Возвращает координаты клетки, которая бы находилась слева от робота, который находится на координатах входной клетки и смотрит в сторону dir
{
	switch (dir)
	{
	case LEFT:
		return sf::Vector2i(pos.x, pos.y + 1);
	case RIGHT:
		return sf::Vector2i(pos.x, pos.y - 1);
	case UP:
		return sf::Vector2i(pos.x - 1, pos.y);
	case DOWN:
		return sf::Vector2i(pos.x + 1, pos.y);
	}
	return pos;
}

sf::Vector2i operator >> (const sf::Vector2i pos, const Direction dir) //Тоже что и << только справа
{
	switch (dir)
	{
	case LEFT:
		return sf::Vector2i(pos.x, pos.y - 1);
	case RIGHT:
		return sf::Vector2i(pos.x, pos.y + 1);
	case UP:
		return sf::Vector2i(pos.x + 1, pos.y);
	case DOWN:
		return sf::Vector2i(pos.x - 1, pos.y);
	}
	return pos;
}

sf::Vector2i operator ^ (const sf::Vector2i pos, const Direction dir) //Тоже что и << только сверху
{
	switch (dir)
	{
	case LEFT:
		return sf::Vector2i(pos.x - 1, pos.y);
	case RIGHT:
		return sf::Vector2i(pos.x + 1, pos.y);
	case UP:
		return sf::Vector2i(pos.x, pos.y - 1);
	case DOWN:
		return sf::Vector2i(pos.x, pos.y + 1);
	}
	return pos;
}

sf::Vector2i operator & (const sf::Vector2i pos, const Direction dir) //Тоже что и << только снизу
{
	switch (dir)
	{
	case LEFT:
		return sf::Vector2i(pos.x + 1, pos.y);
	case RIGHT:
		return sf::Vector2i(pos.x - 1, pos.y);
	case UP:
		return sf::Vector2i(pos.x, pos.y + 1);
	case DOWN:
		return sf::Vector2i(pos.x, pos.y - 1);
	}
	return pos;
}