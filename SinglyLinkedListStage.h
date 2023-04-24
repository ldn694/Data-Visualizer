#pragma once

#include "SinglyLinkedList.h"
#include "Stage.h"

struct SinglyLinkedListStage : public Stage {
private:
	SinglyLinkedList ds;
	bool processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	SinglyLinkedListStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, int numPointCircle = 30);
	void run();
};