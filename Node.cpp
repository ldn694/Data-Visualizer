#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Game.h"
#include "Graph.h"
#include "Template.h"

//-------------------------------------------------------
//Node

Node::NodeMovement::NodeMovement(double _goalX, double _goalY, sf::Time _remainTime) :
	goalX(_goalX), goalY(_goalY), remainTime(_remainTime) {}

void Node::addMovement(double goalX, double goalY, sf::Time time) {
	movementQueue.push_back(NodeMovement(goalX, goalY, time));
}

void Node::updateMovement(sf::Time deltaT) {
	while (!movementQueue.empty()) {
		NodeMovement cur = movementQueue.front();
		movementQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		double dx = elapsedTime / cur.remainTime * (cur.goalX - x);
		double dy = elapsedTime / cur.remainTime * (cur.goalY - y);
		moveX(dx);
		moveY(dy);
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			movementQueue.push_front(cur);
		}
		if (deltaT < epsilonTime) break;
	}
}

Node::NodeZooming::NodeZooming(double _goalRadius, double _goalOutline, sf::Time _remainTime) :
	goalRadius(_goalRadius), goalOutline(_goalOutline), remainTime(_remainTime) {}

void Node::addZooming(double goalRadius, double goalOutline, sf::Time time) {
	zoomingQueue.push_back(NodeZooming(goalRadius, goalOutline, time));
}

void Node::updateZooming(sf::Time deltaT) {
	while (!zoomingQueue.empty()) {
		NodeZooming cur = zoomingQueue.front();
		zoomingQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		double dRadius = elapsedTime / cur.remainTime * (cur.goalRadius - radius);
		double dOutline = elapsedTime / cur.remainTime * (cur.goalOutline - outlineSize);
		setRadius(radius + dRadius);
		setOutline(outlineSize + dOutline);
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			zoomingQueue.push_front(cur);
		}
		if (deltaT < epsilonTime) break;
	}
}

Node::NodeChangingColor::NodeChangingColor(sf::Color _goalColor, sf::Time _remainTime, std::vector <double> _fakeColor) :
	goalColor(_goalColor), remainTime(_remainTime), fakeColor(_fakeColor)
{
	if (std::abs(fakeColor[0] - 300) < epsilonDouble) {
		fakeColor[0] = goalColor.r;
		fakeColor[1] = goalColor.g;
		fakeColor[2] = goalColor.b;
		fakeColor[3] = goalColor.a;
	}
}

sf::Color Node::NodeChangingColor::getRealColor() {
	sf::Color res;
	res.r = fakeColor[0];
	res.g = fakeColor[1];
	res.b = fakeColor[2];
	res.a = fakeColor[3];
	return res;
}

void Node::addFillColor(sf::Color goalColor, sf::Time time) {
	std::vector <double> tmp;
	tmp.resize(4);
	sf::Color prevColor;
	if (fillColorQueue.empty()) {
		prevColor = fillColor;
	}
	else {
		prevColor = fillColorQueue.back().goalColor;
	}
	tmp[0] = prevColor.r;
	tmp[1] = prevColor.g;
	tmp[2] = prevColor.b;
	tmp[3] = prevColor.a;
	fillColorQueue.push_back(NodeChangingColor(goalColor, time, tmp));
}

void Node::updateFillColor(sf::Time deltaT) {
	while (!fillColorQueue.empty()) {
		NodeChangingColor cur = fillColorQueue.front();
		fillColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		double dr = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.r - cur.fakeColor[0]);
		double dg = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.g - cur.fakeColor[1]);
		double db = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.b - cur.fakeColor[2]);
		double da = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.a - cur.fakeColor[3]);
		cur.fakeColor[0] += dr;
		cur.fakeColor[1] += dg;
		cur.fakeColor[2] += db;
		cur.fakeColor[3] += da;
		cur.remainTime -= elapsedTime;
		setFillColor(cur.getRealColor());
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			fillColorQueue.push_front(cur);
		}
		if (deltaT < epsilonTime) break;
	}
}

void Node::addOutlineColor(sf::Color goalColor, sf::Time time) {
	std::vector <double> tmp;
	tmp.resize(4);
	sf::Color prevColor;
	if (outlineColorQueue.empty()) {
		prevColor = outlineColor;
	}
	else {
		prevColor = outlineColorQueue.back().goalColor;
	}
	tmp[0] = prevColor.r;
	tmp[1] = prevColor.g;
	tmp[2] = prevColor.b;
	tmp[3] = prevColor.a;
	outlineColorQueue.push_back(NodeChangingColor(goalColor, time, tmp));
}

void Node::updateOutlineColor(sf::Time deltaT) {
	while (!outlineColorQueue.empty()) {
		NodeChangingColor cur = outlineColorQueue.front();
		outlineColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		double dr = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.r - cur.fakeColor[0]);
		double dg = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.g - cur.fakeColor[1]);
		double db = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.b - cur.fakeColor[2]);
		double da = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.a - cur.fakeColor[3]);
		cur.fakeColor[0] += dr;
		cur.fakeColor[1] += dg;
		cur.fakeColor[2] += db;
		cur.fakeColor[3] += da;
		cur.remainTime -= elapsedTime;
		setOutlineColor(cur.getRealColor());
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			outlineColorQueue.push_front(cur);
		}
		if (deltaT < epsilonTime) break;
	}
}

void Node::addValueColor(sf::Color goalColor, sf::Time time) {
	std::vector <double> tmp;
	tmp.resize(4);
	sf::Color prevColor;
	if (valueColorQueue.empty()) {
		prevColor = valueColor;
	}
	else {
		prevColor = valueColorQueue.back().goalColor;
	}
	tmp[0] = prevColor.r;
	tmp[1] = prevColor.g;
	tmp[2] = prevColor.b;
	tmp[3] = prevColor.a;
	valueColorQueue.push_back(NodeChangingColor(goalColor, time, tmp));
}

void Node::addVariable(std::string variable) {
	if (variableList.find(variable) != variableList.end()) {
		return;
	}
	variableList.insert(variable);
}

void Node::eraseVariable(std::string variable) {
	if (variableList.find(variable) == variableList.end()) {
		return;
	}
	variableList.erase(variableList.find(variable));
}

void Node::updateValueColor(sf::Time deltaT) {
	while (!valueColorQueue.empty()) {
		NodeChangingColor cur = valueColorQueue.front();
		valueColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		double dr = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.r - cur.fakeColor[0]);
		double dg = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.g - cur.fakeColor[1]);
		double db = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.b - cur.fakeColor[2]);
		double da = elapsedTime / cur.remainTime * (1.0 * cur.goalColor.a - cur.fakeColor[3]);
		cur.fakeColor[0] += dr;
		cur.fakeColor[1] += dg;
		cur.fakeColor[2] += db;
		cur.fakeColor[3] += da;
		cur.remainTime -= elapsedTime;
		setValueColor(cur.getRealColor());
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			valueColorQueue.push_front(cur);
		}
		if (deltaT < epsilonTime) break;
	}
}

Node::Node(double _x, double _y, int _value,
	double _radius, double _outlineSize,
	sf::Color _fillColor, sf::Color _outlineColor, sf::Color _valueColor, sf::Color _variableColor,
	sf::Font* _font, bool _display) :
	x(_x), y(_y), value(_value), radius(_radius), outlineSize(_outlineSize),
	fillColor(_fillColor), outlineColor(_outlineColor), valueColor(_valueColor), variableColor(_variableColor), font(_font), display(_display)
{
	shape = sf::CircleShape(radius);
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(outlineSize);
	shape.setPointCount(pointCountCircle);
	shape.setOrigin(radius, radius);
	shape.setPosition(x, y);
}

void Node::setValue(int newValue) {
	value = newValue;
}

void Node::setX(double newX) {
	x = newX;
	shape.setPosition(x, y);
}

void Node::setY(double newY) {
	y = newY;
	shape.setPosition(x, y);
}

void Node::setXY(double newX, double newY) {
	x = newX;
	y = newY;
	shape.setPosition(x, y);
}

void Node::moveX(double dx) {
	x += dx;
	shape.setPosition(x, y);
}
void Node::moveY(double dy) {
	y += dy;
	shape.setPosition(x, y);
}

void Node::setDisplay(bool _display) {
	display = _display;
}

void Node::setFont(sf::Font* newFont) {
	font = newFont;
}

void Node::setRadius(double newRadius) {
	radius = newRadius;
	shape.setRadius(radius);
	shape.setOrigin(radius, radius);
}

void Node::setOutline(double newOutline) {
	outlineSize = newOutline;
	shape.setOutlineThickness(newOutline);
}

void Node::setFillColor(sf::Color newColor) {
	fillColor = newColor;
	shape.setFillColor(fillColor);
}

void Node::setOutlineColor(sf::Color newColor) {
	outlineColor = newColor;
	shape.setOutlineColor(outlineColor);
}

void Node::setValueColor(sf::Color newColor) {
	valueColor = newColor;
}

void Node::setVariableColor(sf::Color newColor) {
	variableColor = newColor;
}

double Node::getX() {
	return x;
}

double Node::getY() {
	return y;
}


double Node::getRadius() {
	return radius;
}

double Node::getOutlineSize() {
	return outlineSize;
}

bool Node::getDisplay() {
	return display;
}

int Node::getValue() {
	return value;
}

sf::Color Node::getFillColor() {
	return fillColor;
}
sf::Color Node::getOutlineColor() {
	return outlineColor;
}
sf::Color Node::getValueColor() {
	return valueColor;
}
sf::Color Node::getVariableColor() {
	return variableColor;
}

sf::CircleShape& Node::getShape() {
	return shape;
}

void Node::updateAnimation(sf::Time deltaT) {
	updateMovement(deltaT);
	updateZooming(deltaT);
	updateFillColor(deltaT);
	updateOutlineColor(deltaT);
	updateValueColor(deltaT);
}

void Node::stopAnimation() {
	if (!movementQueue.empty()) {
		double x = movementQueue.back().goalX;
		double y = movementQueue.back().goalY;
		setXY(x, y);
		movementQueue.clear();
	}
	if (!zoomingQueue.empty()) {
		double radius = zoomingQueue.back().goalRadius;
		double outlineSize = zoomingQueue.back().goalOutline;
		setRadius(radius);
		setOutline(outlineSize);
		zoomingQueue.clear();
	}
	if (!fillColorQueue.empty()) {
		setFillColor(fillColorQueue.back().goalColor);;
		fillColorQueue.clear();
	}
	if (!outlineColorQueue.empty()) {
		setOutlineColor(outlineColorQueue.back().goalColor);
		outlineColorQueue.clear();
	}
	if (!valueColorQueue.empty()) {
		setValueColor(valueColorQueue.back().goalColor);
		valueColorQueue.clear();
	}
}

void Node::draw(sf::RenderWindow& window) {
	if (display) {
		window.draw(shape);
		sf::Text textValue;
		textValue.setFont(*font);
		textValue.setString(intToString(value));
		textValue.setCharacterSize(radius);
		textValue.setFillColor(valueColor);
		sf::FloatRect textRect = textValue.getLocalBounds();
		textValue.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		textValue.setPosition(getX(), getY());
		textValue.setStyle(sf::Text::Bold);
		sf::Text textVariable;
		std::string variableString;
		for (std::set<std::string>::iterator cur = variableList.begin(); cur != variableList.end(); cur++) {
			variableString = variableString + (*cur);
			std::set<std::string>::iterator nxt = cur;
			nxt++;
			if (nxt != variableList.end()) {
				variableString.push_back('/');
			}
		}
		textVariable.setFont(*font);
		textVariable.setString(variableString);
		textVariable.setCharacterSize(radius);
		textVariable.setFillColor(variableColor);
		textVariable.setStyle(sf::Text::Bold);
		textRect = textVariable.getLocalBounds();
		textVariable.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		textVariable.setPosition(getX(), getY() + 2 * radius);
		window.draw(textValue);
		window.draw(textVariable);
	}
}