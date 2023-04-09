#include <iostream>
#include "Scrubber.h"

Scrubber::Scrubber(double _x, double _y, double _width, double _height, double _zipWidth, DataStructure* _ds):
	x(_x), y(_y), width(_width), height(_height), zipWidth(_zipWidth), ds(_ds), isChangingFrame(false) {}

void Scrubber::setDS(DataStructure* newDS) {
	ds = newDS;
}

void Scrubber::setIsAnimating(bool val) {
	ds->setIsAnimating(val);
}

void Scrubber::setNearestFrame(double mouseX, double mouseY) {
	int resID = -1;
	double stepWidth = width / (ds->listFrame.size() - 1);
	for (int i = 0; i < ds->listFrame.size(); i++) {
		double hereX = x + i * stepWidth;
		if (resID == -1 || abs(hereX - mouseX) < abs(x + resID * stepWidth - mouseX)) {
			resID = i;
		}
	}
	ds->setFrame(resID);
}

void Scrubber::handleMousePressed(double mouseX, double mouseY) {
	if (mouseX < x || mouseX > x + width || mouseY < y || mouseY > y + height) {
		return;
	}
	isChangingFrame = true;
	preIsAnimating = ds->isAnimating;
	setIsAnimating(false);
	setNearestFrame(mouseX, mouseY);
}

void Scrubber::handleMouseMove(double mouseX, double mouseY) {
	if (!isChangingFrame) {
		return;
	}
	setNearestFrame(mouseX, mouseY);
}

void Scrubber::handleMouseReleased(double mouseX, double mouseY) {
	if (!isChangingFrame) {
		return;
	}
	isChangingFrame = false;
	setIsAnimating(preIsAnimating);
	setNearestFrame(mouseX, mouseY);
}

void Scrubber::handleKeyPressed(int key) {
	if (key == sf::Keyboard::Space) {
		if (ds->frameQueue.empty() && ds->listFrame.size() > 1) {
			setIsAnimating(true);
			ds->setFrame(0);
		}
		else {
			setIsAnimating(ds->isAnimating ^ 1);
		}
	}
}

void Scrubber::draw(sf::RenderWindow& window, ColorTheme theme) {
	sf::RectangleShape bar(sf::Vector2f(width, height));
	bar.setPosition(x, y);
	bar.setFillColor(scrubberRemainColor[theme]);
	window.draw(bar);
	double stepWidth = width / (ds->listFrame.size() - 1);
	sf::RectangleShape passedBar(sf::Vector2f(stepWidth * ds->curFrame, height));
	passedBar.setPosition(x, y);
	passedBar.setFillColor(scrubberPassedColor[theme]);
	window.draw(passedBar);
	sf::RectangleShape zip(sf::Vector2f(zipWidth, height * 1.2));
	zip.setOrigin(sf::Vector2f(zipWidth / 2, height * 0.6));
	zip.setPosition(x + stepWidth * ds->curFrame, y + height * 0.5);
	zip.setFillColor(scrubberZipColor[theme]);
	window.draw(zip);
}