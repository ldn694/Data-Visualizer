#pragma once

#include "Template.h"
#include <iostream>
#include "Edge.h"

//-------------------------------------------------------
//TrianglePointer

TrianglePointer::TrianglePointer(double x1, double y1, double x2, double y2, double thickness,
	sf::Color _color) : color(_color) {
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
	color(_color), type(_type) {
	MovePoint(x1, y1, x2, y2, shortenStart);
	MovePoint(x2, y2, x1, y1, shortenGoal);
	if (type == EdgeType::SinglyDirected) {
		MovePoint(x2, y2, x1, y1, thickness * 0.5);
	}
	if (type == EdgeType::DoublyDirected) {
		MovePoint(x2, y2, x1, y1, thickness * 0.5);
		//MovePoint(x1, y1, x2, y2, thickness * 0.5);
	}
	double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	double dx = ((y2 - y1) * (thickness / 2.0) / hypo);
	double dy = ((x2 - x1) * (thickness / 2.0) / hypo);
	double X0 = x1 - dx, Y0 = y1 + dy;
	double X1 = x2 - dx, Y1 = y2 + dy;
	double X2 = x2 + dx, Y2 = y2 - dy;
	double X3 = x1 + dx, Y3 = y1 - dy;
	//std::cout << "(" << X0 << "," << Y0 << ") (" << X1 << "," << Y1 << ") (" << X2 << "," << Y2 << ") (" << X3 << "," << Y3 << ")\n";
	//std::cout << "(" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")\n";
	if (type == EdgeType::DoublyDirected) {       
		double diff = shortenGoal - sqrt(shortenGoal * shortenGoal - 4 * thickness * thickness);
		MovePoint(X3, Y3, X0, Y0, -2 * thickness);
		MovePoint(X2, Y2, X1, Y1, -2 * thickness);
		MovePoint(X1, Y1, X2, Y2, 2 * thickness);
		MovePoint(X0, Y0, X3, Y3, 2 * thickness);
		//std::cout << "changed to (" << X0 << "," << Y0 << ") (" << X1 << "," << Y1 << ") (" << X2 << "," << Y2 << ") (" << X3 << "," << Y3 << ")\n";
		MovePoint(x1, y1, X3, Y3, 2 * thickness);
		MovePoint(x2, y2, X2, Y2, 2 * thickness);
		MovePoint(X2, Y2, X3, Y3, -diff);
		MovePoint(X1, Y1, X0, Y0, -diff);
		MovePoint(X3, Y3, X2, Y2, -diff);
		MovePoint(X0, Y0, X1, Y1, -diff);
		MovePoint(x1, y1, x2, y2, -diff);
		MovePoint(x2, y2, x1, y1, -diff);
		//std::cout << "changed to (" << x1 << "," << y1 << ") (" << x2 << "," << y2 << ")\n";
	}
	forwardPointer = TrianglePointer(x1, y1, x2, y2, thickness, color);
	points[0] = sf::Vertex(sf::Vector2f(X0, Y0), color);
	points[1] = sf::Vertex(sf::Vector2f(X1, Y1), color);
	points[2] = sf::Vertex(sf::Vector2f(X2, Y2), color);
	points[3] = sf::Vertex(sf::Vector2f(X3, Y3), color);
}

void Edge::draw(sf::RenderWindow& window) {
	window.draw(points, 4, sf::Quads);
	if (type == EdgeType::SinglyDirected || type == EdgeType::DoublyDirected) {
		forwardPointer.draw(window);
	}
	if (type == EdgeType::DoublyDirected) {
		//backwardPointer.draw(window);
	}
}