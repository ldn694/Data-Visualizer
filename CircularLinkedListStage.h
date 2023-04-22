#pragma once

#include "CircularLinkedList.h"
#include "Stage.h"

struct CircularLinkedListStage : public Stage {
private:
	CircularLinkedList ds;
	bool processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	CircularLinkedListStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected);
	void run();
};