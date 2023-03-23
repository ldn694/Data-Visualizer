#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Game.h"
#include "Graph.h"
#include "Template.h"
#include "Node.h"

//-------------------------------------------------------
//Pointer

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