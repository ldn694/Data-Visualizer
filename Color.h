#pragma once
#include <SFML/Graphics.hpp>

const sf::Color SilverColor(185, 180, 174);
const sf::Color DimGrayColor(105, 105, 105);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);
const sf::Color OrangeColor(255, 128, 0);
const sf::Color YellowColor(255, 255, 0);
const sf::Color LightGreenColor(82, 188, 105);
const sf::Color LightYellowColor(255, 217, 61);

const sf::Color LavenderBushColor(255, 245, 248);
const sf::Color EerieBlackColor(30, 30, 30);
const sf::Color AntiFlashWhiteColor(235, 235, 235);

const sf::Color RoyalPurpleColor(108, 74, 182);
const sf::Color VistaBlueColor(185, 224, 255);
const sf::Color MediumSlateBlueColor(141, 114, 225);
const sf::Color UranianBlueColor(141, 158, 255);
const sf::Color DarkCyanColor(14, 131, 136);

const sf::Color LightRedColor(255, 148, 148);
const sf::Color TeaRoseColor(255, 209, 209);
const sf::Color BrightPinkColor(238, 75, 106);

enum ColorTheme {
	LightTheme, DarkTheme
};

enum ColorNodeType {
	normal, highlight, lowlight, highlight2, highlight3, faded
};

enum TypingBoxMode {
	singleNumber, multipleNumber, string
};

const int numColorTheme = 2;
const int numColorNodeType = 6;
const int numTypingBoxMode = 3;

const int  typingModeMaxCharacter[numTypingBoxMode] = { 3, 20, 20 };

struct ColorNode {
	sf::Color fillColor, outlineColor, valueColor, variableColor;
	ColorNode(sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor);
};

const ColorNode colorNode[numColorTheme][numColorNodeType] =
{
	{
		ColorNode(LavenderBushColor, BlackColor, BlackColor, RedColor),
		ColorNode(OrangeColor, OrangeColor, LavenderBushColor, RedColor),
		ColorNode(LavenderBushColor, OrangeColor, OrangeColor, RedColor),
		ColorNode(LightGreenColor, LightGreenColor, LavenderBushColor, RedColor),
		ColorNode(BlueColor, BlueColor, LavenderBushColor, RedColor),
		ColorNode(LavenderBushColor, SilverColor, SilverColor, RedColor)
	} ,
	{
		ColorNode(EerieBlackColor, WhiteColor, WhiteColor, OrangeColor),
		ColorNode(YellowColor, YellowColor, EerieBlackColor, OrangeColor),
		ColorNode(EerieBlackColor, YellowColor, YellowColor, OrangeColor),
		ColorNode(GreenColor, GreenColor, EerieBlackColor, OrangeColor),
		ColorNode(BlueColor, BlueColor, LavenderBushColor, OrangeColor),
		ColorNode(EerieBlackColor, DimGrayColor, DimGrayColor, OrangeColor)
	}
};

enum ColorBoxType {
	CommandBoxNormal, CommandBoxSelected, GoBoxNormal, GoBoxSelected, TriangleButtonNormal, TriangleButtonSelected, Typing_Box, MediaBox, CodeOuterBox, UploadBox
};

const int numColorBoxType = 10;

struct ColorBox {
	sf::Color fillColor, outlineColor, textColor;
	ColorBox(sf::Color fillColor, sf::Color outlineColor, sf::Color textColor);
};

const ColorBox colorBox[numColorBoxType][numColorTheme] =
{
	{ //CommandBoxNormal
		ColorBox(LightRedColor , LavenderBushColor, BlackColor),
		ColorBox(RoyalPurpleColor, EerieBlackColor, LavenderBushColor),
	},
	{ //CommandBoxSelected
		ColorBox(BrightPinkColor, LavenderBushColor, WhiteColor),
		ColorBox(VistaBlueColor, EerieBlackColor, EerieBlackColor),
	},
	{ //GoBoxNormal
		ColorBox(LavenderBushColor, LavenderBushColor, EerieBlackColor),
		ColorBox(EerieBlackColor, EerieBlackColor, LavenderBushColor)
	},
	{ //GoBoxSelected
		ColorBox(BrightPinkColor, BrightPinkColor, WhiteColor),
		ColorBox(VistaBlueColor, VistaBlueColor, EerieBlackColor)
	},
	{ //TriangleButtonNormal
		ColorBox(EerieBlackColor, LavenderBushColor, BlackColor),
		ColorBox(LavenderBushColor, EerieBlackColor, LavenderBushColor)
	},
	{ //TriangleButtonSelected
		ColorBox(BrightPinkColor, LavenderBushColor, BlackColor),
		ColorBox(VistaBlueColor, EerieBlackColor, LavenderBushColor)
	},
	{ //Typing_Box
		ColorBox(BlackColor, WhiteColor, WhiteColor),
		ColorBox(EerieBlackColor, LavenderBushColor, WhiteColor)
	},
	{ //MediaBox
		ColorBox(LightRedColor, LavenderBushColor, BlackColor),
		ColorBox(RoyalPurpleColor, EerieBlackColor, WhiteColor)
	},
	{ //CodeOuterBox
		ColorBox(TeaRoseColor, LavenderBushColor, WhiteColor),
		ColorBox(UranianBlueColor, EerieBlackColor, EerieBlackColor)
	},
	{ //UploadBox
		ColorBox(AntiFlashWhiteColor, BlackColor, BlackColor),
		ColorBox(AntiFlashWhiteColor, BlackColor, BlackColor)
	}
};

const sf::Color codeNormalViewColor[numColorTheme] = { BlackColor, EerieBlackColor };
const sf::Color codeHightlightViewColor[numColorTheme] = { WhiteColor, EerieBlackColor };
const sf::Color codeHighlightBackGroundColor[numColorTheme]{ BrightPinkColor, DarkCyanColor };

const sf::Color scrubberZipColor[numColorTheme] = { BrightPinkColor, UranianBlueColor };
const sf::Color scrubberPassedColor[numColorTheme] = { TeaRoseColor, MediumSlateBlueColor };
const sf::Color scrubberRemainColor[numColorTheme] = { BlackColor, EerieBlackColor };

const sf::Color playButtonCircleColor[numColorTheme] = { BrightPinkColor, UranianBlueColor };
const sf::Color playButtonTriangleColor[numColorTheme] = { TeaRoseColor, EerieBlackColor };

const sf::Color choicesColor[numColorTheme] = { EerieBlackColor, LavenderBushColor };
const sf::Color choicesOuterCircleColor[numColorTheme] = { EerieBlackColor,  EerieBlackColor };
const sf::Color choicesInnerCircleColor[numColorTheme] = { TeaRoseColor, UranianBlueColor };

const sf::Color backButtonNormalOutlineColor[numColorTheme] = { LavenderBushColor, EerieBlackColor };
const sf::Color backButtonNormalFillColor[numColorTheme] = { LightRedColor, RoyalPurpleColor };

const sf::Color announcementFillColor[numColorTheme] = { BrightPinkColor , VistaBlueColor };
const sf::Color announcementTextColor[numColorTheme] = { WhiteColor, EerieBlackColor };

const sf::Color warningFillColor[numColorTheme] = { TeaRoseColor , MediumSlateBlueColor };
const sf::Color warningTextColor[numColorTheme] = { BlackColor, WhiteColor };

const sf::Color bulbColor[numColorTheme] = { LavenderBushColor, LavenderBushColor };

const sf::Color errorTextColor[numColorTheme] = { RedColor, UranianBlueColor };