#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"

const sf::Time timePerFrame = sf::seconds(1.f / 60.f);

sf::Font* Game::font(fontType id) {
	return &listFont[id];
}

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(1080, 720), "SFML Application", sf::Style::Close, settings), graph(20, 3, 4, WhiteColor, BlackColor, EdgeType::SinglyDirected)
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[fontType::Arial])) {
			assert(false);
		}
	}
	graph.setFont(font(fontType::Arial));
	graph.addNode(5, 185, 400, 200);
	graph.addNode(4, 69, 300, 300);
	graph.addNode(1, 50, 300, 100);
	graph.addNode(2, 70, 200, 150);
	graph.addNode(0, 200, 100, 100);
	graph.addNode(3, 18, 100, 300);
	graph.addNode(69, 180, 400, 150);
	graph.addEdge(0, 1, BlackColor);
	graph.addEdge(0, 3, BlackColor);
	graph.addEdge(0, 5, BlackColor);
	graph.addEdge(1, 2, BlackColor);
	graph.addEdge(2, 0, BlackColor);
	graph.addEdge(3, 0, RedColor);
	graph.addEdge(4, 1, GreenColor);
	graph.addEdge(5, 3, BlueColor);
	graph.addEdge(69, 1, BlackColor);
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
				if (event.mouseButton.button == sf::Mouse::Left) {
					graph.deleteNode(3);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					graph.deleteNode(0);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					graph.addNode(3, 18, 100, 300);
				}
				if (event.mouseButton.button == sf::Mouse::Right) {
					graph.addNode(0, 200, 100, 100);
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
	graph.draw(window);
	/*sf::Font tmpFont;
	tmpFont.loadFromFile("arial.ttf");
	sf::Text text;
	text.setFont(tmpFont);
	text.setString("DCMQ");
	text.setCharacterSize(10);
	text.setFillColor(RedColor);
	text.setPosition(400, 400);
	window.draw(text);*/
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