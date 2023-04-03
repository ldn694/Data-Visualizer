#pragma once
#include <SFML/Graphics.hpp>

const int WIDTH_RES = 1600;
const int HEIGHT_RES = 900;

const sf::Color GreyColor(211, 211, 211);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);
const sf::Color OrangeColor(255, 128, 0);
const sf::Color YellowColor(255, 255, 0);
const sf::Color LightGreenColor(82, 188, 105);
const sf::Color DarkGreenColor(48, 104, 68);
const sf::Color LightGreyBlueColor(176, 194, 219);
const sf::Color DarkGreyBlueColor(71, 108, 158);
const sf::Color PurpleColor(112, 41, 99);

const bool ADD_EDGE = true;
const bool ERASE_EDGE = false;

const int maxID = int(1e9);
const int pointCountCircle = 50;
const double epsilonDouble = 1.f / 1000000.f;
const sf::Time epsilonTime = sf::seconds(1.f / 1000000.f);
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
const sf::Time infTime = sf::seconds(1000000.f);
const sf::Time stepTime = sf::seconds(0.3f);
const sf::Time delayTime = sf::seconds(0.2f);

enum EdgeType {
	Undirected, SinglyDirected, DoublyDirected
};

enum ColorTheme {
	LightTheme, DarkTheme
};

enum ColorNodeType {
	normal, highlight, lowlight, highlight2
};

const int numColorTheme = 2;
const int numColorNodeType = 4;

struct ColorNode {
	sf::Color fillColor, outlineColor, valueColor, variableColor;
	ColorNode(sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor);
};

const ColorNode colorNode[numColorTheme][numColorNodeType] =
{
	{
		ColorNode(WhiteColor, BlackColor, BlackColor, RedColor),
		ColorNode(OrangeColor, OrangeColor, WhiteColor, RedColor),
		ColorNode(WhiteColor, OrangeColor, OrangeColor, RedColor),
		ColorNode(LightGreenColor, LightGreenColor, WhiteColor, RedColor)
	} ,
	{
		ColorNode(RedColor, YellowColor, YellowColor, BlueColor),
		ColorNode(PurpleColor, PurpleColor, RedColor, BlueColor),
		ColorNode(RedColor, PurpleColor, PurpleColor, BlueColor),
		ColorNode(DarkGreyBlueColor, DarkGreyBlueColor, RedColor, BlueColor)
	}
};

enum ColorBoxType {
	CommandBoxNormal, CommandBoxSelected
};

const int numColorBoxType = 2;

struct ColorBox {
	sf::Color fillColor, outlineColor, textColor;
	ColorBox(sf::Color fillColor, sf::Color outlineColor, sf::Color textColor);
};

const ColorBox colorBox[numColorTheme][numColorBoxType] =
{
	{
		ColorBox(LightGreyBlueColor, BlackColor, BlackColor),
		ColorBox(DarkGreyBlueColor, BlackColor, BlackColor)
	},
	{
		ColorBox(PurpleColor, GreenColor, OrangeColor),
		ColorBox(PurpleColor, GreenColor, OrangeColor)
	}
};

std::string intToString(int a);
int stringToInt(std::string& a);

double dist2p(double x1, double y1, double x2, double y2);

sf::Time min(const sf::Time& a, const sf::Time& b);
sf::Time max(const sf::Time& a, const sf::Time& b);

void MovePoint(double& x1, double& y1, double x2, double y2, double dist);