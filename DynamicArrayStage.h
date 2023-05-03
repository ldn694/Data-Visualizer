#pragma once

#include "DynamicArray.h"
#include "Stage.h"

struct DynamicArrayStage : public Stage {
private:
	DynamicArray ds;
	std::pair<bool, ColorTheme> processEvents();
	void update(sf::Time deltaT);
	void render();
public:
	DynamicArrayStage(sf::RenderWindow& window, double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, int numPointCircle = 4);
	ColorTheme run();
};
#pragma once
