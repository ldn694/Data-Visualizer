#include <iostream>
#include "TypingBox.h"
#include "Box.h"

TypingBox::TypingBox(double _x, double _y, double _width, double _height, bool _onlyNumber, sf::Font* _font, int _minValue, int _maxValue) :
	x(_x), y(_y), width(_width), height(_height), onlyNumber(_onlyNumber), font(_font), minValue(_minValue), maxValue(_maxValue)
{
	reading = false;
	displayingLine = true;
	if (onlyNumber) {
		text = intToString(getInt());
	}
}

bool TypingBox::isReading() {
	return reading;
}

std::string TypingBox::getText() {
	if (onlyNumber) {
		return (text.empty() ? "0" : text);
	}
	return text;
}

void TypingBox::setText(std::string newText) {
	if (onlyNumber) {
		text.clear();
		for (char x : newText) {
			if ('0' <= x && x <= '9') {
				text.push_back(x);
			}
		}
	}
	else {
		text = newText;
	}
}

int TypingBox::getInt() {
	int res = 0;
	for (char x : text) {
		res = res * 10 + x - '0';
	}
	return res;
}

void TypingBox::insert(int key) {
	if (key < 0 || key > 35) return;
	if (text.size() + 1 > maxLetter) {
		return;
	}
	if (onlyNumber) {
		if (key < 26) return;
	}
	char x = ((key < 26) ? char(key + 'a') : char(key - 26 + '0'));
	text.push_back(x);
	sf::Text Text;
	Text.setFont(*font);
	Text.setString(text);
	Text.setCharacterSize(height * 0.8);
	sf::FloatRect textRect = Text.getLocalBounds();
	if (textRect.width > width - 20) {
		text.pop_back();
	}
}

void TypingBox::deleteBack() {
	if (!text.empty()) {
		text.pop_back();
	}
}

void TypingBox::update(sf::Time deltaT) {
	if (time + deltaT >= flickeringTime) {
		displayingLine ^= 1;
		time = time + deltaT - flickeringTime;
	}
	else {
		time += deltaT;
	}
}

void TypingBox::clickOn(double hereX, double hereY) {
	if (hereX < x || hereX > x + width || hereY < y || hereY > y + height) {
		reading = false;
		if (onlyNumber) {
			text = intToString(getInt());
		}
		return;
	}
	if (!reading) {
		reading = true;
		time = sf::seconds(0.f);
		displayingLine = true;
	}
}

void TypingBox::readKey(int key) {
	if (0 <= key && key <= 35) {
		insert(key);
	}
	if (key == int(sf::Keyboard::BackSpace)) {
		deleteBack();
	}
	if (key == int(sf::Keyboard::Enter)) {
		reading = false;
		if (onlyNumber) {
			text = intToString(getInt());
		}
	}
}

void TypingBox::draw(sf::RenderWindow& window, ColorTheme theme) {
	sf::RectangleShape rect(sf::Vector2f(width, height));
	rect.setPosition(x, y);
	rect.setFillColor(colorBox[ColorBoxType::Typing_Box][theme].fillColor);
	rect.setOutlineThickness(0.f);
	//std::cout << x << " " << y << "\n";
	window.draw(rect);
	sf::Text Text;
	Text.setFont(*font);
	Text.setString(text);
	Text.setCharacterSize(height * 0.6);
	Text.setFillColor(colorBox[ColorBoxType::Typing_Box][theme].textColor);
	Text.setPosition(x + 10, y + height * 0.1);
	sf::FloatRect textRect = Text.getLocalBounds();
	//Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	window.draw(Text);
	if (reading && displayingLine) {
		sf::Vertex vtx[4]; 
		double textHeight = height * 0.6;
		double lineX = textRect.width < epsilonDouble ? x + 10 : x + textRect.width + 15;
		vtx[0] = sf::Vertex(sf::Vector2f(lineX, y + (height - textHeight) * 0.5f), colorBox[Typing_Box][theme].textColor);
		vtx[1] = sf::Vertex(sf::Vector2f(lineX, y + (height - textHeight) * 0.5f + textHeight), colorBox[Typing_Box][theme].textColor);
		window.draw(vtx, 2, sf::Lines);
	}
}

BigTypingBox::BigTypingBox(double _x, double _y, double _width, double _height, double _outlineSize, std::string _name, 
	bool _onlyNumber, sf::Font* _font, int _minValue, int _maxValue, bool _drawable, bool _typingBoxDrawable) :
	outerX(_x), outerY(_y), outerWidth(_width), outerHeight(_height), outlineSize(_outlineSize), name(_name),
	TypingBox(_x + _width * (1.0f / 3.0f - 1.0f / 20.0f), _y + _height * 0.2, _width * 2 / 3, _height * 0.6, _onlyNumber, _font, _minValue, _maxValue),
	drawable(_drawable), typingBoxDrawable(_typingBoxDrawable)
{}

void BigTypingBox::setDrawable(bool val) {
	drawable = val;
}

void BigTypingBox::setTypingBoxDrawable(bool val) {
	typingBoxDrawable = val;
}

void BigTypingBox::setName(std::string newName) {
	name = newName;
}

void BigTypingBox::drawAll(sf::RenderWindow& window, ColorTheme theme) {
	if (drawable) {
		Box tmpBox(outerX, outerY, outerWidth, outerHeight, { ColorBoxType::CommandBoxNormal }, "", font, 0, WITH_BORDER, outlineSize);
		tmpBox.draw(window, theme);
		sf::Text Text;
		Text.setFont(*font);
		Text.setString(name);
		Text.setCharacterSize(height * 0.6);
		Text.setFillColor(colorBox[ColorBoxType::CommandBoxNormal][theme].textColor);
		sf::FloatRect textRect = Text.getLocalBounds();
		Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		Text.setPosition(outerX + outerWidth / 6, outerY + outerHeight / 2);
		window.draw(Text);
		if (typingBoxDrawable) {
			draw(window, theme);
		}
	}
}