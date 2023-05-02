#include <iostream>
#include "StackStage.h"
#include "Template.h"

StackStage::StackStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType, int numPointCircle) :
	Stage(window, { "Create", "Push", "Pop", "Peek", "Clear"},
		{ 
			{"Empty", "Random", "Random Sorted", "Fixed Size", "Custom", "Upload File"},
			{"Random", "v = ?"},
			{""},
			{""},
			{""}
		},
		{
			{
				{},
				{},
				{},
				{"n ="},
				{"v[] ="},
				{}
			},
			{
				{},
				{"v ="}
			},
			{
				{}
			},
			{
				{}
			},
			{
				{}
			}
		},
		{
			{
				{},
				{},
				{},
				{singleNumber},
				{multipleNumber},
				{}
			},
			{
				{},
				{singleNumber}
			},
			{
				{}
			},
			{
				{}
			},
			{
				{}
			}
		},
		{
			{
				{},
				{},
				{},
				{{0, maxSizeData}},
				{{0, maxValueData}},
				{}
			},
			{
				{},
				{{0, maxValueData}}
			},
			{
				{}
			},
			{
				{}
			},
			{
				{}
			}
		},
		theme)
{
	ds = Stack(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial), numPointCircle);
	setDS(&ds);
}

bool StackStage::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			return true;
			break;
		case sf::Event::MouseButtonPressed:
			if (handleMousePressed(event.mouseButton.x, event.mouseButton.y)) {
				return true;
			}
			break;
		case sf::Event::KeyPressed:
			handleKeyPressed(int(event.key.code));
			break;
		case sf::Event::MouseMoved:
			handleMouseMove(event.mouseMove.x, event.mouseMove.y);
			break;
		case sf::Event::MouseButtonReleased:
			handleMouseReleased(event.mouseButton.x, event.mouseButton.y);
			break;
		}
	}
	if (operating) {
		ds.setIsAnimating(true);
		std::string modeString = modeName[curOperation][curMode];
		if (operationName[curOperation] == "Create") {
			if (modeString == "Empty") {
				ds.createRandom(0, {});
			}
			if (modeString == "Random") {
				ds.createRandom();
			}
			if (modeString == "Random Sorted") {
				ds.createRandom(-1, {}, true);
			}
			if (modeString == "Fixed Size") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.createRandom(val);
				}
			}
			if (modeString == "Custom") {
				std::vector <int> values = valueTypingBox[0].getListInt();
				if (!values.empty()) {
					ds.createRandom(values.size(), values);
				}
			}
			if (modeString == "Upload File") {
				std::vector <int> values = readFromFile.getListInt();
				if (!values.empty()) {
					ds.createRandom(values.size(), values);
				}
			}
		}
		if (operationName[curOperation] == "Pop") {
			ds.pop();
		}
		if (operationName[curOperation] == "Peek") {
			ds.peek();
		}
		if (operationName[curOperation] == "Push") {
			if (modeString == "v = ?") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					std::cout << val << "\n";
					ds.push(val);
				}
			}
			else {
				ds.push(-1);
			}
		}
		if (operationName[curOperation] == "Clear") {
			ds.clear();
		}
		operating = false;
	}
	return false;
}

void StackStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void StackStage::render() {
	window.clear(theme == LightTheme ? MilkColor: EerieBlackColor);
	ds.draw(window);
	draw();
	window.display();
}

void StackStage::run() {
	sf::Clock mClock;
	sf::Time timePool = sf::Time::Zero;
	while (window.isOpen())
	{
		timePool += mClock.restart();
		while (timePool >= timePerFrame) {
			if (processEvents()) {
				return;
			}
			timePool -= timePerFrame;
			update(timePerFrame);
			render();
		}
	}
}