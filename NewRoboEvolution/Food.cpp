#include "Food.h"
#include "Globals.h"


Food::Food(sf::Vector2i& _pos) : pos(_pos)
{
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	body.setFillColor(sf::Color(0, 255, 59));
	body.setRadius((float)gridStep * 0.25f);
	body.setOrigin(-(float)gridStep * 0.25f, -(float)gridStep * 0.25f);
	body.setOutlineColor(sf::Color(7, 193, 51));
	body.setOutlineThickness(1.f);
}

sf::CircleShape& Food::GetBody()
{
	return body;
}

sf::Vector2i& Food::GetPosition()
{
	return pos;
}

bool Food::SetPosition(sf::Vector2i& _pos)
{
	if (_pos.x < 0 || _pos.y < 0 || _pos >= fieldSize)
	{
		return false;
	}
	pos = _pos;
	body.setPosition((float)(pos.x * gridStep), (float)(pos.y * gridStep));
	return true;
}

Food::~Food()
{
}
