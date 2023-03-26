#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "Template.h"

sf::Font* Game::font(fontType id) {
	return &listFont[id];
}

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(1080, 720), "SFML Application", sf::Style::Close, settings), graph(20, 3, 4, WhiteColor, BlackColor, BlackColor, EdgeType::SinglyDirected)
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[fontType::Arial])) {
			assert(false);
		}
	}
	graph.setFont(font(fontType::Arial));
	graph.addNode(0, 0, 100, 100);
	graph.addNode(1, 1, 300, 100);
	graph.addNode(2, 2, 200, 150);
	graph.addNode(3, 3, 100, 300);
	graph.addNode(4, 4, 300, 300);
	graph.addNode(5, 5, 400, 200);
	graph.addNode(69, 69, 400, 150);
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
			if (event.mouseButton.button == sf::Mouse::Middle) {
				graph.deleteNodes({ 1, 2, 4 });
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left) {
				graph.addNode(3, 3, 100, 300);
				graph.addEdge(3, 1, BlackColor);
				graph.addEdge(3, 2, BlackColor);
				graph.addEdge(3, 4, BlackColor);
				graph.addEdge(5, 3, BlueColor);
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				graph.addNode(0, 0, 100, 100);
			}
			if (event.mouseButton.button == sf::Mouse::Middle) {
				graph.addNode(0, 0, 100, 100);
				graph.addNode(1, 1, 300, 100);
				graph.addNode(2, 2, 200, 150);
				graph.addNode(4, 4, 300, 300);
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::W) {
				graph.moveNode(3, 150, 250);
				graph.moveNode(5, 700, 700);
			}
			if (event.key.code == sf::Keyboard::S) {
				graph.moveNode(3, 50, 450);
				graph.moveNode(5, 400, 200);
			}
			if (event.key.code == sf::Keyboard::R) {
				graph.updateNodeValueColor(2, WhiteColor);
				graph.updateNodeFillColor(2, OrangeColor);
				graph.updateNodeOutlineColor(2, OrangeColor);
			}
			if (event.key.code == sf::Keyboard::T) {
				graph.updateNodeValueColor(2, OrangeColor);
				graph.updateNodeFillColor(2, WhiteColor);
				graph.updateNodeOutlineColor(2, OrangeColor);
			}
			if (event.key.code == sf::Keyboard::Y) {
				graph.updateNodeValueColor(2, BlackColor);
				graph.updateNodeFillColor(2, WhiteColor);
				graph.updateNodeOutlineColor(2, BlackColor);
			}
			if (event.key.code == sf::Keyboard::Q) {
				graph.updateEdgeColor(3, 2, OrangeColor);
				graph.updateEdgeColor(3, 4, RedColor);
			}
			if (event.key.code == sf::Keyboard::Delete) {
				std::cout << "Pressed Delete\n";
				graph.deleteEdge(3, 2);
			}
			break;
		}
		
	}
}

void Game::update(sf::Time deltaT)
{
	graph.updateEdgeDelete(deltaT);
	graph.updateNodeDelete(deltaT);
	graph.updateNodeAnimation(deltaT);
}

void Game::render()
{
	window.clear(WhiteColor);
	graph.draw(window);
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