#pragma once
#include <SFML/Graphics.hpp>

const sf::Color GreyColor(211, 211, 211);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);
const sf::Color OrangeColor(255, 128, 0);

const bool ADD_EDGE = true;
const bool ERASE_EDGE = false;

const int pointCountCircle = 50;
const double epsilonDouble = 1.f / 1000000.f;
const sf::Time epsilonTime = sf::seconds(1.f / 1000000.f);
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
const sf::Time infTime = sf::seconds(1000000.f);

enum EdgeType {
	Undirected, SinglyDirected, DoublyDirected
};

std::string intToString(int a);
int stringToInt(std::string& a);

double dist2p(double x1, double y1, double x2, double y2);

sf::Time min(const sf::Time& a, const sf::Time& b);
sf::Time max(const sf::Time& a, const sf::Time& b);

void MovePoint(double& x1, double& y1, double x2, double y2, double dist);