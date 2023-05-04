#include <SFML/Graphics.hpp>
#include "Template.h"
#include "cassert"
#include <iostream>
#include "Game.h"

int main()
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[i])) {
			if (!listFont[i].loadFromFile(fontAlternativeName[i])) {
				assert(false);
			}
		}
	}
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	Game game(settings);
	game.run();
}