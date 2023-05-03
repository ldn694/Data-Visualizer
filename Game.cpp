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

Game::Game(sf::ContextSettings settings)
	: window(sf::VideoMode(WIDTH_RES, HEIGHT_RES), "Data Visualizer", sf::Style::Close, settings)
{
	window.setFramerateLimit(60);
	stackBox = Box(100, 500, 200, 300, { CommandBoxNormal }, "Stack", font(fontType::Prototype), 50, NO_BORDER, 5);
	queueBox = Box(400, 500, 200, 300, { CommandBoxNormal }, "Queue", font(fontType::Prototype), 50, NO_BORDER, 5);
	sllBox = Box(700, 500, 200, 300, { CommandBoxNormal }, "SLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	dllBox = Box(1000, 500, 200, 300, { CommandBoxNormal }, "DLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	cllBox = Box(1300, 500, 200, 300, { CommandBoxNormal }, "CLL", font(fontType::Prototype), 50, NO_BORDER, 5);
	staticArrayBox = Box(400, 100, 200, 300, { CommandBoxNormal }, "Static\nArray", font(fontType::Prototype), 50, NO_BORDER, 5);
	dynamicArrayBox = Box(1000, 100, 200, 300, { CommandBoxNormal }, "Dynamic\n  Array", font(fontType::Prototype), 50, NO_BORDER, 5);
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

void Game::runDynamicArray() {
	DynamicArrayStage dynamicArray(window, 20 * sqrt(2), 3, 4, theme, SinglyDirected, 4);
	dynamicArray.run();
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
	dynamicArrayBox.draw(window, theme);
	window.display();
}

std::string ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string fileName = converter.to_bytes(std::wstring(buffer).substr(0, pos));
	return fileName;
}

void Game::run()
{
	//std::string defaultAddress = ExePath();
	//std::cout << defaultAddress << "\n";
	while (window.isOpen())
	{
		/*std::cout << ("cd " + defaultAddress).c_str() << "\n";
		system(("cd " + defaultAddress).c_str());
		system("cd");
		std::cout << "\n";*/
		processEvents();
		update(timePerFrame);
		render();
	}
}