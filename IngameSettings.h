#pragma once

#include "MediaControl.h"
#include "MultipleChoice.h"
#include "Switch.h"

struct IngameSettings {
private: 
	double x, y, width, height;
	DataStructure* ds;
	MediaControl mediaControl;
	MultipleChoice speedChoices;
	Switch descriptionSwitch, skipAnimationSwitch;
public:
	IngameSettings(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, DataStructure* ds = nullptr, ColorTheme theme = LightTheme);
	void setDS(DataStructure* newDS);
	void handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void handleMouseReleased(double x, double y);
	void handleKeyPressed(int key);
	void update(sf::Time deltaT);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};