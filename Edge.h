#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <deque>
#include "Template.h"

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