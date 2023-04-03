#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <deque>
#include "Template.h"
#include "Node.h"

struct Graph {
private: 
	struct EdgeInfo {
		int v;
		sf::Color color;
		bool display;
		int priority;
		EdgeInfo(int v = 0, sf::Color color = BlackColor, bool display = true, int priority = 0);
	};
	struct cmpEdgeInfo {
		bool operator() (const EdgeInfo& a, const EdgeInfo& b) const;
	};
	struct FakeNode {
		int u, fakeID;
		FakeNode(int u, int fakeID = -1);
	};
	struct NodeAnimation {
		std::vector <FakeNode> nodes;
		sf::Time totalTime, remainTime;
		NodeAnimation(std::vector <FakeNode> nodes, sf::Time totalTime, sf::Time remainTime);
	};
	struct FakeEdge {
		int u, v, fakeIDu, fakeIDv, fakeIDtmp;
		FakeEdge(int u, int v, int fakeIDu, int fakeIDv = -1, int fakeIDtmp = -1);
	};
	struct EdgeAnimation {
		std::vector <FakeEdge> edges;
		sf::Time totalTime, remainTime;
		EdgeAnimation(std::vector <FakeEdge> edges, sf::Time totalTime, sf::Time remainTime);
	};
	struct FakeEdgeSwitch {
		int u, v, newv, fakeID;
		FakeEdgeSwitch(int u, int v, int newv, int fakeID);
	};
	struct EdgeSwitchAnimation {
		std::vector <FakeEdgeSwitch> edges;
		sf::Time totalTime, remainTime;
		EdgeSwitchAnimation(std::vector <FakeEdgeSwitch> edges, sf::Time totalTime, sf::Time remainTime);
	};
	std::set <int> fakeIDList;
	std::map <int, Node> listNode;
	std::map <int, std::set <EdgeInfo, cmpEdgeInfo > > adj;
	std::deque <NodeAnimation> nodeAddQueue, nodeDeleteQueue, nodeMoveQueue, nodeFillColorQueue, nodeOutlineColorQueue, nodeValueColorQueue;
	std::deque <EdgeAnimation> edgeAddQueue, edgeDeleteQueue, edgeColorQueue;
	std::deque <EdgeSwitchAnimation> edgeSwitchQueue;
	Node defaultNode;
	double lineThickness;
	EdgeType edgeType;
	auto findV(int u, int v);
	void toggleEdgeDisplay(int u, int v, bool display);
	int getFakeID();
	void toggleNodeDisplay(int u, bool display);
	void toggleEdgePriority(int u, int v, int priority);
public:
	Graph(double radius = 0, double outlineSize = 0, double _lineThickness = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor, sf::Color variableColor = RedColor,
		EdgeType _edgeType = Undirected, sf::Font* font = nullptr);
	Node getDefaultNode();
	void setFont(sf::Font* newFont);
	void draw(sf::RenderWindow& window);
	void addNode(int pos, int value, double x, double y);
	void addNode(int pos, int value, double x, double y, sf::Time time);
	void addNodes(std::vector <std::tuple <int, int, double, double> > nodes);
	void addNodes(std::vector <std::tuple <int, int, double, double> > nodes, sf::Time time);
	void updateNodeAdd(sf::Time deltaT);
	void deleteNode(int pos);
	void deleteNode(int pos, sf::Time time);
	void deleteNodes(std::vector <int> nodes);
	void deleteNodes(std::vector <int> nodes, sf::Time time);
	void updateNodeDelete(sf::Time deltaT);
	void moveNode(int pos, double x, double y);
	void moveNode(int pos, double x, double y, sf::Time time);
	void moveNodes(std::vector <std::tuple<int, double, double> > nodes);
	void moveNodes(std::vector <std::tuple<int, double, double> > nodes, sf::Time time);
	void translateNodes(std::vector <int> nodes, double dx, double dy);
	void translateNodes(std::vector <int> nodes, double dx, double dy, sf::Time time);
	void mergeNodeMove();
	void updateNodeMove(sf::Time deltaT);
	void addNodeVariable(int u, std::string variable);
	void deleteNodeVariable(int u, std::string variable);
	void setNodeFillColor(int pos, sf::Color color);
	void setNodeFillColor(int pos, sf::Color color, sf::Time time);
	void setNodesFillColor(std::vector <std::pair<int, sf::Color>> nodes);
	void setNodesFillColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time);
	void updateNodeFillColor(sf::Time deltaT);
	void setNodeOutlineColor(int pos, sf::Color color);
	void setNodeOutlineColor(int pos, sf::Color color, sf::Time time);
	void setNodesOutlineColor(std::vector <std::pair<int, sf::Color>> nodes);
	void setNodesOutlineColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time);
	void updateNodeOutlineColor(sf::Time deltaT);
	void setNodeValueColor(int pos, sf::Color color);
	void setNodeValueColor(int pos, sf::Color color, sf::Time time);
	void setNodesValueColor(std::vector <std::pair<int, sf::Color>> nodes);
	void setNodesValueColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time);
	void updateNodeValueColor(sf::Time deltaT);
	void setNodeVariableColor(int pos, sf::Color color);
	void setNodesVariableColor(std::vector <std::pair<int, sf::Color>> nodes);
	void addEdge(int u, int v, sf::Color color);
	void addEdge(int u, int v, sf::Color color, sf::Time time);
	void addEdges(std::vector <std::tuple <int, int, sf::Color>> edges);
	void addEdges(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time);
	void updateEdgeAdd(sf::Time time);
	void deleteEdge(int u, int v);
	void deleteEdge(int u, int v, sf::Time time);
	void deleteEdges(std::vector <std::pair<int, int>> edges);
	void deleteEdges(std::vector <std::pair<int, int>> edges, sf::Time time);
	void updateEdgeDelete(sf::Time deltaT);
	void switchEdge(int u, int v, int newv);
	void switchEdges(std::vector <std::tuple<int, int, int>> edgesSwitch);
	void switchEdge(int u, int v, int newv, sf::Time time);
	void switchEdges(std::vector <std::tuple<int, int, int>> edgesSwitch, sf::Time time);
	void updateEdgeSwitch(sf::Time deltaT);
	void setEdgeColor(int u, int v, sf::Color color);
	void setEdgeColor(int u, int v, sf::Color color, sf::Time time);
	void setEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges);
	void setEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time);
	void updateEdgeColor(sf::Time deltaT);
	void setTheme(ColorTheme preTheme, ColorTheme curTheme);
	void update(sf::Time deltaT);
	void stopAnimation();
};