#include "MediaControl.h"

MediaControl::MediaControl(double _x, double _y, double _width, double _height, DataStructure* _ds) :
	x(_x), y(_y), width(_width), height(_height), ds(_ds),
	scrubber(x, y, width, height / 4, zipWidth),
	playButton(x + width * 0.5, y + height * 0.75, height / 4),
	prevButton("Images/backward.png", x + width * 2 / 6, y + height * 0.75, height / 4, height / 4, playButtonCircleColor),
	nextButton("Images/forward.png", x + width * 4 / 6, y + height * 0.75, height / 4, height / 4, playButtonCircleColor),
	beginButton("Images/skip_begin.png", x + width * 1 / 6, y + height * 0.75, height / 4, height / 4, playButtonCircleColor),
	endButton("Images/skip_end.png", x + width * 5 / 6, y + height * 0.75, height / 4, height / 4, playButtonCircleColor)
{
	
}


void MediaControl::setDS(DataStructure* newDS) {
	scrubber.setDS(newDS);
	playButton.setDS(newDS);
	ds = newDS;
}

void MediaControl::handleMousePressed(double x, double y) {
	scrubber.handleMousePressed(x, y);
	playButton.handleMousePressed(x, y);
	if (nextButton.isMousePressed(x, y)) {
		if (ds->curFrame + 1 < ds->listFrame.size()) {
			ds->setFrame(ds->curFrame + 1);
		}
	}
	if (prevButton.isMousePressed(x, y)) {
		if (ds->curFrame - 1 >= 0) {
			ds->setFrame(ds->curFrame - 1);
		}
	}
	if (beginButton.isMousePressed(x, y)) {
		ds->setFrame(0);
	}
	if (endButton.isMousePressed(x, y)) {
		ds->setFrame(ds->listFrame.size() - 1);
	}
}

void MediaControl::handleMouseMove(double x, double y) {
	scrubber.handleMouseMove(x, y);
}

void MediaControl::handleMouseReleased(double x, double y) {
	scrubber.handleMouseReleased(x, y);
}

void MediaControl::handleKeyPressed(int key) {
	scrubber.handleKeyPressed(key);
	if (key == (int)sf::Keyboard::Right) { //next
		if (ds->curFrame + 1 < ds->listFrame.size()) {
			ds->setFrame(ds->curFrame + 1);
		}
	}
	if (key == (int)sf::Keyboard::Left) { //prev
		if (ds->curFrame - 1 >= 0) {
			ds->setFrame(ds->curFrame - 1);
		}
	}
	if (key == (int)sf::Keyboard::Home) {
		ds->setFrame(0);
	}
	if (key == (int)sf::Keyboard::End) {
		ds->setFrame(ds->listFrame.size() - 1);
	}
}

void MediaControl::draw(sf::RenderWindow& window, ColorTheme theme) {
	scrubber.draw(window, theme);
	playButton.draw(window, theme);
	nextButton.draw(window, theme);
	prevButton.draw(window, theme);
	beginButton.draw(window, theme);
	endButton.draw(window, theme);
}
