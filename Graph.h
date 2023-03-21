#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <deque>
#include "Template.h"

struct Node {
private:
	double x, y;
	int value;
	double radius, outlineSize;
	sf::Color fillColor, outlineColor;
	sf::CircleShape shape;
	sf::Font* font;
	struct NodeMovement{
		double goalX, goalY;
		sf::Time remainTime;
		NodeMovement(double _goalX = 0.f, double _goalY = 0.f, sf::Time _remainTime = sf::seconds(0.f));
	};
	struct NodeZooming {
		double goalRadius, goalOutline;
		sf::Time remainTime;
		NodeZooming(double _goalRadius = 0.f, double _goalOutline = 0.f, sf::Time _remainTime = sf::seconds(0.f));
	};
	std::deque <NodeMovement> movementQueue;
	std::deque <NodeZooming> zoomingQueue;
public:
	Node(double _x = 0, double _y = 0, int _value = 0,
		double _radius = 0, double _outlineSize = 0,
		sf::Color _fillColor = WhiteColor, sf::Color _outlineColor = BlackColor, 
		sf::Font* _font = nullptr);
	void setValue(int newValue);
	void setX(double newX);
	void setY(double newY);
	void setXY(double newX, double newY);
	void moveX(double dx);
	void moveY(double dy);
	void setFont(sf::Font* newFont);
	void setRadius(double newRadius);
	void setOutline(double newOutline);
	double getX();
	double getY();
	double getRadius();
	double getOutlineSize();
	sf::CircleShape& getShape();
	void addMovement(double goalX, double goalY, sf::Time time);
	void updateMovement(sf::Time deltaT);
	void addZooming(double goalRadius, double goalOutline, sf::Time time);
	void updateZooming(sf::Time deltaT);
	void draw(sf::RenderWindow& window);
};

struct TrianglePointer {
private:
	sf::Vertex points[3];
	sf::Color color;
	double thickness;
public:
	TrianglePointer(double x1 = 0.f, double y1 = 0.f, double x2 = 0.f, double y2 = 0.f, double thickness = 0.f, 
		sf::Color _color = BlackColor, double shortenStart = 0.f, double shortenGoal = 0.f);
	void draw(sf::RenderWindow& window);
};

struct Edge {
private:
	sf::Vertex points[4];
	sf::Color color;
	TrianglePointer forwardPointer, backwardPointer;
	double thickness;
	EdgeType type;
	sf::Time remainTime;
public:
	Edge(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0, double thickness = 0, 
		sf::Color _color = BlackColor, EdgeType _type = Undirected,
		double shortenStart = 0.f, double shortenGoal = 0.f);
	void draw(sf::RenderWindow& window);
};

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
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = RedColor,
		EdgeType _edgeType = Undirected, sf::Font* font = nullptr);
	void setFont(sf::Font* newFont);
	void draw(sf::RenderWindow& window);
	void addNode(int pos, int value, double x, double y);
	void deleteNode(int pos);
	void moveNode(int pos, double x, double y, sf::Time time);
	void updateNodeAnimation(sf::Time deltaT);
	void addEdge(int u, int v, sf::Color lineColor = BlackColor);
};