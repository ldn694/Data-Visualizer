#pragma once

#include "Stack.h"
#include "Stage.h"

struct StackStage : public Stage {
private:
	Stack ds;
	bool processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	StackStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, int numPointCircle = 30);
	void run();
};