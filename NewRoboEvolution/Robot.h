#pragma once
#include <SFML\Graphics.hpp>
#include "Globals.h"
#include <vector>
#include "CodeSegment.h"
#include "Wall.h"
#include "Food.h"

class Robot
{
private:
	sf::RectangleShape body;
	sf::Vector2i pos;
	Direction dir;
	std::vector<Wall>* Walls;
	std::vector<Food>* FoodObjects;

	int Saturation;
	bool IsThereWall(sf::Vector2i& pos);
	bool IsThereFood(sf::Vector2i& pos);
	void ExecuteCode(CodeSegment& code);
	void TryMoveToPos(sf::Vector2i& pos);
	void TryEat(sf::Vector2i& pos);
public:
	std::vector<CodeSegment> code; //0-wall left, 1 - wall forw, 2 - wall right, same with food, last always executes
	bool IsDead;
	int Lifetime;

	Robot(sf::Vector2i&, std::vector<CodeSegment>&, std::vector<Wall>*, std::vector<Food>*, Direction _dir);
	void Update();
	int GetLifetime();
	sf::RectangleShape& GetBody();
	sf::Vector2i& GetPosition();
	bool SetPosition(sf::Vector2i& pos);
	bool Robot::operator < (const Robot& str) const;
	~Robot();
};

