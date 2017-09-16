#pragma once
#include <SFML\Graphics.hpp>
void setupGlobals();

extern sf::Vector2i screenSize;
extern int gridStep;
extern int botsNumber;
extern int codeSegmentSize;
extern int codeSegmentsNumber;
extern int foodSaturation;
extern int mutationRate;
extern int startSaturation;
extern int foodAmount;
extern int maxlifetime;
extern float mutationProbability;
extern sf::Vector2i fieldSize;
enum Command { GOUP, GODOWN, GOLEFT, GORIGHT, EATUP, EATDOWN, EATLEFT, EATRIGHT, ROTLEFT, ROTRIGHT, DONOTHING };
enum Direction { UP, DOWN, LEFT, RIGHT };
extern const int CommandSize;

const bool operator < (const sf::Vector2i v1, const sf::Vector2i v2);
const bool operator > (const sf::Vector2i v1, const sf::Vector2i v2);
const bool operator >= (const sf::Vector2i v1, const sf::Vector2i v2);
sf::Vector2i operator << (const sf::Vector2i pos, const Direction dir);
sf::Vector2i operator >> (const sf::Vector2i pos, const Direction dir);
sf::Vector2i operator ^ (const sf::Vector2i pos, const Direction dir);
sf::Vector2i operator & (const sf::Vector2i pos, const Direction dir);