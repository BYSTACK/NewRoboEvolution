#include "World.h"



World::World() : generationLifetime(0), generationNumber(0), generationBest(0), generationAvg(0), generationBestEver(0)
{
	MakeBackground();
	sf::Image wallmap;
	wallmap.loadFromFile("wallmap.png");

	int w = wallmap.getSize().x;
	int h = wallmap.getSize().y;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (wallmap.getPixel(i, j) == sf::Color::Black)
			{
				Walls.push_back(Wall(sf::Vector2i(i, j)));
			}
			else
			{
				GoodPositions.push_back(sf::Vector2i(i, j));
			}
		}
	}
	CreateRandomBots();
}

std::string World::GetRobotCode(sf::Vector2i pos)
{
	Robot* bot = nullptr;
	for (int i = 0; i < Bots.size(); i++)
	{
		if (Bots[i].GetPosition() == pos)
		{
			bot = &Bots[i];
			break;
		}
	}
	if (bot == nullptr)
	{
		return "";
	}

	std::string s;
	for (int i = 0; i < codeSegmentsNumber; i++)
	{
		switch (i)
		{
		case 0:
			s.append("Wall on left:");
			break;
		case 1:
			s.append("Wall in front:");
			break;
		case 2:
			s.append("Wall on right:");
			break;
		case 3:
			s.append("\n");
			s.append("Food on left:");
			break;
		case 4:
			s.append("Food in front:");
			break;
		case 5:
			s.append("Food on right:");
			break;
		case 6:
			s.append("Loop:");
			break;
		}

		s.append("\n");

		bot->code[i].ResetIterator();
		while (!bot->code[i].IsEOC())
		{
			Command cmd = bot->code[i].GetNext();
			switch (cmd)
			{
			case GOUP:
				s.append("Move forward");
				break;
			case GODOWN:
				s.append("Move backward");
				break;
			case GOLEFT:
				s.append("Move left");
				break;
			case GORIGHT:
				s.append("Move right");
				break;
			case EATUP:
				s.append("Eat in front");
				break;
			case EATDOWN:
				s.append("Eat behind");
				break;
			case EATLEFT:
				s.append("Eat on left");
				break;
			case EATRIGHT:
				s.append("Eat on right");
				break;
			case ROTLEFT:
				s.append("Turn left");
				break;
			case ROTRIGHT:
				s.append("Turn right");
				break;
			case DONOTHING:
				s.append("Do nothing");
				break;
			}
			s.append("\n");
		}
		s.append("\n");
	}
	return s;
}

void World::Reset()
{
	generationAvg = 0;
	generationBest = 0;
	generationLifetime = 0;
	generationNumber = 0;
	CreateRandomBots();
}

void World::MakeBackground()
{
	BackgroundImage.create(screenSize.x, screenSize.y, sf::Color(119, 171, 255));
	for (int i = 0; i < fieldSize.x; i++)
	{
		for (int j = 0; j < fieldSize.y; j++)
		{
			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
			{
				for (int k = 0; k < gridStep; k++)
				{
					for (int m = 0; m < gridStep; m++)
					{
						BackgroundImage.setPixel(i*gridStep + k, j*gridStep + m, sf::Color(96, 134, 196));
					}
				}
			}
		}
	}
	BackgroundTexture.loadFromImage(BackgroundImage);
	BackgroundSprite.setTexture(BackgroundTexture);
}

void World::Draw(sf::RenderWindow& window)
{
	window.draw(BackgroundSprite);

	for (int i = 0; i < Bots.size(); i++)
	{
		window.draw(Bots[i].GetBody());
	}
	for (int i = 0; i < Walls.size(); i++)
	{
		window.draw(Walls[i].GetBody());
	}
	for (int i = 0; i < FoodObjects.size(); i++)
	{
		window.draw(FoodObjects[i].GetBody());
	}
}

void World::CreateRandomBots()
{
	Bots.clear();

	for (int i = 0; i < botsNumber; i++)
	{
		std::vector<CodeSegment>& code = CreateRandomCode();
		std::vector<Wall>& walls = Walls;
		Bots.push_back(Robot(GetGoodRandomPos(), code, &Walls, &FoodObjects, UP));
	}
}

void World::Update()
{
	int deadbots = 0;
	for (int i = 0; i < Bots.size(); i++)
	{
		Bots[i].Update();
		if (Bots[i].IsDead)
		{
			deadbots++;
		}
	}
	if (deadbots == botsNumber || generationLifetime > maxlifetime)
	{
		CalculateGenerationStats();
		Reproduce();
		FoodObjects.clear();
		generationLifetime = 0;
	}
	SpawnFood();
	generationLifetime++;
}

void World::CalculateGenerationStats()
{
	generationBest = generationLifetime;
	generationNumber++;
	generationBest = 0;
	for (int i = 0; i < Bots.size(); i++)
	{
		generationAvg += Bots[i].GetLifetime();
		if (generationBest < Bots[i].Lifetime)
		{
			generationBest = Bots[i].Lifetime;
		}
	}

	if (generationBestEver < generationBest)
	{
		generationBestEver = generationBest;
	}

	generationAvg /= botsNumber;
}

std::vector<CodeSegment> World::CreateRandomCode()
{
	std::vector<CodeSegment> codes;
	for (int j = 0; j < codeSegmentsNumber; j++)
	{
		CodeSegment code;
		for (int i = 0; i < codeSegmentSize; i++)
		{
			code.PushBack((Command)(rand() % CommandSize));
		}
		codes.push_back(code);
	}
	return codes;
}

void World::Reproduce()
{
	std::sort(Bots.begin(), Bots.end());
	Bots.erase(Bots.begin(), Bots.end() - botsNumber / 2);
	std::vector<Robot> newBots;

	while (newBots.size() != botsNumber)
	{
		int bot1 = GetWeightedRandomBot();
		int bot2 = GetWeightedRandomBot();
		std::vector<CodeSegment> code1 = Bots[bot1].code;
		std::vector<CodeSegment> code2 = Bots[bot2].code;

		std::vector<CodeSegment> newCode;
		for (int j = 0; j < codeSegmentsNumber; j++)
		{
			CodeSegment newCodeSegment;
			int rnd = rand() % 2;
			if (rnd == 0)
			{
				newCodeSegment = CodeSegment(code1[j]);
			}
			else
			{
				newCodeSegment = CodeSegment(code2[j]);
			}

			rnd = rand() % 100;
			if (rnd <= mutationProbability * 100)
			{
				newCodeSegment.Mutate();
			}

			newCode.push_back(newCodeSegment);
		}
		newBots.push_back(Robot(GetGoodRandomPos(), newCode, &Walls, &FoodObjects, UP));
	}
	Bots = newBots;
}

int World::GetWeightedRandomBot()
{
	int totalLifetime = 0;
	for (int i = 0; i < Bots.size(); i++)
	{
		totalLifetime += Bots[i].GetLifetime();
	}

	int botNum = rand() % totalLifetime;

	if (botNum == 0)
	{
		botNum++;
	}

	int i = 0;
	while (botNum > 0)
	{
		botNum -= Bots[i].GetLifetime();
		i++;
	}
	return i-1;
}

void World::SpawnFood()
{
	while (FoodObjects.size() < foodAmount)
	{

		FoodObjects.push_back(Food(GetGoodRandomPos()));
	}
}

sf::Vector2i World::GetGoodRandomPos()
{
	return GoodPositions[rand() % GoodPositions.size()];
}

World::~World()
{
}
