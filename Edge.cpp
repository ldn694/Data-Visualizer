#pragma once

#include "Template.h"
#include "Edge.h"

//-------------------------------------------------------
//TrianglePointer

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
	double shortenStart, double shortenGoal) :
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