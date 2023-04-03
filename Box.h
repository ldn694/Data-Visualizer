#pragma once
#include <SFML/Graphics.hpp>
#include "Template.h"

const bool WITH_BORDER = true;
const bool NO_BORDER = false;

struct Box {
	double x1, y1, x2, y2, outlineSize, textSize;
	std::string text;
	sf::Font* font;
	std::vector <ColorBoxType> colorModes;
	bool isBorder;
	int curMode;
	Box(double x1 = 0.f, double y1 = 0.f, double x2 = 0.f, double y2 = 0.f,
		std::string text = "", sf::Font* font = nullptr, double textSize = 0.f,
		std::vector <ColorBoxType> colorModes = {},
		bool isBorder = false, double outlineSize = 0.f);
	void draw(sf::RenderWindow& window, ColorTheme theme);
	bool isInside(double x, double y);
	void toggleColorMode();
	void setColorMode(int mode);
};