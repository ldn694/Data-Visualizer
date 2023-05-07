#include <iostream>
#include "QueueStage.h"
#include "Template.h"

QueueStage::QueueStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType, int numPointCircle) :
	Stage(window, { "Create", "Add", "Remove", "Peek", "Clear"},
		{
			{"Empty", "Random", "Random Sorted", "Fixed Size", "Custom", "Upload File"},
			{"Random", "v = ?"},
			{""},
			{"Front", "Back"},
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
				{},
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
				{},
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
				{},
				{}
			},
			{
				{}
			}
		},
		theme)
{
	ds = Queue(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial), numPointCircle);
	setDS(&ds);
	setDSName("Queue");
}

std::pair<bool, ColorTheme> QueueStage::processEvents() {
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
		if (operationName[curOperation] == "Remove") {
			ds.remove();
		}
		if (operationName[curOperation] == "Peek") {
			if (modeString == "Front") {
				ds.peekFront();
			}
			if (modeString == "Back") {
				ds.peekBack();
			}
		}
		if (operationName[curOperation] == "Add") {
			if (modeString == "v = ?") {
				int val = valueTypingBox[0].getProperInt();
				if (val != -1) {
					ds.add(val);
				}
			}
			else {
				ds.add(-1);
			}
		}
		if (operationName[curOperation] == "Clear") {
			ds.clear();
		}
		operating = false;
	}
	return { false, theme };
}

void QueueStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void QueueStage::render() {
	window.clear(theme == LightTheme ? LavenderBushColor : EerieBlackColor);
	ds.draw(window);
	draw();
	window.display();
}

ColorTheme QueueStage::run() {
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