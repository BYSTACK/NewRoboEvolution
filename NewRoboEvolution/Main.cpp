#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "World.h"
#include <ctime>
#include <cstdlib>
#include <string>

int main()
{
	setupGlobals();
	srand((unsigned int)(time(0)));

	sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "New RoboEvolution!");
	window.setFramerateLimit(60);

	World world;

	bool paused = false;
	bool speedup = false;

	sf::Font font;
	font.loadFromFile("arial.ttf");

	sf::Text stats;
	stats.setFont(font);
	stats.setPosition(700, 10);
	stats.setFillColor(sf::Color::Black);
	stats.setOutlineColor(sf::Color::White);
	stats.setOutlineThickness(1.f);
	stats.setCharacterSize(20);

	sf::Text controls;
	controls.setFont(font);
	controls.setPosition(700, 120);
	controls.setCharacterSize(20);
	controls.setFillColor(sf::Color::Black);
	controls.setOutlineColor(sf::Color::White);
	controls.setOutlineThickness(1.f);
	controls.setString(sf::String("F5 - Restart\nP - Pause\nSpace - Speedup\nClick on bot to\nview it's code"));

	sf::Text robotCode;
	robotCode.setFont(font);
	robotCode.setPosition(1000, 10);
	robotCode.setFillColor(sf::Color::Black);
	robotCode.setOutlineColor(sf::Color::White);
	robotCode.setOutlineThickness(1.f);
	robotCode.setCharacterSize(16);

	sf::Text robotCode2;
	robotCode2.setFont(font);
	robotCode2.setPosition(1120, 10);
	robotCode2.setFillColor(sf::Color::Black);
	robotCode2.setOutlineColor(sf::Color::White);
	robotCode2.setOutlineThickness(1.f);
	robotCode2.setCharacterSize(16);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
				{
					world.Reset();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					paused = !paused;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					speedup = !speedup;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed)
			{
				std::string text = world.GetRobotCode(sf::Mouse::getPosition(window) / gridStep);
				if (text != "")
				{
					std::string text1 = text;
					text1.erase(text1.begin() + text1.find("\n\n\n"), text1.end());
					std::string text2 = text;
					text2.erase(text2.begin(), text2.begin() + text2.find("\n\n\n") + 3);
					robotCode.setString(sf::String(text1));
					robotCode2.setString(sf::String(text2));
				}
			}
		}

		window.clear();

		if (!paused)
		{
			if (speedup)
			{
				for (int i = 0; i < 200; i++)
				{
					world.Update();
				}
			}
			else
			{
				world.Update();
			}
		}

		world.Draw(window);
		stats.setString(sf::String(std::string("Generation " + std::to_string(world.generationNumber) + "\nBest Lifetime: " + std::to_string(world.generationBest) + "\nBest Lifetime Ever: " + std::to_string(world.generationBestEver) + "\nAverage Lifetime: " + std::to_string(world.generationAvg))));
		window.draw(stats);
		window.draw(controls);
		window.draw(robotCode);
		window.draw(robotCode2);
		window.display();
	}

	return 0;
}
