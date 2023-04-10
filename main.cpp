#include <SFML/Graphics.hpp>
#include "Template.h"
#include "cassert"
#include <iostream>
#include "Game.h"
#include "StackStage.h"

int main()
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[i])) {
			assert(false);
		}
	}
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;
	Game game(settings);
	game.run();
	/*sf::Texture texture;
	std::cout << texture.loadFromFile("./resources/bomb.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::RenderWindow mWindow(sf::VideoMode(640, 480), "HEY");
	while (mWindow.isOpen()) {
		mWindow.clear();
		mWindow.draw(sprite);
		mWindow.display();
	}*/
}