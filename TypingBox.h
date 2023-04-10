#pragma once

#include <SFML/Graphics.hpp>
#include "Template.h"

struct TypingBox {
protected:
	double x, y, width, height;
	double xWarning, yWarning, widthWarning, heightWarning;
	bool displayingWarning;
	TypingBoxMode typingMode;
	bool reading;
	std::string text, warning; 
	sf::Font* font;
	sf::Time time;
	int maxCharacter, minValue, maxValue;
	bool displayingLine;
public:
	TypingBox(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, 
		double xWarning = 0.f, double yWarning = 0.f, double widthWarning = 0.f, double heightWarning = 0.f,
		TypingBoxMode typingMode = singleNumber, sf::Font *font = nullptr, int maxCharacter = 5, int minValue = 0, int maxValue = 10);
	bool isReading();
	std::string getText();
	void setWarning();
	void setText(std::string newText);
	void insert(int key);
	void deleteBack();
	void readKey(int key);
	int getInt();
	int getProperInt();
	std::vector <int>  getListInt();
	void update(sf::Time deltaT);
	void clickOn(double x, double y);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};

struct BigTypingBox : public TypingBox{
private:
	double outerX, outerY, outerWidth, outerHeight, valueWidth, outlineSize;
	std::string name;
	bool drawable, typingBoxDrawable;
public:
	BigTypingBox(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, double valueWidth = 0.f, double outlineSize = 0.f, std::string name = "",
		double xWarning = 0.f, double yWarning = 0.f, double widthWarning = 0.f, double heightWarning = 0.f,
		TypingBoxMode typingMode = singleNumber, sf::Font* font = nullptr, int maxCharacter = 5, int minValue = 0, int maxValue = 10,
		bool drawable = true, bool typingBoxDrawable = true);
	void setDrawable(bool val);
	void setTypingBoxDrawable(bool val);
	void setName(std::string newName);
	void drawAll(sf::RenderWindow& window, ColorTheme theme);
};