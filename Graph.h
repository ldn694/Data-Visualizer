#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
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
	Node(double _x, double _y, int _value,
		double _radius, double _outlineSize,
		sf::Color _fillColor, sf::Color _outlineColor, 
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
	Edge(double x1, double y1, double x2, double y2, double thickness, sf::Color _color, double shorten = 0, EdgeType _type = Undirected);
	void draw(sf::RenderWindow& window);
};

struct Graph {
private: 
	std::vector <Node> listNode;
	std::vector <std::vector<std::pair<int, sf::Color> > > adj;
	Node defaultNode;
	double lineThickness;
	EdgeType edgeType;
public:
	Graph(double radius, double outlineSize, double _lineThickness,
		sf::Color fillColor, sf::Color outlineColor,
		EdgeType _edgeType = Undirected, sf::Font* font = nullptr);
	void setFont(sf::Font* newFont);
	void draw(sf::RenderWindow& window);
	void addNode(int pos, int value, double x, double y);
	void addEdge(int u, int v, sf::Color lineColor = BlackColor);
};