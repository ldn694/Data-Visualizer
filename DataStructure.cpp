#include <vector>
#include <cassert>
#include <iostream>
#include "Template.h"
#include "Graph.h"
#include "DataStructure.h"

DataStructure::DataStructure(double radius, double outlineSize, double lineThickness,
	sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor,
	EdgeType idEdgeType, sf::Font* font) : 
	defaultGraph(Graph(radius, outlineSize, lineThickness, fillColor, outlineColor, valueColor, idEdgeType, font)) 
{
	mainGraph = defaultGraph;
	curGraph = defaultGraph;
	listFrame.push_back({ defaultGraph, {} });
}

void DataStructure::resetAnimation() {
	curGraph = mainGraph;
	listFrame.clear();
	listFrame.push_back({ mainGraph, {} });
}

bool cmpAnimation(const Animation& a, const Animation& b) {
	return a.type < b.type;
}

void DataStructure::updateAnimation(Graph& graph, Animation animation, sf::Time time) {
	if (animation.type == AddNode) {
		if (animation.element.nodes.size() != animation.work.nodeInfos.size()) {
			assert(false);
		}
		std::vector <std::tuple <int, int, double, double> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			auto& info = animation.work.nodeInfos[i];
			int value = std::get<0>(info);
			double x = std::get<1>(info), y = std::get<2>(info);
			nodeList.push_back({ u, value, x, y });
		}
		if (time < epsilonTime) {
			graph.addNodes(nodeList);
		}
		else {
			graph.addNodes(nodeList, time);
		}
	}
	if (animation.type == DeleteNode) {
		if (time < epsilonTime) {
			graph.deleteNodes(animation.element.nodes);
		}
		else {
			graph.deleteNodes(animation.element.nodes, time);
		}
	}
	if (animation.type == MoveNode) {
		if (animation.element.nodes.size() != animation.work.coordinates.size()) {
			assert(false);
		}
		std::vector <std::tuple <int, double, double> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			auto& info = animation.work.coordinates[i];
			double x = info.first, y = info.second;
			nodeList.push_back({ u, x, y });
		}
		if (time < epsilonTime) {
			graph.moveNodes(nodeList);
		}
		else {
			graph.moveNodes(nodeList, time);
		}
	}
	if (animation.type == FillColorNode) {
		if (animation.element.nodes.size() != animation.work.colors.size()) {
			assert(false);
		}
		std::vector <std::pair <int, sf::Color> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			sf::Color color = animation.work.colors[i];
			nodeList.push_back({ u, color });
		}
		if (time < epsilonTime) {
			graph.setNodesFillColor(nodeList);
		}
		else {
			graph.setNodesFillColor(nodeList, time);
		}
	}
	if (animation.type == OutlineColorNode) {
		if (animation.element.nodes.size() != animation.work.colors.size()) {
			assert(false);
		}
		std::vector <std::pair <int, sf::Color> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			sf::Color color = animation.work.colors[i];
			nodeList.push_back({ u, color });
		}
		if (time < epsilonTime) {
			graph.setNodesOutlineColor(nodeList);
		}
		else {
			graph.setNodesOutlineColor(nodeList, time);
		}
	}
	if (animation.type == ValueColorNode) {
		if (animation.element.nodes.size() != animation.work.colors.size()) {
			assert(false);
		}
		std::vector <std::pair <int, sf::Color> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			sf::Color color = animation.work.colors[i];
			nodeList.push_back({ u, color });
		}
		if (time < epsilonTime) {
			graph.setNodesValueColor(nodeList);
		}
		else {
			graph.setNodesValueColor(nodeList, time);
		}
	}
	if (animation.type == AddEdge) {
		if (animation.element.edges.size() != animation.work.colors.size()) {
			assert(false);
		}
		std::vector <std::tuple <int, int, sf::Color> > edgeList;
		for (int i = 0; i < (int)animation.element.edges.size(); i++) {
			auto e = animation.element.edges[i];
			int u = e.first, v = e.second;
			sf::Color color = animation.work.colors[i];
			edgeList.push_back({ u, v, color });
		}
		if (time < epsilonTime) {
			graph.addEdges(edgeList);
		}
		else {
			graph.addEdges(edgeList, time);
		}
	}
	if (animation.type == DeleteEdge) {
		std::vector <std::pair <int, int> > edgeList;
		for (int i = 0; i < (int)animation.element.edges.size(); i++) {
			auto e = animation.element.edges[i];
			int u = e.first, v = e.second;
			edgeList.push_back({ u, v });
		}
		if (time < epsilonTime) {
			graph.deleteEdges(edgeList);
		}
		else {
			graph.deleteEdges(edgeList, time);
		}
	}
	if (animation.type == SwitchEdge) {
		std::vector <std::tuple <int, int, int> > edgeSwitchList;
		if (animation.element.edges.size() != animation.work.goalNode.size()) {
			assert(false);
		}
		for (int i = 0; i < (int)animation.element.edges.size(); i++) {
			auto e = animation.element.edges[i];
			int u = e.first, v = e.second, newv = animation.work.goalNode[i];
			edgeSwitchList.push_back({ u, v, newv });
		}
		if (time < epsilonTime) {
			graph.switchEdges(edgeSwitchList);
		}
		else {
			graph.switchEdges(edgeSwitchList, time);
		}
	}
	if (animation.type == EdgeColor) {
		std::vector <std::tuple <int, int, sf::Color> > edgeList;
		if (animation.element.edges.size() != animation.work.colors.size()) {
			assert(false);
		}
		for (int i = 0; i < (int)animation.element.edges.size(); i++) {
			auto e = animation.element.edges[i];
			int u = e.first, v = e.second;
			sf::Color color = animation.work.colors[i];
			edgeList.push_back({ u, v, color });
		}
		if (time < epsilonTime) {
			graph.setEdgesColor(edgeList);
		}
		else {
			graph.setEdgesColor(edgeList, time);
		}
	}
}

void DataStructure::addAnimations(std::vector <Animation> animationList) {
	sort(animationList.begin(), animationList.end(), cmpAnimation);
	Graph tmpGraph = listFrame.back().graph;
	for (Animation& animation : animationList) {
		updateAnimation(tmpGraph, animation);
	}
	listFrame.back().nextStep = animationList;
	listFrame.push_back({ tmpGraph, {} });
	curGraph = tmpGraph;
}

void DataStructure::animateFrame(int idFrame, sf::Time time) {//from idFrame - 1 to idFrame
	if (idFrame < 1) {
		return;
	}
	curGraph = listFrame[idFrame - 1].graph;
	for (Animation& animation : listFrame[idFrame - 1].nextStep) {
		updateAnimation(curGraph, animation, time);
	}
}

void DataStructure::update(sf::Time deltaT) {
	curGraph.update(deltaT);
}

void DataStructure::draw(sf::RenderWindow& window) {
	curGraph.draw(window);
}