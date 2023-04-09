#pragma once

#include <vector>
#include "Template.h"
#include "Graph.h"

enum AnimationType {
	AddNode, AddEdge, MoveNode, TranslateNode, MergeMoveNode,
	FillColorNode, OutlineColorNode, ValueColorNode, VariableColorNode,
	AddVariable, DeleteVariable,
	EdgeColor, SwitchEdge,
	DeleteNode, DeleteEdge, DoNothing
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
		int line;
	};
	float speed;
	Graph defaultGraph, curGraph, mainGraph;
	std::vector <Frame> listFrame;
	std::deque <std::tuple<int, sf::Time, sf::Time, bool> > frameQueue;
	bool isAnimating;
	ColorTheme theme;
	std::vector <std::vector <std::string> > codes;
	std::vector <std::vector <sf::Text> > codeText;
	std::vector <int> numStep;
	int numOperation, curStep = 0, curOperation = 0;
	int curFrame;
	sf::RectangleShape codeBoard;
	DataStructure(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, 
		std::vector <std::vector <std::string> > codes = {}, double x = 0, double y = 0, double width = 0, double height = 0, sf::Font* codeFont = nullptr);
	void resetAnimation();
	void setTheme(ColorTheme theme);
	void setNodeColor(std::vector <Animation> &animationList, std::vector <int> nodes, ColorTheme theme, ColorNodeType type);
	void addNode(std::vector <Animation>& animationList, int pos, int value, double x, double y);
	void deleteNode(std::vector <Animation>& animationList, int pos);
	void translateNode(std::vector <Animation>& animationList, std::vector <int> nodes, double dx, double dy);
	void moveNode(std::vector <Animation>& animationList, int pos, double x, double y);
	void mergeMoveNode(std::vector <Animation>& animationList);
	void addVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void deleteVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void addEdge(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorNodeType type);
	void setEdgeColor(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorNodeType type);
	void doNothing(std::vector <Animation>& animationList);
	void setCurOperation(int val);
	void update(sf::Time deltaT);
	void updateAnimation(Graph& graph, Animation animation, sf::Time time = sf::seconds(0.f));
	void addAnimations(std::vector <Animation> animationList, sf::Time time, int line);
	void setIsAnimating(bool val);
	void animateFrame(int idFrame);
	void setFrame(int idFrame);
	void animateAllFrame();
	void updateFrameQueue(sf::Time deltaT);
	void clearFrameQueue();
	void draw(sf::RenderWindow& window);
};