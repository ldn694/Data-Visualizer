#pragma once
#include "DataStructure.h"
#include "MyShape.h"

struct PlayButton {
	MyShape circle, triangle, pause, replay;
	double x, y, radius;
	DataStructure* ds;
	PlayButton(double x = 0.f, double y = 0.f, double radius = 0.f, DataStructure* ds = nullptr);
	void setDS(DataStructure* newDS);
	void handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};