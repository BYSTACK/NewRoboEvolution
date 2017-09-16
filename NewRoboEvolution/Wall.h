#pragma once
#include <SFML\Graphics.hpp>


class Wall
{
private:
	sf::RectangleShape body;
	sf::Vector2i pos;
public:
	Wall(sf::Vector2i& _pos);
	sf::RectangleShape& GetBody();
	sf::Vector2i& GetPosition();
	bool SetPosition(sf::Vector2i& pos);
	~Wall();
};

