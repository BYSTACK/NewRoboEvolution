#include "Robot.h"

Robot::Robot(
	sf::Vector2i& _pos,
	std::vector<CodeSegment>& _code,
	std::vector<Wall>* _Walls,
	std::vector<Food>* _FoodObjects,
	Direction _dir) :
	pos(_pos),
	code(_code),
	Walls(_Walls),
	FoodObjects(_FoodObjects),
	dir(_dir),
	Lifetime(0),
	IsDead(false),
	Saturation(startSaturation)
{
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	body.setFillColor(sf::Color(128, 0, 0));
	body.setSize(sf::Vector2f((float)gridStep, (float)gridStep));
	body.setOutlineColor(sf::Color::White);
	body.setOutlineThickness(1.f);
}

sf::RectangleShape& Robot::GetBody()
{
	return body;
}

sf::Vector2i& Robot::GetPosition()
{
	return pos;
}

bool Robot::SetPosition(sf::Vector2i& _pos)
{
	if (_pos.x < 0 || _pos.y < 0 || _pos >= fieldSize)
	{
		return false;
	}
	pos = _pos;
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	return true;
}

void Robot::Update()
{
	if (!IsDead)
	{
		if (IsThereWall(pos << dir))
		{
			ExecuteCode(code[0]);
		}
		if (IsThereWall(pos ^ dir))
		{
			ExecuteCode(code[1]);
		}
		if (IsThereWall(pos >> dir))
		{
			ExecuteCode(code[2]);
		}
		if (IsThereFood(pos << dir))
		{
			ExecuteCode(code[3]);
		}
		if (IsThereFood(pos ^ dir))
		{
			ExecuteCode(code[4]);
		}
		if (IsThereFood(pos >> dir))
		{
			ExecuteCode(code[5]);
		}
		ExecuteCode(code[6]);

		Lifetime++;
		Saturation--;
		if (Saturation == 0)
		{
			IsDead = true;
			body.setFillColor(sf::Color(128, 128, 128));
		}
	}
}

int Robot::GetLifetime()
{
	return Lifetime;
}

void Robot::ExecuteCode(CodeSegment& code)
{
	code.ResetIterator();
	while (!code.IsEOC())
	{
		Command cmd = code.GetNext();
		switch (cmd)
		{
		case GOUP:
			TryMoveToPos(pos ^ dir);
			break;
		case GODOWN:
			TryMoveToPos(pos & dir);
			break;
		case GOLEFT:
			TryMoveToPos(pos << dir);
			break;
		case GORIGHT:
			TryMoveToPos(pos >> dir);
			break;
		case EATUP:
			TryEat(pos ^ dir);
			break;
		case EATDOWN:
			TryEat(pos & dir);
			break;
		case EATLEFT:
			TryEat(pos << dir);
			break;
		case EATRIGHT:
			TryEat(pos >> dir);
			break;
		case ROTLEFT:
			switch (dir)
			{
			case UP:
				dir = LEFT;
				break;
			case DOWN:
				dir = RIGHT;
				break;
			case LEFT:
				dir = DOWN;
				break;
			case RIGHT:
				dir = UP;
				break;
			}
			break;
		case ROTRIGHT:
			switch (dir)
			{
			case UP:
				dir = RIGHT;
				break;
			case DOWN:
				dir = LEFT;
				break;
			case LEFT:
				dir = UP;
				break;
			case RIGHT:
				dir = DOWN;
				break;
			}
			break;
		}
	}
}

void Robot::TryMoveToPos(sf::Vector2i& pos)
{
	if (!IsThereWall(pos))
	{
		SetPosition(pos);
	}
}

void Robot::TryEat(sf::Vector2i& pos)
{
	for (int i = 0; i < FoodObjects->size(); i++)
	{
		if ((*FoodObjects)[i].GetPosition() == pos)
		{
			FoodObjects->erase(FoodObjects->begin() + i);
			Saturation += foodSaturation;
			return;
		}
	}
}

bool Robot::IsThereWall(sf::Vector2i& pos)
{
	if (pos.x < 0 || pos.y < 0 || pos >= fieldSize)
	{
		return true;
	}
	for (int i = 0; i < Walls->size(); i++)
	{
		if ((*Walls)[i].GetPosition() == pos)
		{
			return true;
		}
	}
	return false;
}

bool Robot::IsThereFood(sf::Vector2i& pos)
{
	for (int i = 0; i < FoodObjects->size(); i++)
	{
		if ((*FoodObjects)[i].GetPosition() == pos)
		{
			return true;
		}
	}
	return false;
}

bool Robot::operator < (const Robot& str) const
{
	return (Lifetime < str.Lifetime);
}

Robot::~Robot()
{
}
