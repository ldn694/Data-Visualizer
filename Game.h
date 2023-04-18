#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Box.h"

struct Game
{
public:
	Game(sf::ContextSettings settings);
	void run();
private:
	void processEvents(sf::Clock& mClock);
	void update(sf::Time deltaT);
	void render();
	void handlePlayerInput();
	void runStack();
	void runQueue();
	void runSLL();
private:
	ColorTheme theme;
	sf::RenderWindow window;
	Box stackBox, queueBox, sllBox;
};