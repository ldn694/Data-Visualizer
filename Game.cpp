#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "SinglyLinkedListStage.h"
#include "DoublyLinkedListStage.h"
#include "CircularLinkedListStage.h"
#include "StackStage.h"
#include "QueueStage.h"
#include "StaticArrayStage.h"
#include "DynamicArrayStage.h"
#include "Template.h"

Game::Game(sf::ContextSettings settings): 
	window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings),
	lightBulb("Images/full_bulb.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 8 / 46 * 30, widthBox / 8, bulbColor),
	darkBulb("Images/empty_bulb.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 8 / 46 * 30, widthBox / 8, bulbColor),
	themeBox("Images/curved_square.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 4, widthBox / 4, backButtonNormalFillColor)
{
	window.setMouseCursor(arrowCursor);
	window.setFramerateLimit(60);
	stackBox = Box(410, 400, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Stack", font(fontType::Prototype), 30, NO_BORDER, 3);
	queueBox = Box(830, 400, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Queue", font(fontType::Prototype), 30, NO_BORDER, 3);
	sllBox = Box(200, 550, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Singly Linked List", font(fontType::Prototype), 30, NO_BORDER, 3);
	dllBox = Box(620, 550, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Doubly Linked List", font(fontType::Prototype), 30, NO_BORDER, 3);
	cllBox = Box(1040, 550, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Circular Linked List", font(fontType::Prototype), 30, NO_BORDER, 3);
	staticArrayBox = Box(410, 700, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Static Array", font(fontType::Prototype), 30, NO_BORDER, 3);
	dynamicArrayBox = Box(830, 700, 360, 120, { CommandBoxNormal, CommandBoxSelected }, "Dynamic Array", font(fontType::Prototype), 30, NO_BORDER, 3);
	theme = loadFromFileTheme();
	projName.setFont(*font(fontType::Prototype));
	projName.setCharacterSize(70);
	projName.setString("DATA VISUALIZER");
	projName.setStyle(sf::Text::Bold);
	projName.setOrigin(projName.getLocalBounds().left + projName.getLocalBounds().width / 2, projName.getLocalBounds().top + projName.getLocalBounds().height / 2);
	projName.setPosition(WIDTH_RES / 2, 105);
	description.setFont(*font(fontType::Prototype));
	description.setCharacterSize(30);
	description.setString("CS162 Lab Project – Based on VisuAlgo");
	description.setStyle(sf::Text::Italic);
	description.setOrigin(description.getLocalBounds().left + description.getLocalBounds().width / 2, description.getLocalBounds().top + description.getLocalBounds().height / 2);
	description.setPosition(WIDTH_RES / 2, 205);
	author.setFont(*font(fontType::Prototype));
	author.setCharacterSize(30);
	author.setString("by Le Duc Nhuan - 22125070 - 22TT1");
	author.setStyle(sf::Text::Italic);
	author.setOrigin(author.getLocalBounds().left + author.getLocalBounds().width / 2, author.getLocalBounds().top + author.getLocalBounds().height / 2);
	author.setPosition(WIDTH_RES / 2, 256);
}

void Game::runStack() {
	window.setMouseCursor(waitCursor);
	StackStage stack(window, 20, 5, 4, theme, SinglyDirected, 30);
	theme = stack.run();
}

void Game::runQueue() {
	window.setMouseCursor(waitCursor);
	QueueStage queue(window, 20, 5, 4, theme, SinglyDirected, 30);
	theme = queue.run();
}

void Game::runSLL() {
	window.setMouseCursor(waitCursor);
	SinglyLinkedListStage sll(window, 20, 5, 4, theme, SinglyDirected, 30);
	theme = sll.run();
}

void Game::runDLL() {
	window.setMouseCursor(waitCursor);
	DoublyLinkedListStage dll(window, 20, 5, 4, theme, DoublyDirected, 30);
	theme = dll.run();
}

void Game::runCLL() {
	window.setMouseCursor(waitCursor);
	CircularLinkedListStage cll(window, 20, 5, 4, theme, SinglyDirected, 30);
	theme = cll.run();
}

void Game::runStaticArray() {
	window.setMouseCursor(waitCursor);
	StaticArrayStage staticArray(window, 20 * sqrt(2), 3, 4, theme, SinglyDirected, 4);
	theme = staticArray.run();
}

void Game::runDynamicArray() {
	window.setMouseCursor(waitCursor);
	DynamicArrayStage dynamicArray(window, 20 * sqrt(2), 3, 4, theme, SinglyDirected, 4);
	theme = dynamicArray.run();
}

void Game::handleMouseMove(double x, double y) {
	if (themeBox.handleMouseMove(x, y, window)) return;
	if (stackBox.handleMouseMove(x, y, window)) return;
	if (queueBox.handleMouseMove(x, y, window)) return;
	if (sllBox.handleMouseMove(x, y, window)) return;
	if (dllBox.handleMouseMove(x, y, window)) return;
	if (cllBox.handleMouseMove(x, y, window)) return;
	if (staticArrayBox.handleMouseMove(x, y, window)) return;
	if (dynamicArrayBox.handleMouseMove(x, y, window)) return;
	window.setMouseCursor(arrowCursor);
}

ColorTheme Game::loadFromFileTheme() {
	std::ifstream fi;
	fi.open("Settings/theme.dat");
	int temp;
	fi >> temp;
	fi.close();
	return ColorTheme(temp);
}

void Game::saveFileTheme() {
	std::ofstream fo;
	fo.open("Settings/theme.dat");
	fo << int(theme);
	fo.close();
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			return;
			break;
		case sf::Event::MouseButtonPressed:
			if (stackBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runStack();
			}
			if (queueBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runQueue();
			}
			if (sllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runSLL();
			}
			if (dllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runDLL();
			}
			if (cllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runCLL();
			}
			if (staticArrayBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runStaticArray();
			}
			if (dynamicArrayBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runDynamicArray();
			}
			if (themeBox.isMousePressed(event.mouseButton.x, event.mouseButton.y)) {
				theme = ColorTheme((theme + 1) % numColorTheme);
			}
			else {
				handleMouseMove(2000, 2000);
			}
			break;
		case sf::Event::MouseMoved:
			handleMouseMove(event.mouseMove.x, event.mouseMove.y);
			break;
		}
	}
}

void Game::update(sf::Time deltaT)
{
	
}

void Game::render()
{
	window.clear(theme == LightTheme ? LavenderBushColor : EerieBlackColor);
	sf::Color textColor = theme == LightTheme ? BlackColor : WhiteColor;
	themeBox.draw(window, theme);
	if (theme == LightTheme) {
		lightBulb.draw(window, theme);
	}
	else {
		darkBulb.draw(window, theme);
	}
	projName.setFillColor(textColor);
	description.setFillColor(textColor);
	author.setFillColor(textColor);
	window.draw(projName);
	window.draw(description);
	window.draw(author);
	stackBox.draw(window, theme); 
	queueBox.draw(window, theme);
	sllBox.draw(window, theme);
	dllBox.draw(window, theme);
	cllBox.draw(window, theme);
	staticArrayBox.draw(window, theme);
	dynamicArrayBox.draw(window, theme);
	window.display();
}

void Game::run()
{
	while (window.isOpen())
	{
		processEvents();
		update(timePerFrame);
		render();
	}
	saveFileTheme();
}