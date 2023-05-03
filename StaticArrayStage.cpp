#include <iostream>
#include "StaticArrayStage.h"
#include "Template.h"

StaticArrayStage::StaticArrayStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType, int numPointCircle) :
	Stage(window, { "Create", "Insert", "Delete", "Search", "Update", "Access"},
		{
			{"Empty", "Random", "Random Sorted", "Fixed Size", "Manual", "Upload File"},
			{"i = 0 (head)", "i = n (after tail)", "i = 1..n - 1 (middle)"},
			{"i = 0 (head)", "i = n - 1 (tail)", "i = 1..n - 2 (middle)"},
			{"v = ?"},
			{"i = ?, v = ?"},
			{"i = ?"}
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
				{"v ="},
				{"v ="},
				{"i =", "v ="}
			},
			{
				{},
				{},
				{"i ="}
			},
			{
				{"v ="}
			},
			{
				{"i =", "v ="}
			},
			{
				{"i ="}
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
				{singleNumber},
				{singleNumber},
				{singleNumber, singleNumber}
			},
			{
				{},
				{},
				{singleNumber}
			},
			{
				{singleNumber}
			},
			{
				{singleNumber, singleNumber}
			},
			{
				{singleNumber}
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
				{{0, maxValueData}},
				{{0, maxValueData}},
				{{0, maxSizeData}, {0, maxValueData}}
			},
			{
				{},
				{},
				{{0, maxSizeData}}
			},
			{
				{{0, maxValueData}}
			},
			{
				{{0, maxSizeData}, {0, maxValueData}}
			},
			{
				{{0, maxSizeData}}
			}
		},
		theme)
{
	ds = StaticArray(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial), numPointCircle);
	setDS(&ds);
}

std::pair<bool, ColorTheme> StaticArrayStage::processEvents() {
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
			if (modeString == "Manual") {
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
		if (operationName[curOperation] == "Insert") {
			if (modeString == "i = 0 (head)") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.insertFront(val);
				}
			}
			if (modeString == "i = n (after tail)") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.insertBack(val);
				}
			}
			if (modeString == "i = 1..n - 1 (middle)") {
				int pos = valueTypingBox[0].getProperInt();
				int val = valueTypingBox[1].getProperInt();
				if (pos != -1 && val != -1) {
					ds.insertMiddle(pos, val);
				}
			}
		}
		if (operationName[curOperation] == "Delete") {
			if (modeString == "i = 0 (head)") {
				ds.deleteFront();
			}
			if (modeString == "i = n - 1 (tail)") {
				ds.deleteBack();
			}
			if (modeString == "i = 1..n - 2 (middle)") {
				int pos = valueTypingBox[0].getProperInt();
				if (pos != -1) {
					ds.deleteMiddle(pos);
				}
			}
		}
		if (operationName[curOperation] == "Search") {
			int val = valueTypingBox[0].getProperInt();
			if (val != -1) {
				ds.search(val);
			}
		}
		if (operationName[curOperation] == "Update") {
			if (modeString == "i = ?, v = ?") {
				int pos = valueTypingBox[0].getProperInt();
				int val = valueTypingBox[1].getProperInt();
				if (pos != -1 && val != -1) {
					ds.updateVal(pos, val);
				}
			}
		}
		if (operationName[curOperation] == "Access") {
			if (modeString == "i = ?") {
				int pos = valueTypingBox[0].getProperInt();
				if (pos != -1) {
					ds.access(pos);
				}
			}
		}
		operating = false;
	}
	return { false, theme };
}

void StaticArrayStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void StaticArrayStage::render() {
	window.clear(theme == LightTheme ? MilkColor : EerieBlackColor);
	ds.draw(window);
	draw();
	window.display();
}

ColorTheme StaticArrayStage::run() {
	while (window.isOpen())
	{
		while (true) {
			auto curStatus = processEvents();
			if (curStatus.first) {
				return curStatus.second;
			}
			update(timePerFrame);
			render();
		}
	}
}