#pragma once
#include "MyShape.h"
#include "Scrubber.h"

struct PlayButton {
	MyShape circle, triangle, pause, replay;
	double x, y, radius;
	DataStructure* ds;
	PlayButton(double x = 0.f, double y = 0.f, double radius = 0.f, DataStructure* ds = nullptr);
	void setDS(DataStructure* newDS);
	void handleMousePressed(double x, double y);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};