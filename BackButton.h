#pragma once

#include "MyShape.h"

struct BackButton {
	MyShape arrow, square, innerSquare;
	BackButton(double x, double y, double width, double height);
	bool handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};