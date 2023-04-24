#pragma once

#include "Queue.h"
#include "Stage.h"

struct QueueStage : public Stage {
private:
	Queue ds;
	bool processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	QueueStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, int numPointCircle = 30);
	void run();
};