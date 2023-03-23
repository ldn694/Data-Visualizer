#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "Game.h"
#include "Graph.h"
#include "Template.h"
#include "Node.h"
#include "Edge.h"

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