#include <cassert>
#include "MyShape.h"

MyShape::MyShape(std::string filename, double _x, double _y, double _width, double _height, const sf::Color* _color) :
	x(_x), y(_y), width(_width), height(_height), color(_color)
{
	assert(texture.loadFromFile(filename));
	texture.setSmooth(true);
	sprite.setTexture(texture, true);
	sprite.setScale(width / sprite.getLocalBounds().width, height / sprite.getLocalBounds().height);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
	sprite.setPosition(x, y);
}

bool MyShape::isMousePressed(double mouseX, double mouseY) {
	return (x - width / 2 <= mouseX && mouseX <= x + width / 2 && y - height / 2 <= mouseY && mouseY <= y + height / 2);
}

void MyShape::setOrigin(double _x, double _y) {
	sprite.setOrigin(_x, _y);
	sprite.setPosition(x, y);
}

void MyShape::draw(sf::RenderWindow& window, ColorTheme theme) {
	sprite.setColor(color[theme]);
	window.draw(sprite);
}