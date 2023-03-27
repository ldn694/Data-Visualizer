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
	/*graph.addNode(1, 1, 100, 100, sf::seconds(0.3f));
	graph.addNode(2, 2, 300, 100, sf::seconds(0.3f));
	graph.addNode(3, 3, 200, 150, sf::seconds(0.3f));
	graph.addNode(4, 4, 100, 300, sf::seconds(0.3f));
	graph.addNode(5, 5, 300, 300, sf::seconds(0.3f));
	graph.addNode(6, 6, 400, 200, sf::seconds(0.3f));
	graph.addNode(69, 69, 400, 150, sf::seconds(0.3f));*/
	std::vector <std::tuple <int, int, double, double> > nodeList;
	nodeList.push_back({ 1, 1, 100, 100 });
	nodeList.push_back({ 2, 2, 300, 100 });
	nodeList.push_back({ 3, 3, 200, 150 });
	nodeList.push_back({ 4, 4, 100, 300 });
	nodeList.push_back({ 5, 5, 300, 300 });
	nodeList.push_back({ 6, 6, 400, 200 });
	nodeList.push_back({ 69, 69, 400, 150 });
	graph.addNodes(nodeList, sf::seconds(1.0f));
	/*graph.addEdge(1, 2, BlackColor, sf::seconds(1.0f));
	graph.addEdge(1, 4, BlackColor, sf::seconds(1.0f));
	graph.addEdge(1, 6, BlackColor, sf::seconds(1.0f));
	graph.addEdge(2, 3, BlackColor, sf::seconds(1.0f));
	graph.addEdge(3, 1, BlackColor, sf::seconds(1.0f));
	graph.addEdge(4, 1, RedColor, sf::seconds(1.0f));
	graph.addEdge(5, 2, GreenColor, sf::seconds(1.0f));
	graph.addEdge(6, 4, BlueColor, sf::seconds(1.0f));
	graph.addEdge(69, 2, BlackColor, sf::seconds(1.0f));*/
	std::vector <std::tuple<int, int, sf::Color> > edgeList;
	edgeList.push_back({ 1, 2, BlackColor });
	edgeList.push_back({1, 4, BlackColor});
	edgeList.push_back({ 1, 6, BlackColor });
	edgeList.push_back({ 2, 3, BlackColor });
	edgeList.push_back({ 3, 1, BlackColor });
	edgeList.push_back({4, 1, RedColor});
	edgeList.push_back({5, 2, GreenColor});
	edgeList.push_back({6, 4, BlueColor});
	edgeList.push_back({69, 2, BlackColor});
	graph.addEdges(edgeList, sf::seconds(1.0f));
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
			graph.stopAnimation();
			if (event.mouseButton.button == sf::Mouse::Left) {
				graph.deleteNode(4, sf::seconds(0.3f));
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				graph.deleteNode(1, sf::seconds(0.3f));
			}
			if (event.mouseButton.button == sf::Mouse::Middle) {
				graph.deleteNodes({ 2, 3, 5 }, sf::seconds(0.3f));
			}
			break;
		case sf::Event::MouseButtonReleased:
			graph.stopAnimation();
			if (event.mouseButton.button == sf::Mouse::Left) {
				graph.addNode(4, 4, 100, 300, sf::seconds(0.3f));
				std::vector <std::tuple<int, int, sf::Color> > edgeList;
				edgeList.push_back({ 4, 2, BlackColor });
				edgeList.push_back({4, 3, BlackColor});
				edgeList.push_back({4, 5, BlackColor});
				edgeList.push_back({6, 4, BlueColor});
				graph.addEdges(edgeList, sf::seconds(0.3f));
			}
			if (event.mouseButton.button == sf::Mouse::Right) {
				graph.addNode(1, 1, 100, 100, sf::seconds(0.3f));
			}
			if (event.mouseButton.button == sf::Mouse::Middle) {
				graph.addNode(1, 1, 100, 100, sf::seconds(0.3f));
				graph.addNode(2, 2, 300, 100, sf::seconds(0.3f));
				graph.addNode(3, 3, 200, 150, sf::seconds(0.3f));
				graph.addNode(5, 5, 300, 300, sf::seconds(0.3f));
			}
			break;
		case sf::Event::KeyPressed:
			graph.stopAnimation();
			if(event.key.code == sf::Keyboard::Tab) {
				break;
			}
			if (event.key.code == sf::Keyboard::S) {
				std::vector <std::tuple <int, double, double> > moveList;
				moveList.push_back({ 4, 50, 450 });
				moveList.push_back({ 6, 500, 500 });
				graph.moveNodes(moveList, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::W) {
				std::vector <std::tuple <int, double, double> > moveList;
				moveList.push_back({ 4, 150, 250 });
				moveList.push_back({ 6, 400, 200 });
				graph.moveNodes(moveList, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::R) {
				graph.setNodeFillColor(3, OrangeColor, sf::seconds(0.3f));
				graph.setNodeOutlineColor(3, OrangeColor, sf::seconds(0.3f));
				graph.setNodeValueColor(3, WhiteColor, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::T) {
				graph.setNodeFillColor(3, WhiteColor, sf::seconds(0.3f));
				graph.setNodeOutlineColor(3, OrangeColor, sf::seconds(0.3f));
				graph.setNodeValueColor(3, OrangeColor, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Y) {
				graph.setNodeFillColor(3, WhiteColor, sf::seconds(0.3f));
				graph.setNodeOutlineColor(3, BlackColor, sf::seconds(0.3f));
				graph.setNodeValueColor(3, BlackColor, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Q) {
				std::vector <std::tuple<int, int, sf::Color> > edgeList;
				edgeList.push_back({ 4, 3, OrangeColor });
				edgeList.push_back({ 4, 5, RedColor });
				graph.setEdgesColor(edgeList, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Delete) {
				std::vector <std::pair<int, int> > edgeList;
				edgeList.push_back({ 1, 2 });
				edgeList.push_back({ 3, 1 });
				graph.deleteEdges(edgeList, sf::seconds(1.0f));
				edgeList.clear();
				edgeList.push_back({ 4, 1 });
				edgeList.push_back({ 69, 2 });
				graph.deleteEdges(edgeList, sf::seconds(1.0f));
			}
			if (event.key.code == sf::Keyboard::U) {
				graph.stopAnimation();
				graph.switchEdge(4, 3, 69, sf::seconds(1.0f));
			}
			break;
		}
		
	}
}

void Game::update(sf::Time deltaT)
{
	graph.update(deltaT);
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