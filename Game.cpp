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
	//box = Box(300, 300, 400, 350, "WWW", font(fontType::Arial), 25, {CommandBoxNormal, CommandBoxSelected}, false, 0);*/
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
				ds.peek();
			}
			if (event.key.code == sf::Keyboard::I) {
				ds.setTheme(DarkTheme);
			}
			if (event.key.code == sf::Keyboard::O) {
				ds.setTheme(LightTheme);
			}
			if (26 <= event.key.code && event.key.code <= 35) { //0 -> 9
				ds.animateFrame(event.key.code - 26);
			}
			if (event.key.code == sf::Keyboard::R) {
				ds.animateAllFrame();
			}
		case sf::Event::MouseButtonPressed:
			if (box.isInside(event.mouseButton.x, event.mouseButton.y)) {
				box.toggleColorMode();
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
	//box.draw(window, LightTheme); 
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