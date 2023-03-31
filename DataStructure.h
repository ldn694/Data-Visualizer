#pragma once

#include <vector>
#include "Template.h"
#include "Graph.h"

enum AnimationType {
	AddNode, AddEdge, MoveNode, TranslateNode, MergeMoveNode,
	FillColorNode, OutlineColorNode, ValueColorNode,
	AddVariable, DeleteVariable,
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
		std::vector <std::string> variables;
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
		sf::Time time;
	};
	float speed;
	Graph defaultGraph, curGraph, mainGraph;
	std::vector <Frame> listFrame;
	std::deque <std::tuple<int, sf::Time, bool> > frameQueue;
	DataStructure(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor, sf::Color variableColor = RedColor,
		EdgeType edgeType = Undirected, sf::Font* font = nullptr);
	void resetAnimation();
	void setNodeColor(std::vector <Animation> &animationList, std::vector <int> nodes, ColorTheme theme, ColorType type);
	void addNode(std::vector <Animation>& animationList, int pos, int value, double x, double y);
	void deleteNode(std::vector <Animation>& animationList, int pos);
	void translateNode(std::vector <Animation>& animationList, std::vector <int> nodes, double dx, double dy);
	void moveNode(std::vector <Animation>& animationList, int pos, double x, double y);
	void mergeMoveNode(std::vector <Animation>& animationList);
	void addVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void deleteVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void addEdge(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorType type);
	void setEdgeColor(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorType type);
	void update(sf::Time deltaT);
	void updateAnimation(Graph& graph, Animation animation, sf::Time time = sf::seconds(0.f));
	void addAnimations(std::vector <Animation> animationList, sf::Time time);
	void animateFrame(int idFrame);
	void animateAllFrame();
	void updateFrameQueue(sf::Time deltaT);
	void draw(sf::RenderWindow& window);
};