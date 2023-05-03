#pragma once
#include <SFML/Graphics.hpp>

const sf::Color SilverColor(185, 180, 174);
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
const sf::Color EerieBlackColor(30, 30, 30);
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
const sf::Color GrapeColor(101, 0, 164);
const sf::Color TaupeGrayColor(147, 145, 150);
const sf::Color TiffanyBlueColor(162, 232, 221);
const sf::Color EmeraldColor(50, 222, 138);
const sf::Color CaribbeanCurrentColor(0, 108, 103);
const sf::Color NyanzaColor(207, 255, 229);
const sf::Color WhiteSmokeColor(245, 245, 245);
const sf::Color AntiFlashWhiteColor(235, 235, 235);
const sf::Color PlatinumColor(200, 198, 194);
const sf::Color DimGrayColor(80, 80, 80);

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
		ColorNode(MilkColor, BlackColor, BlackColor, RedColor),
		ColorNode(OrangeColor, OrangeColor, MilkColor, RedColor),
		ColorNode(MilkColor, OrangeColor, OrangeColor, RedColor),
		ColorNode(LightGreenColor, LightGreenColor, MilkColor, RedColor),
		ColorNode(BlueColor, BlueColor, MilkColor, RedColor),
		ColorNode(MilkColor, SilverColor, SilverColor, RedColor)
	} ,
	{
		ColorNode(BlackColor, WhiteColor, WhiteColor, OrangeColor),
		ColorNode(YellowColor, YellowColor, BlackColor, OrangeColor),
		ColorNode(BlackColor, YellowColor, YellowColor, OrangeColor),
		ColorNode(GreenColor, GreenColor, BlackColor, OrangeColor),
		ColorNode(BlueColor, BlueColor, MilkColor, OrangeColor),
		ColorNode(MilkColor, SilverColor, SilverColor, OrangeColor)
	}
};

enum ColorBoxType {
	CommandBoxNormal, CommandBoxSelected, GoBoxNormal, TriangleButtonNormal, Typing_Box, MediaBox, CodeOuterBox, WarningBox, UploadBox
};

const int numColorBoxType = 9;

struct ColorBox {
	sf::Color fillColor, outlineColor, textColor;
	ColorBox(sf::Color fillColor, sf::Color outlineColor, sf::Color textColor);
};

const ColorBox colorBox[numColorBoxType][numColorTheme] =
{
	{ //CommandBoxNormal
		ColorBox(DarkPinkColor, BlackColor, BlackColor),
		ColorBox(GrapeColor, WhiteSmokeColor, WhiteSmokeColor),
	},
	{ //CommandBoxSelected
		ColorBox(DarkOrangeColor, BlackColor, BlackColor),
		ColorBox(CaribbeanCurrentColor, WhiteSmokeColor, WhiteSmokeColor),
	},
	{ //GoBoxNormal
		ColorBox(SlightlyGreenColor, BlackColor, WhiteColor),
		ColorBox(NyanzaColor, WhiteSmokeColor, BlackColor)
	},
	{ //TriangleButtonNormal
		ColorBox(PastelBlueColor, BlackColor, BlackColor),
		ColorBox(NyanzaColor, WhiteSmokeColor, WhiteSmokeColor)
	},
	{ //Typing_Box
		ColorBox(BlackColor, WhiteColor, WhiteColor),
		ColorBox(EerieBlackColor, WhiteSmokeColor, WhiteColor)
	},
	{ //MediaBox
		ColorBox(DarkPinkColor, BlackColor, BlackColor),
		ColorBox(GrapeColor, WhiteSmokeColor, WhiteColor)
	},
	{ //CodeOuterBox
		ColorBox(BuffColor, BlackColor, BlackColor),
		ColorBox(DarkBlueColor, WhiteSmokeColor, WhiteSmokeColor)
	},
	{ //WarningBox
		ColorBox(LightYellowColor, RedColor, BlackColor),
		ColorBox(EmeraldColor, RedColor, EerieBlackColor)
	},
	{ //UploadBox
		ColorBox(AntiFlashWhiteColor, BlackColor, BlackColor),
		ColorBox(AntiFlashWhiteColor, BlackColor, BlackColor)
	}
};

const sf::Color codeNormalViewColor[numColorTheme] = { BlackColor, WhiteSmokeColor };
const sf::Color codeHightlightViewColor[numColorTheme] = { WhiteColor, EerieBlackColor };
const sf::Color codeHighlightBackGroundColor[numColorTheme]{ BrightPinkColor, DarkCyanColor };

const sf::Color scrubberZipColor[numColorTheme] = { RedColor, CaribbeanCurrentColor };
const sf::Color scrubberPassedColor[numColorTheme] = { RedColor, EmeraldColor };
const sf::Color scrubberRemainColor[numColorTheme] = { BlackColor, TaupeGrayColor };

const sf::Color playButtonCircleColor[numColorTheme] = { DarkBrownColor, EmeraldColor };
const sf::Color playButtonTriangleColor[numColorTheme] = { DarkOrangeColor, EerieBlackColor };

const sf::Color choicesColor[numColorTheme] = { BlackColor, WhiteSmokeColor };
const sf::Color choicesOuterCircleColor[numColorTheme] = { DarkBrownColor,  EerieBlackColor };
const sf::Color choicesInnerCircleColor[numColorTheme] = { OrangeColor, EmeraldColor };

const sf::Color warningColor[numColorTheme] = { RedColor, RedColor };

const sf::Color backButtonNormalOutlineColor[numColorTheme] = { BlackColor, TaupeGrayColor };
const sf::Color backButtonNormalFillColor[numColorTheme] = { DarkPinkColor, GrapeColor };

const sf::Color announcementFillColor[numColorTheme] = { DarkOrangeColor , CaribbeanCurrentColor };
const sf::Color announcementTextColor[numColorTheme] = { BlackColor, WhiteColor };

const sf::Color warningFillColor[numColorTheme] = { YellowColor , CaribbeanCurrentColor };
const sf::Color warningTextColor[numColorTheme] = { BlackColor, WhiteColor };

const sf::Color bulbColor[numColorTheme] = { MilkColor, MilkColor };

const sf::Color errorTextColor[numColorTheme] = { RedColor, EmeraldColor };