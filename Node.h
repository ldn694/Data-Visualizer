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
	int value, numPointCircle;
	std::set <std::string> variableList;
	double radius, outlineSize;
	sf::Color fillColor, outlineColor, valueColor, variableColor;
	sf::CircleShape shape;
	sf::Font* font;
	bool display;
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
	std::deque <NodeChangingColor> fillColorQueue, outlineColorQueue, valueColorQueue;
public:
	Node(double x = 0, double y = 0, int value = 0,
		double radius = 0, double outlineSize = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor, sf::Color variableColor = RedColor,
		sf::Font* font = nullptr, bool display = true, int numPointCircle = 30);
	void setValue(int newValue);
	void setX(double newX);
	void setY(double newY);
	void setXY(double newX, double newY);
	void moveX(double dx);
	void moveY(double dy);
	void setDisplay(bool display);
	void setFont(sf::Font* newFont);
	void setRadius(double newRadius);
	void setOutline(double newOutline);
	void setFillColor(sf::Color newColor);
	void setOutlineColor(sf::Color newColor);
	void setValueColor(sf::Color newColor);
	void setVariableColor(sf::Color newColor);
	double getX();
	double getY();
	double getRadius();
	double getOutlineSize();
	bool getDisplay();
	int getValue();
	sf::Color getFillColor();
	sf::Color getOutlineColor();
	sf::Color getValueColor();
	sf::Color getVariableColor();
	sf::CircleShape& getShape();
	void addMovement(double goalX, double goalY, sf::Time time);
	void updateMovement(sf::Time deltaT);
	void addZooming(double goalRadius, double goalOutline, sf::Time time);
	void updateZooming(sf::Time deltaT);
	void addFillColor(sf::Color goalColor, sf::Time time);
	void updateFillColor(sf::Time deltaT);
	void addOutlineColor(sf::Color goalColor, sf::Time time);
	void updateOutlineColor(sf::Time deltaT);
	void addValueColor(sf::Color goalColor, sf::Time time);
	void updateValueColor(sf::Time deltaT);
	void addVariable(std::string variable);
	void eraseVariable(std::string variable);
	void updateAnimation(sf::Time deltaT);
	void stopAnimation();
	void draw(sf::RenderWindow& window);
};