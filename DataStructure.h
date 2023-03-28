#pragma once
#include <vector>
#include "Template.h"
#include "Graph.h"

enum AnimationType {
	AddNode, AddEdge, MoveNode,
	FillColorNode, OutlineColorNode, ValueColorNode,
	EdgeColor, SwitchEdge,
	DeleteNode, DeleteEdge
};

struct Animation {
	AnimationType type;
	struct Element {
		std::vector <int> nodes;
		std::vector <std::pair<int, int>> edges;
	} element;
	struct Work {
		std::vector <std::tuple<int, double, double> > nodeInfos;
		std::vector <std::pair<double, double> > coordinates;
		std::vector <int> goalNode;
		std::vector <sf::Color> colors;
	} work;
};

struct DataStructure {

	struct Frame {
		Graph graph;
		std::vector <Animation> nextStep;
	};
	Graph defaultGraph, curGraph, mainGraph;
	std::vector <Frame> listFrame;
	DataStructure(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor,
		EdgeType edgeType = Undirected, sf::Font* font = nullptr);
	void resetAnimation();
	void update(sf::Time deltaT);
	void updateAnimation(Graph& graph, Animation animation, sf::Time time = sf::seconds(0.f));
	void addAnimations(std::vector <Animation> animationList);
	void animateFrame(int idFrame, sf::Time time);
	void draw(sf::RenderWindow& window);
};