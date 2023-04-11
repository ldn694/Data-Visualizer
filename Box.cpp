#include "Box.h"

Box::Box(double _x1, double _y1, double _width, double _height,
	std::vector <ColorBoxType> _colorModes,
	std::string _text, sf::Font* _font, double _textSize,
	bool _isBorder, double _outlineSize) :
	x1(_x1), y1(_y1), width(_width), height(_height),
	text(_text), font(_font), textSize(_textSize),
	colorModes(_colorModes),
	isBorder(_isBorder), outlineSize(_outlineSize)
{
	curMode = 0;
	isDrawable = true;
}

double Box::getOutlineSize() {
	return outlineSize;
}

void Box::setTextSize(double newSize) {
	textSize = newSize;
}

void Box::setText(std::string newText) {
	text = newText;
}

sf::Font* Box::getFont() {
	return font;
}

int Box::getWidth() {
	return width;
}
int Box::getHeight() {
	return height;
}

void Box::setPosition(double _x1, double _y1) {
	x1 = _x1;
	y1 = _y1;
}

void Box::setDrawable(bool drawable) {
	isDrawable = drawable;
}

void Box::draw(sf::RenderWindow& window, ColorTheme theme) {
	if (!isDrawable) {
		return;
	}
	double tmpOutlineSize = (isBorder ? outlineSize : 0.f);
	sf::RectangleShape outerRect(sf::Vector2f(width - tmpOutlineSize, height - tmpOutlineSize));
	outerRect.setPosition(x1 + tmpOutlineSize / 2.0f, y1 + tmpOutlineSize / 2.0f);
	ColorBox cur = colorBox[colorModes[curMode]][theme];
	outerRect.setFillColor(cur.fillColor);
	outerRect.setOutlineColor(cur.outlineColor);
	outerRect.setOutlineThickness(outlineSize);
	window.draw(outerRect);
	sf::Text Text;
	Text.setFont(*font);
	Text.setString(text);
	Text.setCharacterSize(textSize);
	Text.setFillColor(cur.textColor);
	sf::FloatRect textRect = Text.getLocalBounds();
	Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	Text.setPosition(x1 + width / 2.0f, y1 + height / 2.0f);
	Text.setStyle(sf::Text::Bold);
	window.draw(Text);
}

bool Box::isInside(double x, double y) {
	return (x1 <= x && x <= x1 + width && y1 <= y && y <= y1 + height);
}

void Box::toggleColorMode() {
	curMode = (curMode + 1) % colorModes.size();
}

void Box::setColorMode(int mode) {
	curMode = mode;
}