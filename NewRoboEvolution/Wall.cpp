#include "Wall.h"
#include "Globals.h"


Wall::Wall(sf::Vector2i& _pos) : pos(_pos)
{
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	body.setFillColor(sf::Color(186,186,186));
	body.setSize(sf::Vector2f((float)gridStep, (float)gridStep));
	body.setOutlineColor(sf::Color::Black);
	body.setOutlineThickness(1.f);
}

sf::RectangleShape& Wall::GetBody()
{
	return body;
}

sf::Vector2i& Wall::GetPosition()
{
	return pos;
}

bool Wall::SetPosition(sf::Vector2i& _pos)
{
	if (_pos.x < 0 || _pos.y < 0 || _pos >= fieldSize)
	{
		return false;
	}
	pos = _pos;
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	return true;
}

Wall::~Wall()
{
}
