#pragma once
#include <SFML/Graphics.hpp>
#include "Template.h"
#include "Color.h"
#include "Box.h"

struct Switch {
private:
	double x, y, width, height, progress;
	Box outerBox;
	sf::RectangleShape bar, zipper;
	sf::Text nameText;
	sf::Time remainTime;
	bool state;
public:
	Switch(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, std::string name = "", sf::Font* font = nullptr, bool curState = 0);
	bool getState();
	void draw(sf::RenderWindow& window, ColorTheme theme);
	bool isInside(double x, double y);
	bool handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void update(sf::Time deltaT);
};
