#include <iostream>
#include "StackStage.h"
#include "Template.h"

StackStage::StackStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType) :
	Stage(window, { "Create", "Push", "Pop", "Peek" }, 
		{ 
			{"Random", "n = ?", "Custom"},
			{"v = ?"},
			{""},
			{""}
		},
		{
			{
				{},
				{"n ="},
				{"v[] ="}
			},
			{
				{"v ="}
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
				{singleNumber},
				{multipleNumber}
			},
			{
				{singleNumber}
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
				{{0, 10}},
				{{0, 99}}
			},
			{
				{{0, 99}}
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
	ds = Stack(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial));
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
			if (operating) {
				ds.setIsAnimating(true);
				std::string modeString = modeName[curOperation][curMode];
				if (operationName[curOperation] == "Create") {
					if (modeString == "Random") {
						ds.createRandom();
					}
					if (modeString == "n = ?") {
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
				}
				if (operationName[curOperation] == "Pop") {
					ds.pop();
				}
				if (operationName[curOperation] == "Peek") {
					ds.peek();
				}
				if (operationName[curOperation] == "Push") {
					int val = valueTypingBox[0].getProperInt();
					if (val != -1) {
						ds.push(val);
					}
				}
				operating = false;
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
	return false;
}

void StackStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
	//std::cout << "done updated!\n";
}

void StackStage::render() {
	window.clear(theme == LightTheme ? MilkColor: EerieBlackColor);
	ds.draw(window);
	//std::cout << "drawed ds\n";
	draw();
	//std::cout << "drawed stage\n";
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