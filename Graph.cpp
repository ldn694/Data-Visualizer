#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Graph.h"
#include "Template.h"

//-------------------------------------------------------
//Node

Node::Node(double _x, double _y, int _value,
	double _radius, double _outlineSize,
	sf::Color _fillColor, sf::Color _outlineColor,
	sf::Font* _font):
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

void Node::setFont(sf::Font* newFont) {
	font = newFont;
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

//-------------------------------------------------------
//Pointer

void MovePoint(double &x1, double &y1, double x2, double y2, double dist) {
	double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dx = (x2 - x1) * dist / hypo;
	double dy = (y2 - y1) * dist / hypo;
	x1 += dx;
	y1 += dy;
}

TrianglePointer::TrianglePointer(double x1, double y1, double x2, double y2, double thickness, sf::Color _color, double shorten) : color(_color) {
	//first move (x1,y1) and (x2,y2) closer, each move a distance of 'shorten'
	MovePoint(x1, y1, x2, y2, shorten);
	MovePoint(x2, y2, x1, y1, shorten);
	double x3 = x2, y3 = y2;
	//now move (x3, y3) a distance of thickness, (x3, y3) is the midpoint of the hypotenius of the triangle
	MovePoint(x3, y3, x1, y1, 2 * thickness);
	double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dx = ((y2 - y1) * thickness / hypo);
	double dy = ((x2 - x1) * thickness / hypo);
	points[0] = sf::Vertex(sf::Vector2f(x2, y2), color);
	points[1] = sf::Vertex(sf::Vector2f(x3 - 2 * dx, y3 + 2 * dy), color);
	points[2] = sf::Vertex(sf::Vector2f(x3 + 2 * dx, y3 - 2 * dy), color);
}

void TrianglePointer::draw(sf::RenderWindow& window) {
	window.draw(points, 3, sf::TriangleStrip);
}

//-------------------------------------------------------
//Edge

Edge::Edge(double x1, double y1, double x2, double y2, double thickness, sf::Color _color, double shorten, EdgeType _type): 
	color(_color), type(_type),
	forwardPointer(x1, y1, x2, y2, thickness, color, shorten),
	backwardPointer(x2, y2, x1, y1, thickness, color, shorten) {
	MovePoint(x1, y1, x2, y2, shorten);
	double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dx = ((x2 - x1) * (thickness / 2.0) / hypo);
	double dy = ((y2 - y1) * (thickness / 2.0) / hypo);
	if (dx == 0) dx = thickness / 2.0;
	if (dy == 0) dy = thickness / 2.0;
	points[0] = sf::Vertex(sf::Vector2f(x1 - dx, y1 + dy), color);
	points[1] = sf::Vertex(sf::Vector2f(x2 - dx, y2 + dy), color);
	points[2] = sf::Vertex(sf::Vector2f(x2 + dx, y2 - dy), color);
	points[3] = sf::Vertex(sf::Vector2f(x1 + dx, y1 - dy), color);
}

void Edge::draw(sf::RenderWindow& window) {
	window.draw(points, 4, sf::Quads);
	if (type == EdgeType::SinglyDirected || type == EdgeType::DoublyDirected) {
		forwardPointer.draw(window);
	}
	if (type == EdgeType::DoublyDirected) {
		backwardPointer.draw(window);
	}
}

//-------------------------------------------------------
//Graph

bool Graph::cmp::operator() (const std::pair<int, sf::Color>& a, const std::pair <int, sf::Color>& b) const {
	if (a.first != b.first) {
		return a.first < b.first;
	}
	if (a.second.r != b.second.r) {
		return a.second.r < b.second.r;
	}
	if (a.second.g != b.second.g) {
		return a.second.g < b.second.g;
	}
	if (a.second.b != b.second.b) {
		return a.second.b < b.second.b;
	}
	return a.second.a < b.second.a;
}

Graph::Graph(double radius, double outlineSize, double _lineThickness,
		sf::Color fillColor, sf::Color outlineColor,
		EdgeType _idEdgeType, sf::Font* font) :
	defaultNode(0, 0, 0, radius, outlineSize, fillColor, outlineColor, font), edgeType(_idEdgeType)
{
	lineThickness = _lineThickness;
}

void Graph::setFont(sf::Font* newFont) {
	defaultNode.setFont(newFont);
}

void Graph::draw(sf::RenderWindow& window) {
	for (int u = 0; u < (int)listNode.size(); u++) {
		for (auto vComp : adj[u]) {
			int v = vComp.first;
			sf::Color lineColor = vComp.second;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			Edge edge(x1, y1, x2, y2, lineThickness, lineColor, defaultNode.getRadius() + defaultNode.getOutlineSize(), edgeType);
			edge.draw(window);
		}
	}
	for (int u = 0; u < (int)listNode.size(); u++) {
		listNode[u].draw(window);
	}
}

void Graph::addNode(int pos, int value, double x, double y) {
	Node newNode = defaultNode;
	newNode.setValue(value);
	newNode.setXY(x, y);
	std::cout << newNode.getX() << " " << newNode.getY() << "\n";
	listNode[pos] = newNode;
	std::cout << "Done add node " << pos << "\n";
}

void Graph::addEdge(int u, int v, sf::Color lineColor) {
	adj[u].insert(std::make_pair(v, lineColor));
}

//-------------------------------------------------------