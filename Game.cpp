#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "StackStage.h"
#include "QueueStage.h"
#include "Template.h"

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings)
{
	stackBox = Box(300, 500, 200, 300, { CommandBoxNormal }, "Stack", font(fontType::Prototype), 50, NO_BORDER, 5);
	queueBox = Box(600, 500, 200, 300, { CommandBoxNormal }, "Queue", font(fontType::Prototype), 50, NO_BORDER, 5);
	theme = LightTheme;
}

void Game::runStack() {
	StackStage stack(window, 20, 5, 3, theme, DoublyDirected);
	stack.run();
}

void Game::runQueue() {
	QueueStage queue(window, 20, 5, 3, theme, SinglyDirected);
	queue.run();
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