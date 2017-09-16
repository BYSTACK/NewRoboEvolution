#pragma once
#include <vector>
#include "Robot.h"
#include "Wall.h"
#include "Food.h"
#include "CodeSegment.h"
#include <algorithm>
#include <string>

class World
{
private:
	std::vector<Robot> Bots;
	std::vector<Wall> Walls;
	std::vector<Food> FoodObjects;
	std::vector<sf::Vector2i> GoodPositions;

	int generationLifetime;
	

	sf::Image BackgroundImage;
	sf::Texture BackgroundTexture;
	sf::Sprite BackgroundSprite;
	void MakeBackground();
	void Reproduce();
	void SpawnFood();
	void CalculateGenerationStats();
	int World::GetWeightedRandomBot();
	std::vector<CodeSegment> CreateRandomCode();
	sf::Vector2i GetGoodRandomPos();
public:
	int generationNumber;
	int generationBest;
	int generationBestEver;
	float generationAvg;
	World();
	//bool CompareBotsLifetime(Robot& b1, Robot& b2);
	void Draw(sf::RenderWindow& window);
	void Update();
	void CreateRandomBots();
	void World::Reset();
	std::string GetRobotCode(sf::Vector2i pos);
	~World();
};

