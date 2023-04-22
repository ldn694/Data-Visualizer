#pragma once

#include "DoublyLinkedList.h"
#include "Stage.h"

struct DoublyLinkedListStage : public Stage {
private:
	DoublyLinkedList ds;
	bool processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	DoublyLinkedListStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected);
	void run();
};