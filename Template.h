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
const sf::Color LightCyanColor(203, 228, 222);
const sf::Color DarkCyanColor(14, 131, 136);
const sf::Color LightYellowColor(255, 217, 61);
const sf::Color DarkBrownColor(79, 32, 13);
const sf::Color MilkColor(246, 241, 233);
const sf::Color SlightlyBlackColor(30, 30, 30);
const sf::Color NavyColor(0, 72, 124);
const sf::Color LightNavyColor(62, 102, 128);
const sf::Color DarkBlueColor(28, 130, 173);
const sf::Color SlightlyGreenColor(76, 175, 80);
const sf::Color DarkOrangeColor(255, 155, 66);
const sf::Color DarkPinkColor(240, 128, 128);
const sf::Color PastelBlueColor(191, 215, 234);
const sf::Color DarkYellowGreenColor(142, 168, 4);
const sf::Color BuffColor(216, 164, 127);
const sf::Color BrightPinkColor(238, 75, 106);

const bool ADD_EDGE = true;
const bool ERASE_EDGE = false;

const int maxID = int(1e9);
const int pointCountCircle = 50;
const double epsilonDouble = 1.f / 1000000.f;
const double PI = 3.14159265358979323846;
const sf::Time epsilonTime = sf::seconds(1.f / 1000000.f);
const sf::Time timePerFrame = sf::seconds(1.f / 60.f);
const sf::Time infTime = sf::seconds(1000000.f);
const sf::Time stepTime = sf::seconds(0.3f);
const sf::Time delayTime = sf::seconds(0.2f);
const sf::Time flickeringTime = sf::seconds(0.5f);

const double heightBox = 100;
const double widthBox = 250;
const double outlineBox = 5;
const double speedList[] = { 0.25, 0.5, 1.0, 2.0, 4.0 };

const int maxLetter = 4;

const double heightScrubber = 20;
const double zipWidth = 15;

enum EdgeType {
	Undirected, SinglyDirected, DoublyDirected
};

enum ColorTheme {
	LightTheme, DarkTheme
};

enum ColorNodeType {
	normal, highlight, lowlight, highlight2
};

enum TypingBoxMode {
	singleNumber, multipleNumber, string
};

const int numColorTheme = 2;
const int numColorNodeType = 4;
const int numTypingBoxMode = 3;

const int  typingModeMaxCharacter[numTypingBoxMode] = { 3, 20, 20 };

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
		ColorNode(BlackColor, WhiteColor, WhiteColor, OrangeColor),
		ColorNode(YellowColor, YellowColor, BlackColor, OrangeColor),
		ColorNode(BlackColor, YellowColor, YellowColor, OrangeColor),
		ColorNode(GreenColor, GreenColor, BlackColor, OrangeColor)
	}
};

enum ColorBoxType {
	CommandBoxNormal, CommandBoxSelected, GoBoxNormal, TriangleButtonNormal, Typing_Box, MediaBox, CodeOuterBox, WarningBox
};

const int numColorBoxType = 8;

struct ColorBox {
	sf::Color fillColor, outlineColor, textColor;
	ColorBox(sf::Color fillColor, sf::Color outlineColor, sf::Color textColor);
};

const ColorBox colorBox[numColorBoxType][numColorTheme] =
{
	{ //CommandBoxNormal
		ColorBox(DarkPinkColor, BlackColor, BlackColor),
		ColorBox(NavyColor, WhiteColor, WhiteColor),
	},
	{ //CommandBoxSelected
		ColorBox(DarkOrangeColor, BlackColor, BlackColor),
		ColorBox(DarkBlueColor, WhiteColor, WhiteColor),
	},
	{ //GoBoxNormal
		ColorBox(SlightlyGreenColor, BlackColor, WhiteColor),
		ColorBox(DarkGreenColor, WhiteColor, WhiteColor)
	},
	{ //TriangleButtonNormal
		ColorBox(PastelBlueColor, BlackColor, BlackColor),
		ColorBox(GreyColor, WhiteColor, WhiteColor)
	},
	{ //Typing_Box
		ColorBox(BlackColor, WhiteColor, WhiteColor),
		ColorBox(WhiteColor, WhiteColor, WhiteColor)
	},
	{ //MediaBox
		ColorBox(DarkPinkColor, BlackColor, BlackColor),
		ColorBox(DarkPinkColor, WhiteColor, WhiteColor)
	}, 
	{ //CodeOuterBox
		ColorBox(BuffColor, BlackColor, BlackColor),
		ColorBox(BuffColor, WhiteColor, WhiteColor)
	},
	{ //WarningBox
		ColorBox(LightYellowColor, RedColor, BlackColor),
		ColorBox(LightYellowColor, RedColor, WhiteColor)
	}
};

const sf::Color codeNormalViewColor[numColorTheme] = { BlackColor, BlackColor };
const sf::Color codeHightlightViewColor[numColorTheme] = { WhiteColor, WhiteColor };
const sf::Color codeHighlightBackGroundColor[numColorTheme]{ BrightPinkColor, DarkCyanColor };

const sf::Color scrubberZipColor[numColorTheme] = {LightYellowColor, LightYellowColor };
const sf::Color scrubberPassedColor[numColorTheme] = { OrangeColor, OrangeColor };
const sf::Color scrubberRemainColor[numColorTheme] = { DarkBrownColor, DarkBrownColor };

const sf::Color playButtonCircleColor[numColorTheme] = { LightYellowColor, LightYellowColor };
const sf::Color playButtonTriangleColor[numColorTheme] = { DarkBrownColor, DarkBrownColor };

const sf::Color choicesColor[numColorTheme] = {BlackColor, DarkBrownColor};
const sf::Color choicesOuterCircleColor[numColorTheme] = { DarkBrownColor, DarkBrownColor };
const sf::Color choicesInnerCircleColor[numColorTheme] = { OrangeColor, OrangeColor };

const sf::Color warningColor[numColorTheme] = { RedColor, RedColor };

std::string intToString(int a);
int stringToInt(std::string a);

double dist2p(double x1, double y1, double x2, double y2);

sf::Time min(const sf::Time& a, const sf::Time& b);
sf::Time max(const sf::Time& a, const sf::Time& b);

void MovePoint(double& x1, double& y1, double x2, double y2, double dist);

void MovePointParallel(double& x, double& y, double x1, double y1, double x2, double y2); //move point A(x, y) to a A'(x', y') so that AA' is parallel to BC in which B is (x1, y1) and C is (x2, y2) and |AA'|=|BC|

const std::string fontName[] = { "Fonts/arial.ttf", "Fonts/Consolas.ttf"};
const int numFont = 2;
enum fontType {
	Arial, Consolas
};
extern std::vector <sf::Font> listFont;
sf::Font* font(fontType id);

double area(double x1, double y1, double x2, double y2, double x3, double y3);

bool isInsideTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double x, double y);

void RotatePoint(double& x, double& y, double cx, double cy, double angle);