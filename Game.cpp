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
#include "Template.h"

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings)
{
	stackBox = Box(100, 500, 200, 300, { CommandBoxNormal }, "Stack", font(fontType::Prototype), 50, NO_BORDER, 5);
	queueBox = Box(400, 500, 200, 300, { CommandBoxNormal }, "Queue", font(fontType::Prototype), 50, NO_BORDER, 5);
	sllBox = Box(700, 500, 200, 300, { CommandBoxNormal }, "SLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	dllBox = Box(1000, 500, 200, 300, { CommandBoxNormal }, "DLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	cllBox = Box(1300, 500, 200, 300, { CommandBoxNormal }, "CLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	staticArrayBox = Box(400, 100, 200, 300, { CommandBoxNormal }, "Static\nArray", font(fontType::Prototype), 50, NO_BORDER, 5);
	theme = LightTheme;
}

void Game::runStack() {
	StackStage stack(window, 20, 5, 4, theme, SinglyDirected, 30);
	stack.run();
}

void Game::runQueue() {
	QueueStage queue(window, 20, 5, 4, theme, SinglyDirected, 30);
	queue.run();
}

void Game::runSLL() {
	SinglyLinkedListStage sll(window, 20, 5, 4, theme, SinglyDirected, 30);
	sll.run();
}

void Game::runDLL() {
	DoublyLinkedListStage dll(window, 20, 5, 4, theme, DoublyDirected, 30);
	dll.run();
}

void Game::runCLL() {
	CircularLinkedListStage cll(window, 20, 5, 4, theme, SinglyDirected, 30);
	cll.run();
}

void Game::runStaticArray() {
	StaticArrayStage staticArray(window, 20 * sqrt(2), 3, 4, theme, SinglyDirected, 4);
	staticArray.run();
}

void Game::processEvents(sf::Clock& mClock)
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
				mClock.restart();
			}
			if (queueBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runQueue();
				mClock.restart();
			}
			if (sllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runSLL();
				mClock.restart();
			}
			if (dllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runDLL();
				mClock.restart();
			}
			if (cllBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runCLL();
				mClock.restart();
			}
			if (staticArrayBox.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runStaticArray();
				mClock.restart();
			}
			break;
		}
	}
}

void Game::update(sf::Time deltaT)
{
	
}

void Game::render()
{
	window.clear(WhiteColor);
	stackBox.draw(window, theme); 
	queueBox.draw(window, theme);
	sllBox.draw(window, theme);
	dllBox.draw(window, theme);
	cllBox.draw(window, theme);
	staticArrayBox.draw(window, theme);
	window.display();
}

void Game::run()
{
	sf::Clock mClock;
	sf::Time timePool = sf::Time::Zero;
	while (window.isOpen())
	{
		timePool += mClock.restart();
		while (timePool >= timePerFrame) {
			processEvents(mClock);
			timePool -= timePerFrame;
			update(timePerFrame);
			render();
		}
	}
}