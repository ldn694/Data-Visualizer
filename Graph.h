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
		sf::Time totalTime, remainTime;
		bool adding; //adding = 0: erasing edge; adding = 1: adding edge
		EdgeInfo(int _v = 0, sf::Color color = BlackColor, bool adding = ERASE_EDGE, sf::Time totalTime = sf::seconds(0.f), sf::Time remainTime = sf::seconds(0.f));
	};
	struct EdgeSwitchInfo {
		int start, goal;
		sf::Color color;
		sf::Time totalTime, remainTime;
		EdgeSwitchInfo(int start, int goal, sf::Color color, sf::Time totalTime, sf::Time remainTime);
	};
	struct NodeDeleteInfo {
		std::vector <int> nodes;
		sf::Time totalTime, remainTime;
		NodeDeleteInfo(std::vector<int> _nodes, sf::Time _totalTime = sf::seconds(0.f), sf::Time _remainTime = sf::seconds(0.f));
	};
	struct EdgeDeleteInfo {
		std::vector <std::pair <int, int> > edges;
		sf::Time totalTime, remainTime;
		EdgeDeleteInfo(std::vector<std::pair <int, int> > _edges = {{0, 0}}, sf::Time _totalTime = sf::seconds(0.f), sf::Time _remainTime = sf::seconds(0.f));
	};
	struct cmp {
		bool operator() (const EdgeInfo& a, const EdgeInfo& b) const;
	};
	std::map <int, Node> listNode;
	std::map <int, std::set <EdgeInfo, cmp > > adj, tmpAdj;
	std::deque <NodeDeleteInfo> nodeDeleteQueue;
	std::deque <EdgeDeleteInfo> edgeDeleteQueue;
	Node defaultNode;
	double lineThickness;
	EdgeType edgeType;
public:
	Graph(double radius = 0, double outlineSize = 0, double _lineThickness = 0,
		sf::Color fillColor = WhiteColor, sf::Color outlineColor = BlackColor, sf::Color valueColor = BlackColor, 
		EdgeType _edgeType = Undirected, sf::Font* font = nullptr);
	void setFont(sf::Font* newFont);
	void draw(sf::RenderWindow& window);
	void addNode(int pos, int value, double x, double y);
	void addNode(int pos, int value, double x, double y, sf::Time time);
	void deleteNode(int pos);
	void deleteNode(int pos, sf::Time time);
	void deleteNodes(std::vector <int> nodes);
	void deleteNodes(std::vector <int> nodes, sf::Time time);
	void moveNode(int pos, double x, double y);
	void moveNode(int pos, double x, double y, sf::Time time);
	void updateNodeFillColor(int pos, sf::Color color);
	void updateNodeFillColor(int pos, sf::Color color, sf::Time time);
	void updateNodeOutlineColor(int pos, sf::Color color);
	void updateNodeOutlineColor(int pos, sf::Color color, sf::Time time);
	void updateNodeValueColor(int pos, sf::Color color);
	void updateNodeValueColor(int pos, sf::Color color, sf::Time time);
	void updateNodeAnimation(sf::Time deltaT);
	void updateNodeDelete(sf::Time deltaT);
	void addEdge(int u, int v, sf::Color lineColor);
	void addEdge(int u, int v, sf::Color lineColor, sf::Time time);
	void addTmpEdge(int u, int v, sf::Color lineColor, sf::Time time);
	void deleteEdge(int u, int v);
	void deleteEdge(int u, int v, sf::Time time);
	void deleteEdges(std::vector <std::pair<int, int>> edges);
	void deleteEdges(std::vector <std::pair<int, int>> edges, sf::Time time);
	void updateEdgeColor(int u, int v, sf::Color lineColor);
	void updateEdgeColor(int u, int v, sf::Color lineColor, sf::Time time);
	void updateEdgeDelete(sf::Time deltaT);
};