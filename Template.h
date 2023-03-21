#pragma once
#include <SFML/Graphics.hpp>

const sf::Color GreyColor(211, 211, 211);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);

const double pointCountCircle = 50;
const sf::Time epsilonTime = sf::seconds(1.f / 10000.f);
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

enum EdgeType {
	Undirected, SinglyDirected, DoublyDirected
};

std::string intToString(int a);
int stringToInt(std::string& a);

double dist2p(double x1, double y1, double x2, double y2);