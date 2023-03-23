#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <deque>
#include "Template.h"
#include "Node.h"

struct Graph {
private: 
	struct EdgeInfo {
		int v;
		sf::Color color;
		sf::Time totalTime, remainTime;
		EdgeInfo(int _v = 0, sf::Color _color = BlackColor, sf::Time totalTime = sf::seconds(0.f), sf::Time remainTime = sf::seconds(0.f));
	};
	struct cmp {
		bool operator() (const EdgeInfo& a, const EdgeInfo& b) const;
	};
	std::map <int, Node> listNode;
	std::map <int, std::set <EdgeInfo, cmp > > adj;
	Node defaultNode;
	double lineThickness;
	EdgeType edgeType;
public:
	Graph(double radius = 0, double outlineSize = 0, double _lineThickness = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor, 
		EdgeType _edgeType = Undirected, sf::Font* font = nullptr);
	void setFont(sf::Font* newFont);
	void draw(sf::RenderWindow& window);
	void addNode(int pos, int value, double x, double y);
	void deleteNode(int pos);
	void moveNode(int pos, double x, double y, sf::Time time);
	void updateNodeFillColor(int pos, sf::Color color, sf::Time time);
	void updateNodeOutlineColor(int pos, sf::Color color, sf::Time time);
	void updateNodeValueColor(int pos, sf::Color color, sf::Time time);
	void updateNodeAnimation(sf::Time deltaT);
	void addEdge(int u, int v, sf::Color lineColor = BlackColor);
};