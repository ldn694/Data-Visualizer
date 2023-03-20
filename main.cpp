#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"

int main()
{
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