#pragma once
#include <SFML/Graphics.hpp>
#include "Template.h"

const bool WITH_BORDER = true;
const bool NO_BORDER = false;

struct Box {
private:
	double x1, y1, width, height, outlineSize, textSize;
	std::string text;
	sf::Font* font;
	std::vector <ColorBoxType> colorModes;
	bool isBorder, isDrawable;
	int curMode;
public:
	Box(double x1 = 0.f, double y1 = 0.f, double width = 0.f, double height = 0.f,
		std::vector <ColorBoxType> colorModes = {},
		std::string text = "", sf::Font* font = nullptr, double textSize = 0.f,
		bool isBorder = true, double outlineSize = outlineBox);
	double getOutlineSize();
	void setPosition(double x1, double y1);
	void draw(sf::RenderWindow& window, ColorTheme theme);
	bool isInside(double x, double y);
	void toggleColorMode();
	void setDrawable(bool drawable);
	void setColorMode(int mode);
};