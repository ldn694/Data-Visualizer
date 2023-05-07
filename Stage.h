#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include "Template.h"
#include "Box.h"
#include "TriangleButton.h"
#include "TypingBox.h"
#include "IngameSettings.h"
#include "DataStructure.h"
#include "MultipleChoice.h"
#include "MediaControl.h"
#include "BackButton.h"
#include "ReadFromFile.h"

struct Stage {
protected:
	DataStructure* ds;
	std::vector <std::string> operationName;
	std::vector <Box> operationBox;
	int curOperation, numOperation;
	bool operationSelecting;
	bool operating;

	sf::Text dsName, curOperationName;

	Box goBox, outerGoBox;

	std::vector <std::vector <std::string> > modeName;
	std::vector <std::vector <Box> > modeBox;
	std::vector <int> numMode;
	int curMode;

	TriangleButton prevModeButton, nextModeButton;
	sf::CircleShape upwardTriangle;
	bool upwarding;

	std::vector <std::vector <std::vector <std::string> > > valueName;
	std::vector <std::vector <std::vector <TypingBoxMode> > > typingMode;
	std::vector <std::vector <std::vector <std::pair <int, int> > > > valueBound;
	std::vector <BigTypingBox> valueTypingBox;

	ReadFromFile readFromFile;

	std::vector <std::vector <int>> numValue;

	IngameSettings ingameSettings;
	BackButton backButton;


	MyShape lightBulb, darkBulb, themeBox;
	ColorTheme theme;
	sf::RenderWindow& window;
public:
	Stage(sf::RenderWindow &window, std::vector <std::string> operationName, std::vector <std::vector <std::string> > modeName, 
		std::vector <std::vector <std::vector <std::string> > > valueName, 
		std::vector <std::vector <std::vector <TypingBoxMode> > > typingMode,
		std::vector <std::vector <std::vector <std::pair <int, int> > > > valueBound,
		ColorTheme theme = LightTheme, DataStructure* ds = nullptr);
	void setDS(DataStructure* newDS);
	void setDSName(std::string name);
	void setCurOperationName(std::string name);
	void updateModeBox(int newMode);
	bool handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y);
	void handleMouseReleased(double x, double y);
	void handleKeyPressed(int key);
	void draw();
	void stageUpdate(sf::Time deltaT);
	void setTheme(ColorTheme newTheme);
};