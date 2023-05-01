#pragma once

#include <vector>
#include "Template.h"
#include "Graph.h"
#include "Box.h"

enum AnimationType {
	AddNode, AddEdge, AddCircularEdge,
	MoveNode, TranslateNode, MergeMoveNode, ValueNode,
	FillColorNode, OutlineColorNode, ValueColorNode, VariableColorNode,
	AddVariable, DeleteVariable,
	EdgeColor, CircularEdgeColor, SwitchEdge, SwitchCircularEdge,
	DeleteNode, DeleteEdge, DeleteCircularEdge, DoNothing
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
		std::vector <int> values;
	} work;
};

struct DataStructure {
	struct Frame {
		Graph graph;
		std::vector <Animation> nextStep;
		sf::Time time;
		int line;
		std::string announcement;
	};
	double speed;
	Graph defaultGraph, curGraph, mainGraph;
	std::vector <Frame> listFrame;
	std::deque <std::tuple<int, sf::Time, sf::Time, bool> > frameQueue;
	bool isAnimating;
	ColorTheme theme;
	std::vector <std::vector <std::vector <std::string> > > codes;
	std::vector <std::vector <std::vector <sf::Text> > > codeText;
	double xAnnouncement, yAnnouncement, widthAnnouncement, heightAnnouncement;
	sf::Font* announcementFont;
	double xError, yError, widthError, heightError;
	std::string error;
	sf::Font* errorFont;
	sf::Time errorTime;
	std::vector <int> numMode;
	std::vector <std::vector <int> > numStep;
	int numOperation, curStep = 0, curMode = 0, curOperation = 0;
	int curFrame = 0;
	sf::RectangleShape codeBoard;
	DataStructure(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, int numPointCircle = 30,
		std::vector < std::vector <std::vector <std::string> > > codes = {}, double x = 0, double y = 0, double width = 0, double height = 0, sf::Font* codeFont = nullptr,
		double xAnnouncement = 0, double yAnnouncement = 0, double widthAnnouncement = 0, double heightAnnouncement = 0, sf::Font *announcementFont = nullptr,
		double xError = 0, double yError = 0, double widthError = 0, double heightError = 0, sf::Font* errorFont = nullptr);
	void resetAnimation();
	void setError(bool val, std::string newError = "");
	void setTheme(ColorTheme theme);
	void setSpeed(double newSpeed);
	void setNodeColor(std::vector <Animation> &animationList, std::vector <int> nodes, ColorTheme theme, ColorNodeType type);
	void setNodeColor(std::vector <Animation>& animationList, std::vector <int> nodes, ColorTheme theme, std::vector <ColorNodeType> type);
	void addNode(std::vector <Animation>& animationList, int pos, int value, double x, double y);
	void deleteNode(std::vector <Animation>& animationList, int pos);
	void deleteNode(std::vector <Animation>& animationList, std::vector <int> pos);
	void translateNode(std::vector <Animation>& animationList, std::vector <int> nodes, double dx, double dy);
	void moveNode(std::vector <Animation>& animationList, int pos, double x, double y);
	void mergeMoveNode(std::vector <Animation>& animationList);
	void setNodeValue(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <int> values);
	void addVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void deleteVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList);
	void addEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type);
	void addEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type);
	void addCircularEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type);
	void deleteEdge(std::vector <Animation>& animationList, std::vector < std::pair <int, int> > edges);
	void deleteCircularEdge(std::vector <Animation>& animationList, std::vector < std::pair <int, int> > edges);
	void setEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type);
	void setEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type);
	void setCircularEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type);
	void setCircularEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type);
	void switchEdge(std::vector <Animation>& animationList, std::vector <std::tuple <int, int, int> > edgeList);
	void switchCircularEdge(std::vector <Animation>& animationList, std::vector <std::tuple <int, int, int> > edgeList);
	void doNothing(std::vector <Animation>& animationList);
	void setCurOperation(int val);
	void setCurMode(int val);
	void update(sf::Time deltaT);
	void updateAnimation(Graph& graph, Animation animation, sf::Time time = sf::seconds(0.f));
	void addAnimations(std::vector <Animation> animationList, sf::Time time, int line, std::string announcement = "");
	void setIsAnimating(bool val);
	void animateFrame(int idFrame);
	void setFrame(int idFrame);
	void animateAllFrame();
	void updateFrameQueue(sf::Time deltaT);
	void clearFrameQueue();
	void draw(sf::RenderWindow& window);
};