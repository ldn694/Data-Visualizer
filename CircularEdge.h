#pragma once
#include <SFML/Graphics.hpp>

struct CircularEdge {
private:
	double x1, y1, x2, y2, thickness, upward, leftward, shorten, progress;
	sf::Color color;
public:
	CircularEdge(double x1, double y1, double x2, double y2, sf::Color color, double thickness, double upward, double leftward, double shorten, double progress = 0);
	void draw(sf::RenderWindow &window);
	void setProgress(double newProgress);
};