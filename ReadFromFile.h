#pragma once
#include <iostream>
#include "Template.h"


struct ReadFromFile {
private:
	double x, y, width, height, xWarning, yWarning, widthWarning, heightWarning;
	sf::Font* font;
	std::string fileName, address, warning;
	bool isDisplaying, displayingWarning;
	int minValue, maxValue, maxSize;

public:
	ReadFromFile(double x, double y, double width, double height,
		double xWarning, double yWarning, double widthWarning, double heightWarning,
		sf::Font* font, int maxSize, int minValue, int maxValue);
	void handleMousePressed(double x, double y);
	std::vector <int> getListInt();
	void draw(sf::RenderWindow& window, ColorTheme theme);
	void setDisplaying(bool val);
	bool getDisplaying();
	void setWarning();
	void reset();
};