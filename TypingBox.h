#pragma once

#include <SFML/Graphics.hpp>
#include "Template.h"

struct TypingBox {
private:
	double x, y, width, height;
	bool onlyNumber, reading;
	std::string text; 
	sf::Font* font;
	sf::Time time;
	int minValue, maxValue;
	bool displayingLine;
public:
	TypingBox(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, bool onlyNumber = true, 
		sf::Font *font = nullptr, int minValue = 0, int maxValue = 10);
	bool isReading();
	std::string getText();
	void setText(std::string newText);
	void insert(int key);
	void deleteBack();
	void readKey(int key);
	int getInt();
	void update(sf::Time deltaT);
	void clickOn(double x, double y);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};

struct BigTypingBox {

};