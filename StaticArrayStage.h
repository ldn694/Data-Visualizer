#pragma once

#include "StaticArray.h"
#include "Stage.h"

struct StaticArrayStage : public Stage {
private:
	StaticArray ds;
	std::pair<bool, ColorTheme> processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	StaticArrayStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, int numPointCircle = 4);
	ColorTheme run();
};
