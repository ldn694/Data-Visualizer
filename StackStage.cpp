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
	setDSName("Stack");
	setCurOperationName("");
}

std::pair<bool, ColorTheme> StackStage::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			return { true, theme };
			break;
		case sf::Event::MouseButtonPressed:
			if (handleMousePressed(event.mouseButton.x, event.mouseButton.y)) {
				return { true, theme };
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
				setCurOperationName("Create empty stack");
				ds.createRandom(0, {});
			}
			if (modeString == "Random") {
				setCurOperationName("Create random stack");
				ds.createRandom();
			}
			if (modeString == "Random Sorted") {
				setCurOperationName("Create random sorted stack");
				ds.createRandom(-1, {}, true);
			}
			if (modeString == "Fixed Size") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					setCurOperationName("Create stack of size " + intToString(val));
					ds.createRandom(val);
				}
			}
			if (modeString == "Custom") {
				std::vector <int> values = valueTypingBox[0].getListInt();
				if (!values.empty()) {
					setCurOperationName("Create custom stack");
					ds.createRandom(values.size(), values);
				}
			}
			if (modeString == "Upload File") {
				std::vector <int> values = readFromFile.getListInt();
				if (!values.empty()) {
					setCurOperationName("Create custom stack");
					ds.createRandom(values.size(), values);
				}
			}
		}
		if (operationName[curOperation] == "Pop") {
			setCurOperationName("Pop element at top of stack");
			ds.pop();
		}
		if (operationName[curOperation] == "Peek") {
			setCurOperationName("Peek element at top of stack");
			ds.peek();
		}
		if (operationName[curOperation] == "Push") {
			if (modeString == "v = ?") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					setCurOperationName("Push " + intToString(val) + " into stack");
					ds.push(val);
				}
			}
			else {
				setCurOperationName("Push random value into stack");
				ds.push(-1);
			}
		}
		if (operationName[curOperation] == "Clear") {
			setCurOperationName("Clear stack");
			ds.clear();
		}
		operating = false;
	}
	return { false, theme };
}

void StackStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void StackStage::render() {
	window.clear(theme == LightTheme ? LavenderBushColor : EerieBlackColor);
	ds.draw(window);
	draw();
	window.display();
}

ColorTheme StackStage::run() {
	window.setMouseCursor(arrowCursor);
	while (window.isOpen())
	{
		auto curStatus = processEvents();
		if (curStatus.first) {
			return curStatus.second;
		}
		update(timePerFrame);
		render();
	}
}