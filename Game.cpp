#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "Template.h"

sf::Font* Game::font(fontType id) {
	return &listFont[id];
}

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings)
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[fontType::Arial])) {
			assert(false);
		}
	}
	ds = Stack(20, 3, 4, LightTheme, EdgeType::SinglyDirected, font(fontType::Arial));
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
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Q) {
				ds.createRandom();
			}
			if (event.key.code == sf::Keyboard::T) {
				ds.push(69);
			}
			if (event.key.code == sf::Keyboard::Y) {
				ds.pop();
			}
			if (event.key.code == sf::Keyboard::U) {
				//ds.peek();
			}
			if (event.key.code == sf::Keyboard::Num1) {
				ds.animateFrame(1);
			}
			if (event.key.code == sf::Keyboard::Num2) {
				ds.animateFrame(2);
			}
			if (event.key.code == sf::Keyboard::Num3) {
				ds.animateFrame(3);
			}
			if (event.key.code == sf::Keyboard::Num4) {
				ds.animateFrame(4);
			}
			if (event.key.code == sf::Keyboard::Num5) {
				ds.animateFrame(5);
			}
			if (event.key.code == sf::Keyboard::Num6) {
				ds.animateFrame(6);
			}
			if (event.key.code == sf::Keyboard::Num7) {
				ds.animateFrame(7);
			}
			if (event.key.code == sf::Keyboard::R) {
				ds.animateAllFrame();
			}
		}
	}
}

void Game::update(sf::Time deltaT)
{
	ds.update(deltaT);
}

void Game::render()
{
	window.clear(WhiteColor);
	ds.draw(window);
	window.display();
}

void Game::run()
{
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