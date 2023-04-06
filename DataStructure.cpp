#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include "Template.h"
#include "Graph.h"
#include "DataStructure.h"

DataStructure::DataStructure(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType idEdgeType, sf::Font* font) : 
	theme(_theme),
	defaultGraph(Graph(radius, outlineSize, lineThickness, colorNode[_theme][normal].fillColor, colorNode[_theme][normal].outlineColor, colorNode[_theme][normal].valueColor, colorNode[_theme][normal].variableColor, idEdgeType, font))
{
	mainGraph = defaultGraph;
	curGraph = defaultGraph;
	listFrame.push_back({ defaultGraph, {} });
	speed = 1.0f;
}

void DataStructure::resetAnimation() {
	frameQueue.clear();
	curGraph = mainGraph;
	listFrame.clear();
	listFrame.push_back({ mainGraph, {} });
}

void DataStructure::setTheme(ColorTheme newTheme) {
	defaultGraph.setTheme(theme, newTheme);
	std::cout << "Done default\n";
	curGraph.setTheme(theme, newTheme);
	std::cout << "Done cur\n";
	mainGraph.setTheme(theme, newTheme);
	std::cout << "Done main\n";
	for (int i = 0; i < (int)listFrame.size(); i++) {
		listFrame[i].graph.setTheme(theme, newTheme);
		for (int j = 0; j < (int)listFrame[i].nextStep.size(); j++) {
			Animation& tmp = listFrame[i].nextStep[j];
			if (tmp.type == FillColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].fillColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				tmp.work.colors = { colorNode[newTheme][resType].fillColor };
			}
			if (tmp.type == OutlineColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].outlineColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				tmp.work.colors = { colorNode[newTheme][resType].outlineColor };
			}
			if (tmp.type == ValueColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].valueColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				tmp.work.colors = { colorNode[newTheme][resType].valueColor };
			}
			if (tmp.type == VariableColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].variableColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				tmp.work.colors = { colorNode[newTheme][resType].variableColor };
			}
			if (tmp.type == EdgeColor) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].outlineColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				tmp.work.colors = { colorNode[newTheme][resType].outlineColor };
			}
			if (tmp.type == AddEdge) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				sf::Color hereColor = tmp.work.colors[0];
				int resType = -1;
				for (int type = 0; type < numColorNodeType; type++) {
					if (colorNode[theme][type].outlineColor == hereColor) {
						resType = type;
						break;
					}
				}
				assert(resType != -1);
				for (int i = 0; i < (int)tmp.work.colors.size(); i++) {
					tmp.work.colors[i] = colorNode[newTheme][resType].outlineColor;
				}
			}
		}
	}
	theme = newTheme;
}


bool cmpAnimation(const Animation& a, const Animation& b) {
	return a.type < b.type;
}

void DataStructure::setNodeColor(std::vector <Animation>& animationList, std::vector <int> nodes, ColorTheme theme, ColorNodeType type)
{
	Animation tmp;
	tmp.type = FillColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type].fillColor);
	}
	animationList.push_back(tmp);
	tmp.type = OutlineColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type].outlineColor);
	}
	animationList.push_back(tmp);
	tmp.type = ValueColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type].valueColor);
	}
	animationList.push_back(tmp);
	tmp.type = VariableColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type].variableColor);
	}
	animationList.push_back(tmp);
}

void DataStructure::addNode(std::vector <Animation>& animationList, int pos, int value, double x, double y) {
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = { pos };
	tmp.work.nodeInfos = { {value, x, y} };
	animationList.push_back(tmp);
}

void DataStructure::deleteNode(std::vector <Animation>& animationList, int pos) {
	Animation tmp;
	tmp.type = DeleteNode;
	tmp.element.nodes = { pos };
	animationList.push_back(tmp);
}

void DataStructure::translateNode(std::vector <Animation>& animationList, std::vector <int> nodes, double dx, double dy) {
	Animation tmp;
	tmp.type = TranslateNode;
	tmp.element.nodes = nodes;
	tmp.work.coordinates = { {dx, dy} };
	animationList.push_back(tmp);
}

void DataStructure::mergeMoveNode(std::vector <Animation>& animationList) {
	Animation tmp;
	tmp.type = MergeMoveNode;
	animationList.push_back(tmp);
}

void DataStructure::moveNode(std::vector <Animation>& animationList, int pos, double x, double y) {
	Animation tmp;
	tmp.type = MoveNode;
	tmp.element.nodes = { pos };
	tmp.work.coordinates = { {x, y} };
	animationList.push_back(tmp);
}

void DataStructure::addVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList) {
	Animation tmp;
	tmp.type = AddVariable;
	tmp.element.nodes = nodes;
	tmp.work.variables = variableList;
	animationList.push_back(tmp);
}

void DataStructure::deleteVariables(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <std::string> variableList) {
	Animation tmp;
	tmp.type = DeleteVariable;
	tmp.element.nodes = nodes;
	tmp.work.variables = variableList;
	animationList.push_back(tmp);
}

void DataStructure::addEdge(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = AddEdge;
	tmp.element.edges = { {u, v} };
	tmp.work.colors = { colorNode[theme][type].outlineColor };
	animationList.push_back(tmp);
}

void DataStructure::setEdgeColor(std::vector <Animation>& animationList, int u, int v, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = EdgeColor;
	tmp.element.edges = { {u, v} };
	tmp.work.colors = { colorNode[theme][type].outlineColor };
	animationList.push_back(tmp);
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
	if (animation.type == TranslateNode) {
		if (animation.work.coordinates.empty()) {
			assert(false);
		}
		double dx = animation.work.coordinates[0].first, dy = animation.work.coordinates[0].second;
		if (time < epsilonTime) {
			graph.translateNodes(animation.element.nodes, dx, dy);
		}
		else {
			graph.translateNodes(animation.element.nodes, dx, dy, time);
		}
	}
	if (animation.type == MergeMoveNode) {
		graph.mergeNodeMove();
	}
	if (animation.type == AddVariable) {
		for (int u : animation.element.nodes) {
			for (std::string variable : animation.work.variables) {
				graph.addNodeVariable(u, variable);
			}
		}
	}
	if (animation.type == DeleteVariable) {
		for (int u : animation.element.nodes) {
			for (std::string variable : animation.work.variables) {
				graph.deleteNodeVariable(u, variable);
			}
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
	if (animation.type == VariableColorNode) {
		if (animation.element.nodes.size() != animation.work.colors.size()) {
			assert(false);
		}
		std::vector <std::pair <int, sf::Color> > nodeList;
		for (int i = 0; i < (int)animation.element.nodes.size(); i++) {
			int u = animation.element.nodes[i];
			sf::Color color = animation.work.colors[i];
			nodeList.push_back({ u, color });
		}
		graph.setNodesVariableColor(nodeList);
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

void DataStructure::addAnimations(std::vector <Animation> animationList, sf::Time time) {
	sort(animationList.begin(), animationList.end(), cmpAnimation);
	Graph tmpGraph = listFrame.back().graph;
	for (Animation& animation : animationList) {
		updateAnimation(tmpGraph, animation);
	}
	listFrame.back().nextStep = animationList;
	listFrame.back().time = time;
	listFrame.push_back({ tmpGraph, {} });
	curGraph = tmpGraph;
	mainGraph = tmpGraph;
}

void DataStructure::animateFrame(int idFrame) {//from idFrame - 1 to idFrame
	if (idFrame < 1 || idFrame >= listFrame.size()) {
		return;
	}
	frameQueue.push_back({ idFrame, speed * (listFrame[idFrame - 1].time + delayTime), false});
}

void DataStructure::animateAllFrame() {
	for (int i = 1; i < (int)listFrame.size(); i++) {
		animateFrame(i);
	}
}

void DataStructure::update(sf::Time deltaT) {
	updateFrameQueue(deltaT);
}

void DataStructure::draw(sf::RenderWindow& window) {
	curGraph.draw(window);
}

void DataStructure::updateFrameQueue(sf::Time deltaT) {
	while (!frameQueue.empty()) {
		auto &cur = frameQueue.front();
		frameQueue.pop_front();
		int idFrame = std::get<0>(cur);
		sf::Time time = (std::get<1>(cur) - speed * delayTime);
		if (!std::get<2>(cur)) {
			curGraph = listFrame[idFrame - 1].graph;
			for (Animation& animation : listFrame[idFrame - 1].nextStep) {
				updateAnimation(curGraph, animation, time);
			}
		}
		time += speed * delayTime;
		sf::Time elapsedTime = (time < deltaT ? time : deltaT);
		curGraph.update(elapsedTime);
		deltaT -= elapsedTime;
		time -= elapsedTime;
		if (time >= epsilonTime) {
			frameQueue.push_front({idFrame, time, true});
		}
		else {

		}
		if (deltaT < epsilonTime) break;
	}
}

void DataStructure::clearFrameQueue() {
	frameQueue.clear();
}