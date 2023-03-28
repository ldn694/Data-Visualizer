#include <SFML/Graphics.hpp>
#include <iostream>
#include <cassert>
#include "Game.h"
#include "Template.h"

sf::Font* Game::font(fontType id) {
	return &listFont[id];
}

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(1080, 720), "Data Visualizer", sf::Style::Close, settings)
{
	listFont.resize(numFont);
	for (int i = 0; i < numFont; i++) {
		if (!listFont[i].loadFromFile(fontName[fontType::Arial])) {
			assert(false);
		}
	}
	ds = DataStructure(20, 3, 4, WhiteColor, BlackColor, BlackColor, EdgeType::SinglyDirected, font(fontType::Arial));
	std::vector <Animation> animationList;
	Animation tmp;
	//-----------------
	tmp.type = AddNode;
	tmp.element.nodes = { 1, 2, 3, 4, 5 };
	tmp.work.nodeInfos = { {12, 100, 100}, {69, 200, 100}, {185, 150, 150}, {12, 100, 300}, {15, 150, 300} };
	animationList.push_back(tmp);
	tmp.type = AddEdge;
	tmp.element.edges = { {1, 2}, {1, 3}, {2, 4} , {1, 4} , {3, 5} };
	tmp.work.colors = { BlackColor, GreenColor, BlueColor, BlackColor, OrangeColor};
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = EdgeColor;
	tmp.element.edges = { {3, 5}, {1, 4} };
	tmp.work.colors = { BlackColor, OrangeColor };
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = SwitchEdge;
	tmp.element.edges = { {3, 5}, {1, 4} };
	tmp.work.goalNode = {4, 5};
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = DeleteEdge;
	tmp.element.edges = { {3, 4}, {1, 5} };
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = FillColorNode;
	tmp.element.nodes = { 2, 4 };
	tmp.work.colors = { OrangeColor, WhiteColor };
	animationList.push_back(tmp);
	tmp.type = OutlineColorNode;
	tmp.work.colors = { OrangeColor, OrangeColor };
	animationList.push_back(tmp);
	tmp.type = ValueColorNode;
	tmp.work.colors = { WhiteColor, OrangeColor };
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = MoveNode;
	tmp.element.nodes = { 1, 2, 3 };
	tmp.work.coordinates = { {150, 100}, {250, 100}, {200, 150} };
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
	//-----------------
	animationList.clear();
	tmp.type = DeleteNode;
	tmp.element.nodes = { 3, 4 };
	animationList.push_back(tmp);
	ds.addAnimations(animationList);
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
			if (event.key.code == sf::Keyboard::Num1) {
				ds.animateFrame(1, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num2) {
				ds.animateFrame(2, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num3) {
				ds.animateFrame(3, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num4) {
				ds.animateFrame(4, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num5) {
				ds.animateFrame(5, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num6) {
				ds.animateFrame(6, sf::seconds(0.3f));
			}
			if (event.key.code == sf::Keyboard::Num7) {
				ds.animateFrame(7, sf::seconds(0.3f));
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