#include "Color.h"

ColorNode::ColorNode(sf::Color _fillColor, sf::Color _outlineColor, sf::Color _valueColor, sf::Color _variableColor) :
	fillColor(_fillColor), outlineColor(_outlineColor), valueColor(_valueColor), variableColor(_variableColor) {}

ColorBox::ColorBox(sf::Color _fillColor, sf::Color _outlineColor, sf::Color _textColor) :
	fillColor(_fillColor), outlineColor(_outlineColor), textColor(_textColor) {}