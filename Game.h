#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Graph.h"
#include "DataStructure.h"
#include "Stack.h"

const std::string fontName[] = { "arial.ttf" };
const int numFont = 1;
enum fontType {
	Arial
};

struct Game
{
public:
	Game(sf::ContextSettings settings);
	void run();
private:
	void processEvents();
	void update(sf::Time deltaT);
	void render();
	void handlePlayerInput(sf::Keyboard::Key Key, bool isMoving);
private:
	sf::RenderWindow window;
	Stack ds;
	std::vector <sf::Font> listFont;
	sf::Font* font(fontType id);
};