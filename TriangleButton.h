#pragma once

#include "Template.h"
#include "Color.h"

struct TriangleButton {
	double x, y, radius, outlineSize, rotation;
	ColorBoxType type;
	sf::CircleShape shape;
	TriangleButton(double x = 0.f, double y = 0.f, double radius = 0.f, double outlineSize = 0.f, double rotation = 0.f);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, ColorTheme theme);
	bool isInside(double x, double y);
};
