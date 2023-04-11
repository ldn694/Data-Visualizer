#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "StackStage.h"
#include "Template.h"

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings)
{
	box = Box(300, 500, 200, 300, { CommandBoxNormal }, "Stack",  font(fontType::Prototype), 50, NO_BORDER, 5);
	theme = LightTheme;
}

void Game::runStack() {
	StackStage st(window, 20, 5, 3, theme, SinglyDirected);
	st.run();
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
			if (box.isInside(event.mouseButton.x, event.mouseButton.y)) {
				runStack();
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
	box.draw(window, theme); 
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