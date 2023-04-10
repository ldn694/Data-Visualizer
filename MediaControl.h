#pragma once
#include <SFML/Graphics.hpp>
#include "Scrubber.h"
#include "PlayButton.h"

struct MediaControl {
	double x, y, width, height;
	PlayButton playButton;
	MyShape nextButton, prevButton, beginButton, endButton;
	Scrubber scrubber;
	DataStructure* ds;
	MediaControl(double x = 0.f, double y = 0.f, double width = 0.f, double height = 0.f, DataStructure* ds = nullptr);
	void setDS(DataStructure* newDS);
	void handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y);
	void handleMouseReleased(double x, double y);
	void handleKeyPressed(int key);
	void draw(sf::RenderWindow& window, ColorTheme theme);
};