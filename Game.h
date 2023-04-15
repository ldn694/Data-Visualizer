#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Graph.h"
#include "DataStructure.h"
#include "Stack.h"
#include "SinglyLinkedList.h"
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
private:
	ColorTheme theme;
	sf::RenderWindow window;
	Box stackBox, queueBox;
};