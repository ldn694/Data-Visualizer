#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Box.h"
#include "MyShape.h"

struct Game
{
public:
	Game(sf::ContextSettings settings);
	void run();
private:
	void processEvents();
	void update(sf::Time deltaT);
	void render();
	void handlePlayerInput();
	void runStack();
	void runQueue();
	void runSLL();
	void runDLL();
	void runCLL();
	void runStaticArray();
	void runDynamicArray();
private:
	ColorTheme theme;
	sf::RenderWindow window;
	Box stackBox, queueBox, sllBox, dllBox, cllBox, staticArrayBox, dynamicArrayBox;
	MyShape lightBulb, darkBulb, themeBox;
	sf::Text projName, description, author;
};