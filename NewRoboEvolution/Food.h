#pragma once
#include <SFML\Graphics.hpp>

class Food
{
private:
	sf::CircleShape body;
	sf::Vector2i pos;
public:
	Food(sf::Vector2i& _pos);
	sf::CircleShape& GetBody();
	sf::Vector2i& GetPosition();
	bool SetPosition(sf::Vector2i& pos);
	~Food();
};

