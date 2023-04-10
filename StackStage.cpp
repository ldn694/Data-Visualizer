#include <iostream>
#include "StackStage.h"
#include "Template.h"

StackStage::StackStage(sf::RenderWindow& window, double radius, double outlineSize, double lineThickness,
	ColorTheme theme, EdgeType edgeType) :
	Stage(window, { "Create", "Push", "Pop", "Peek" }, 
		{ 
			{"Random", "n = ?"}, 
			{"v = ?"},
			{""},
			{""}
		},
		{
			{
				{},
				{"n = "}
			},
			{
				{"v = "}
			},
			{
				{}
			},
			{
				{}
			}
		}
		,
		{
			{
				{},
				{{0, 10}}
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
	mediaControl.setDS(&ds);
}

void StackStage::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			return;
			break;
		case sf::Event::MouseButtonPressed:
			handleMousePressed(event.mouseButton.x, event.mouseButton.y);
			if (operating) {
				ds.setIsAnimating(true);
				std::string modeString = modeName[curOperation][curMode];
				if (operationName[curOperation] == "Create") {
					if (modeString == "Random") {
						ds.createRandom();
					}
					else {
						ds.createRandom(valueTypingBox[0].getInt());
					}
				}
				if (operationName[curOperation] == "Pop") {
					ds.pop();
				}
				if (operationName[curOperation] == "Peek") {
					ds.peek();
				}
				if (operationName[curOperation] == "Push") {
					ds.push(valueTypingBox[0].getInt());
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
}

void StackStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
	//std::cout << "done updated!\n";
}

void StackStage::render() {
	window.clear(theme == LightTheme ? WhiteColor : SlightlyBlackColor);
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
		processEvents();
		timePool += mClock.restart();
		while (timePool >= timePerFrame) {
			timePool -= timePerFrame;
			update(timePerFrame);
			render();
		}
	}
}