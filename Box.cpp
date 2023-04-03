#include "Box.h"

Box::Box(double _x1, double _y1, double _x2, double _y2,
	std::string _text, sf::Font* _font, double _textSize,
	std::vector <ColorBoxType> _colorModes,
	bool _isBorder, double _outlineSize) :
	x1(_x1), y1(_y1), x2(_x2), y2(_y2), 
	text(_text), font(_font), textSize(_textSize),
	colorModes(_colorModes),
	isBorder(_isBorder), outlineSize(_outlineSize)
{
	curMode = 0;
}

void Box::draw(sf::RenderWindow& window, ColorTheme theme) {
	double tmpOutlineSize = (isBorder ? outlineSize : 0.f);
	sf::RectangleShape outerRect(sf::Vector2f(x2 - x1 - tmpOutlineSize * 2, y2 - y1 - tmpOutlineSize * 2));
	outerRect.setPosition(x1 + tmpOutlineSize, y1 + tmpOutlineSize);
	ColorBox cur = colorBox[theme][colorModes[curMode]];
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
	Text.setPosition((x1 + x2) / 2, (y1 + y2) / 2);
	//Text.setStyle(sf::Text::Bold);
	window.draw(Text);
}

bool Box::isInside(double x, double y) {
	return (x1 <= x && x <= x2 && y1 <= y && y <= y2);
}

void Box::toggleColorMode() {
	curMode = (curMode + 1) % colorModes.size();
}

void Box::setColorMode(int mode) {
	curMode = mode;
}