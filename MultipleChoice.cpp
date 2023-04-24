#include <iostream>
#include <algorithm>
#include "MultipleChoice.h"
#include "Box.h"
MultipleChoice::MultipleChoice(double _x, double _y, double _width, double _height, std::vector <std::string> _choices, sf::Font* _font, int _curChoice) :
	x(_x), y(_y), width(_width), height(_height), choices(_choices), curChoice(_curChoice), font(_font)
{
	stepHeight = height / choices.size();
	double l = 0.f, r = 1000.f;
	for (int cnt = 0; cnt < 60; cnt++) {
		double mid = (l + r) / 2;
		double maxWidth = 0, maxHeight = 0;
		for (int i = 0; i < choices.size(); i++)
		{
			sf::Text text;
			text.setFont(*font);
			text.setString(choices[i]);
			text.setCharacterSize(mid);
			maxWidth = (maxWidth > text.getLocalBounds().width ? maxWidth : text.getLocalBounds().width);
			maxHeight = (maxHeight > text.getLocalBounds().height ? maxHeight : text.getLocalBounds().height);
		}
		if (maxWidth <= width * 0.6 && maxHeight <= stepHeight / 2) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	letterSize = l;
	circles.resize(choices.size());
	for (int i = 0; i < choices.size(); i++) {
		circles[i].setPointCount(pointCountCircle);
		circles[i].setRadius(std::min(stepHeight * 0.35, width * 0.05));
		circles[i].setOrigin(circles[i].getLocalBounds().width / 2, circles[i].getLocalBounds().height / 2);
		circles[i].setPosition(x + width * 0.85, y + stepHeight * (i + 0.5));
	}
}

bool MultipleChoice::handleMousePressed(double mouseX, double mouseY) {
	for (int i = 0; i < choices.size(); i++) {
		double dist = sqrt((mouseX - circles[i].getPosition().x) * (mouseX - circles[i].getPosition().x) + (mouseY - circles[i].getPosition().y) * (mouseY - circles[i].getPosition().y));
		if (dist <= circles[i].getRadius()) {
			curChoice = i;
			return true;
		}
	}
	return false;
}

int MultipleChoice::getChoice() {
	return curChoice;
}

void MultipleChoice::draw(sf::RenderWindow& window, ColorTheme theme) {
	Box outerBox(x, y, width, height, { MediaBox });
	outerBox.draw(window, theme);
	for (int i = 0; i < choices.size(); i++) {
		Box lineBox(x, y + stepHeight * i, width, stepHeight, {MediaBox});
		lineBox.draw(window, theme);
		sf::Text text;
		text.setString(choices[i]);
		text.setFont(*font);
		text.setCharacterSize(letterSize);
		text.setFillColor(choicesColor[theme]);
		text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
		text.setPosition(x + width * 0.4, y + stepHeight * (i + 0.5));
		window.draw(text);
		circles[i].setFillColor(choicesOuterCircleColor[theme]);
		window.draw(circles[i]);
	}
	sf::CircleShape curCircle;
	curCircle.setPointCount(pointCountCircle);
	curCircle.setRadius(std::min(stepHeight * 0.35, width * 0.05) * 0.65);
	curCircle.setOrigin(curCircle.getLocalBounds().width / 2, curCircle.getLocalBounds().height / 2);
	curCircle.setFillColor(choicesInnerCircleColor[theme]);
	curCircle.setPosition(circles[curChoice].getPosition());
	window.draw(curCircle);

}