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
	struct NodeMovement {
		double goalX, goalY;
		sf::Time remainTime;
		NodeMovement(double _goalX = 0.f, double _goalY = 0.f, sf::Time _remainTime = sf::seconds(0.f));
	};
	struct NodeZooming {
		double goalRadius, goalOutline;
		sf::Time remainTime;
		NodeZooming(double _goalRadius = 0.f, double _goalOutline = 0.f, sf::Time _remainTime = sf::seconds(0.f));
	};
	struct NodeChangingColor {
		sf::Color goalColor;
		std::vector <double> fakeColor;
		sf::Time remainTime;
		NodeChangingColor(sf::Color goalColor, sf::Time _remainTime = sf::seconds(0.f), std::vector <double>_fakeColor = std::vector <double>(300));
		sf::Color getRealColor();
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
	void setFillColor(sf::Color);
	void setOutlineColor(sf::Color);
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