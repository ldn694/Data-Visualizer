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
		theme)
{
	ds = Stack(radius, outlineSize, lineThickness, theme, edgeType, font(fontType::Arial));
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
				std::string modeString = modeName[curOperation][curMode];
				if (operationName[curOperation] == "Create") {
					if (modeString == "Random") {
						ds.createRandom();
					}
					else {
						ds.createRandom(valueTypingBox.getInt());
					}
				}
				if (operationName[curOperation] == "Pop") {
					ds.pop();
				}
				if (operationName[curOperation] == "Peek") {
					ds.peek();
				}
				if (operationName[curOperation] == "Push") {
					ds.push(valueTypingBox.getInt());
				}
				operating = false;
			}
			break;
		case sf::Event::KeyPressed:
			handleKeyPressed(int(event.key.code));
		}
	}
}

void StackStage::update(sf::Time deltaT) {
	ds.update(deltaT);
	stageUpdate(deltaT);
}

void StackStage::render() {
	window.clear(theme == LightTheme ? WhiteColor : BlackColor);
	ds.draw(window);
	draw();
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