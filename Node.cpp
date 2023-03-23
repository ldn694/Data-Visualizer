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
		double dOutline = elapsedTime / cur.remainTime * (cur.goalRadius - outlineSize);
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
	res.r = goalColor.r;
	res.g = goalColor.g;
	res.b = goalColor.b;
	res.a = goalColor.a;
	return res;
}

Node::Node(double _x, double _y, int _value,
	double _radius, double _outlineSize,
	sf::Color _fillColor, sf::Color _outlineColor,
	sf::Font* _font) :
	x(_x), y(_y), value(_value), radius(_radius), outlineSize(_outlineSize), fillColor(_fillColor), outlineColor(_outlineColor), font(_font)
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

void Node::setFont(sf::Font* newFont) {
	font = newFont;
}

void Node::setRadius(double newRadius) {
	radius = newRadius;
}

void Node::setOutline(double newOutline) {
	outlineSize = newOutline;
}

void Node::setFillColor(sf::Color newColor) {
	fillColor = newColor;
}

void Node::setOutlineColor(sf::Color newColor) {
	outlineColor = newColor;
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

sf::CircleShape& Node::getShape() {
	return shape;
}

void Node::draw(sf::RenderWindow& window) {
	window.draw(shape);
	sf::Text textValue;
	textValue.setFont(*font);
	textValue.setString(intToString(value));
	textValue.setCharacterSize(radius);
	textValue.setFillColor(outlineColor);
	sf::FloatRect textRect = textValue.getLocalBounds();
	textValue.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	textValue.setPosition(getX(), getY());
	textValue.setStyle(sf::Text::Bold);
	window.draw(textValue);
}