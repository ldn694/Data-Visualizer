#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include "Template.h"

const sf::Color GreyColor(211, 211, 211);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);

const double pointCountCircle = 50;

struct Node {
private:
	double x, y;
	int value;
	double radius, outlineSize;
	sf::Color fillColor, outlineColor;
	sf::CircleShape shape;
	sf::Font* font;

public:
	Node(double _x = 0, double _y = 0, int _value = 0,
		double _radius = 0, double _outlineSize = 0,
		sf::Color _fillColor = WhiteColor, sf::Color _outlineColor = BlackColor, 
		sf::Font* _font = nullptr);
	void setValue(int newValue);
	void setX(double newX);
	void setY(double newY);
	void setXY(double newX, double newY);
	void setFont(sf::Font* newFont);
	double getX();
	double getY();
	double getRadius();
	double getOutlineSize();
	sf::CircleShape& getShape();
	void draw(sf::RenderWindow& window);
};

struct TrianglePointer {
private:
	sf::Vertex points[3];
	sf::Color color;
	double thickness;
public:
	TrianglePointer(double x1, double y1, double x2, double y2, double thickness, sf::Color _color, double shorten = 0);
	void draw(sf::RenderWindow& window);
};

struct Edge {
private:
	sf::Vertex points[4];
	sf::Color color;
	TrianglePointer forwardPointer, backwardPointer;
	double thickness;
	EdgeType type;
public:
	Edge(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0, double thickness = 0, sf::Color _color = BlackColor, double shorten = 0, EdgeType _type = Undirected);
	void draw(sf::RenderWindow& window);
};

struct Graph {
private: 
	struct cmp {
		bool operator() (const std::pair<int, sf::Color>& a, const std::pair <int, sf::Color>& b) const;
	};
	std::map <int, Node> listNode;
	std::map <int, std::set <std::pair<int, sf::Color>, cmp > > adj;
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
	void addEdge(int u, int v, sf::Color lineColor = BlackColor);
};