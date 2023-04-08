#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include "Template.h"
#include "Box.h"
#include "TriangleButton.h"
#include "TypingBox.h"
#include "Scrubber.h"

struct Stage {
protected:
	std::vector <std::string> operationName;
	std::vector <Box> operationBox;
	int curOperation, numOperation;
	bool operationSelecting;
	bool operating;

	Box goBox, outerGoBox;

	std::vector <std::vector <std::string> > modeName;
	std::vector <std::vector <Box> > modeBox;
	std::vector <int> numMode;
	int curMode;

	TriangleButton prevModeButton, nextModeButton;

	std::vector <std::vector <std::vector <std::string> > > valueName;
	std::vector <std::vector <std::vector <std::pair <int, int> > > > valueBound;
	std::vector <BigTypingBox> valueTypingBox;
	std::vector <std::vector <int>> numValue;

	Scrubber scrubber;

	ColorTheme theme;
	sf::RenderWindow& window;
public:
	Stage(sf::RenderWindow &window, std::vector <std::string> operationName, std::vector <std::vector <std::string> > modeName, 
		std::vector <std::vector <std::vector <std::string> > > valueName, 
		std::vector <std::vector <std::vector <std::pair <int, int> > > > valueBound,
		ColorTheme theme = LightTheme);
	void updateModeBox(int newMode);
	void handleMousePressed(double x, double y);
	void handleMouseMove(double x, double y);
	void handleMouseReleased(double x, double y);
	void handleKeyPressed(int key);
	void draw();
	void stageUpdate(sf::Time deltaT);
	void setTheme(ColorTheme newTheme);
};