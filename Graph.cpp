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

TrianglePointer::TrianglePointer(double x1, double y1, double x2, double y2, double thickness, 
	sf::Color _color, double shortenStart, double shortenGoal) : color(_color) {
	//first move (x1,y1) and (x2,y2) closer
	MovePoint(x1, y1, x2, y2, shortenStart);
	MovePoint(x2, y2, x1, y1, shortenGoal);
	double x3 = x2, y3 = y2;
	//now move (x3, y3) a distance of 2 * thickness, (x3, y3) is the midpoint of the hypotenuse of the triangle
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

Edge::Edge(double x1, double y1, double x2, double y2, double thickness, 
	sf::Color _color, EdgeType _type, 
	double shortenStart, double shortenGoal): 
	color(_color), type(_type),
	forwardPointer(x1, y1, x2, y2, thickness, color, shortenStart, shortenGoal),
	backwardPointer(x2, y2, x1, y1, thickness, color, shortenStart, shortenGoal) {
	MovePoint(x1, y1, x2, y2, shortenStart);
	MovePoint(x2, y2, x1, y1, shortenGoal);
	if (type == EdgeType::SinglyDirected) {
		MovePoint(x2, y2, x1, y1, thickness * 0.5);
	}
	if (type == EdgeType::DoublyDirected) {
		MovePoint(x2, y2, x1, y1, thickness * 0.5);
		MovePoint(x1, y1, x2, y2, thickness * 0.5);
	}
	double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dx = ((y2 - y1) * (thickness / 2.0) / hypo);
	double dy = ((x2 - x1) * (thickness / 2.0) / hypo);
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

bool Graph::cmp:: operator() (const EdgeInfo& a, const EdgeInfo& b) const {
	if (a.remainTime != b.remainTime) {
		return a.remainTime > b.remainTime;
	}
	if (a.v != b.v) {
		return a.v < b.v;
	}
	if (a.color.r != b.color.r) {
		return a.color.r < b.color.r;
	}
	if (a.color.g != b.color.g) {
		return a.color.g < b.color.g;
	}
	if (a.color.b != b.color.b) {
		return a.color.b < b.color.b;
	}
	if (a.color.a != b.color.a) {
		return a.color.a < b.color.a;
	}
	return a.totalTime < b.totalTime;
}
Graph::EdgeInfo::EdgeInfo(int _v, sf::Color _color, 
	sf::Time _totalTime, sf::Time _remainTime):
	v(_v), color(_color), totalTime(_totalTime), remainTime(_remainTime) {}


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
	for (auto &uComp: listNode) {
		uComp.second.draw(window);
		int u = uComp.first;
		for (auto &vComp : adj[u]) {
			int v = vComp.v;
			sf::Color lineColor = vComp.color;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			double hypo = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) - 2 * shorten;
			if (vComp.remainTime > epsilonTime) {
				MovePoint(x2, y2, x1, y1, hypo * (max(vComp.remainTime, epsilonTime) / vComp.totalTime));
			}
			Edge edge(x1, y1, x2, y2, lineThickness, lineColor, edgeType, shorten, shorten);
			edge.draw(window);
		}
	}
}

void Graph::addNode(int pos, int value, double x, double y) {
	Node newNode = defaultNode;
	newNode.setRadius(0.f);
	newNode.setOutline(0.f);
	newNode.setValue(value);
	newNode.setXY(x, y);
	std::cout << newNode.getX() << " " << newNode.getY() << "\n";
	listNode[pos] = newNode;
	listNode[pos].addZooming(defaultNode.getRadius(), defaultNode.getOutlineSize(), sf::seconds(0.2f));
	std::cout << "added pos = " << pos << " size = " << (int)listNode.size() << "\n";
}

void Graph::deleteNode(int pos) {
	listNode.erase(pos);
	adj.erase(pos);
	for (auto& uComp : listNode) {
		int u = uComp.first;
		while (true) {
			auto here = adj[u].end();
			for (auto cur = adj[u].begin(); cur != adj[u].end(); cur++) {
				if (cur->v == pos) {
					here = cur;
					break;
				}
			}
			if (here != adj[u].end() && here->v == pos) {
				adj[u].erase(here);
			}
			else {
				break;
			}
		}
	}
	std::cout << "deleted pos = " << pos << " size = " << (int)listNode.size() << "\n";
}

void Graph::moveNode(int pos, double x, double y, sf::Time time) {
	listNode[pos].addMovement(x, y, time);
}

void Graph::updateNodeAnimation(sf::Time deltaT) {
	for (auto& uComp : listNode) {
		int u = uComp.first;
		listNode[u].updateMovement(deltaT);
		listNode[u].updateZooming(deltaT);
		std::set <EdgeInfo, cmp> tmpSet;
		while (true) {
			auto here = adj[u].lower_bound(EdgeInfo(0, BlackColor, infTime, infTime));
			if (here == adj[u].end()) {
				break;
			}
			EdgeInfo tmp = *here;
			if (tmp.remainTime < epsilonTime) {
				//tmp.remainTime = sf::seconds(0.f);
				break;
			}
			adj[u].erase(here);
			sf::Time elapsedTime = min(tmp.remainTime, deltaT);
			tmp.remainTime -= elapsedTime;
			tmpSet.insert(tmp);
		}
		for (auto& here : tmpSet) {
			adj[u].insert(here);
		}
	}
}

void Graph::addEdge(int u, int v, sf::Color lineColor) {
	adj[u].insert(EdgeInfo(v, lineColor, sf::seconds(1.0f), sf::seconds(1.0f)));
}

//-------------------------------------------------------