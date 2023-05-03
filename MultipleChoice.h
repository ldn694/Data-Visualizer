#pragma once

#include "Template.h"
#include "MyShape.h"
#include "Box.h"

struct MultipleChoice {
private:
	double x, y, width, height, stepHeight, letterSize;
	std::vector <std::string> choices;
	std::vector <sf::CircleShape> circles;
	std::vector <Box> listBox;
	sf::Font* font;
	int curChoice;
	Box outerBox;
public:
	MultipleChoice(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, std::vector <std::string> choices = {}, sf::Font* font = nullptr, int curChoice = 0);
	int getChoice();
	bool handleMousePressed(double x, double y);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};
