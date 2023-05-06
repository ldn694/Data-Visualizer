#pragma once
#include <SFML/Graphics.hpp>
#include "Template.h"
#include "Color.h"

struct MyShape {
	sf::Texture texture;
	sf::Sprite sprite;
	double x, y, width, height;
	const sf::Color* color;
	MyShape(std::string filename, double x, double y, double width, double height, const sf::Color* color);
	bool isMousePressed(double x, double y);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void setOrigin(double x, double y);
	void setPosition(double x, double y);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};