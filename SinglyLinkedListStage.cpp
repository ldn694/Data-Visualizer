#include <iostream>
#include "SinglyLinkedListStage.h"
#include "Template.h"

SinglyLinkedListStage::SinglyLinkedListStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType, int numPointCircle) :
	Stage(window, { "Create", "Search", "Insert", "Delete", "Update" },
		{
			{"Empty", "Random", "Random Sorted", "Fixed Size", "Manual", "Upload File"},
			{"v = ?"},
			{"i = 0 (head)", "i = n (after tail)", "i = 1..n - 1 (middle)"},
			{"i = 0 (head)", "i = n - 1 (tail)", "i = 1..n - 2 (middle)"},
			{"i = 0 (head)", "i = n - 1 (tail)", "i = 1..n - 2 (middle)"},
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
				{"v ="}
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
				{"v ="},
				{"v ="},
				{"i =", "v ="}
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
				{singleNumber}
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
				{singleNumber},
				{singleNumber},
				{singleNumber, singleNumber}
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
				{{0, maxValueData}}
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
				{{0, maxValueData}},
				{{0, maxValueData}},
				{{0, maxSizeData}, {0, maxValueData}}
			}
		},
		theme)
{
	ds = SinglyLinkedList(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial), numPointCircle);
	setDS(&ds);
	setDSName("Singly Linked List");
}

std::pair<bool, ColorTheme> SinglyLinkedListStage::processEvents() {
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
		if (operationName[curOperation] == "Search") {
			int val = valueTypingBox[0].getProperInt();
			if (val != -1) {
				ds.search(val);
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
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.deleteMiddle(val);
				}
			}
		}
		if (operationName[curOperation] == "Update") {
			if (modeString == "i = 0 (head)") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.updateFront(val);
				}
			}
			if (modeString == "i = n - 1 (tail)") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.updateBack(val);
				}
			}
			if (modeString == "i = 1..n - 2 (middle)") {
				int pos = valueTypingBox[0].getProperInt();
				int val = valueTypingBox[1].getProperInt();
				if (pos != -1 && val != -1) {
					ds.updateMiddle(pos, val);
				}
			}
		}
		operating = false;
	}
	return { false, theme };
}

void SinglyLinkedListStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void SinglyLinkedListStage::render() {
	window.clear(theme == LightTheme ? LavenderBushColor : EerieBlackColor);
	ds.draw(window);
	draw();
	window.display();
}

ColorTheme SinglyLinkedListStage::run() {
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