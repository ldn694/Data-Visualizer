#pragma once
#include "DataStructure.h"

struct Scrubber {
private: 
	double x, y, width, height, zipWidth;
	DataStructure* ds;
	bool isChangingFrame, preIsAnimating, isHovering;
public:
	Scrubber(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, double zipWidth = 0.f, DataStructure* ds = nullptr);
	void setIsAnimating(bool val);
	void setNearestFrame(double x, double y);
	void handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y);
	void handleMouseReleased(double x, double y);
	void handleKeyPressed(int key);
	void setDS(DataStructure* newDS);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};