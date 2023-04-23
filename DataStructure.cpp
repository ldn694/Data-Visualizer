#pragma once

#include <vector>
#include <cassert>
#include <iostream>
#include "Template.h"
#include "Graph.h"
#include "DataStructure.h"
#include "Box.h"

DataStructure::DataStructure(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType idEdgeType, sf::Font* font, 
	std::vector <std::vector <std::vector <std::string> > > _codes, double x, double y, double width, double height, sf::Font* codeFont,
	double _xAnnouncement, double _yAnnouncement, double _widthAnnouncement, double _heightAnnouncement, sf::Font* _announcementFont,
	double _xError, double _yError, double _widthError, double _heightError, sf::Font* _errorFont) :
	theme(_theme), codes(_codes),
	xAnnouncement(_xAnnouncement), yAnnouncement(_yAnnouncement), widthAnnouncement(_widthAnnouncement), heightAnnouncement(_heightAnnouncement), announcementFont(_announcementFont),
	xError(_xError), yError(_yError), widthError(_widthError), heightError(_heightError), errorFont(_errorFont),
	defaultGraph(Graph(radius, outlineSize, lineThickness, colorNode[_theme][normal].fillColor, colorNode[_theme][normal].outlineColor, colorNode[_theme][normal].valueColor, colorNode[_theme][normal].variableColor, idEdgeType, font))
{
	errorTime = sf::seconds(0.f);
	isAnimating = false;
	mainGraph = defaultGraph;
	curGraph = defaultGraph;
	listFrame.push_back({ defaultGraph, {} });
	speed = 1.0f;
	
	numOperation = codes.size();
	numStep.resize(numOperation);
	numMode.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		numMode[i] = codes[i].size();
		numStep[i].resize(numMode[i]);
		for (int j = 0; j < numMode[i]; j++) {
			numStep[i][j] = codes[i][j].size() - 1;
		}
	}
	codeText.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		codeText[i].resize(numMode[i]);
		for (int j = 0; j < numMode[i]; j++) {
			codeText[i][j].resize(numStep[i][j] + 1);
			double stepY = height / numStep[i][j];
			double outlineSize = height / numStep[i][j] * 0.2f;
			double maxHeight = height / numStep[i][j] * 0.6f;
			double charSize = 10000.f;
			for (int k = 1; k <= numStep[i][j]; k++) {
				double l = 0, r = maxHeight, res = 0;
				for (int cnt = 0; cnt < 60; cnt++) {
					double mid = (l + r) / 2.0f;
					sf::Text text;
					text.setString(codes[i][j][k]);
					text.setFont(*codeFont);
					text.setCharacterSize(mid);
					if (text.getLocalBounds().width <= width - outlineSize * 2) {
						res = mid;
						l = mid;
					}
					else {
						r = mid;
					}
				}
				if (charSize - res > epsilonDouble) {
					charSize = res;
				}
			}
			double curY = y + outlineSize;
			for (int k = 1; k <= numStep[i][j]; k++) {
				codeText[i][j][k].setString(codes[i][j][k]);
				codeText[i][j][k].setFont(*codeFont);
				codeText[i][j][k].setCharacterSize(charSize);
				codeText[i][j][k].setPosition(x + outlineSize, curY);
				codeText[i][j][k].setFillColor(codeNormalViewColor[theme]);
				curY += stepY;
			}
		}
	}
	codeBoard = sf::RectangleShape(sf::Vector2f(width, height));
	codeBoard.setPosition(x, y);
}

void DataStructure::resetAnimation() {
	frameQueue.clear();
	curGraph = mainGraph;
	listFrame.clear();
	listFrame.push_back({ mainGraph, {} });
}

void DataStructure::setError(bool val, std::string newError) {
	if (val) {
		error = newError;
		errorTime = errorDisplayTime;
	}
}

void DataStructure::setTheme(ColorTheme newTheme) {
	defaultGraph.setTheme(theme, newTheme);
	curGraph.setTheme(theme, newTheme);
	mainGraph.setTheme(theme, newTheme);
	for (int i = 0; i < (int)listFrame.size(); i++) {
		listFrame[i].graph.setTheme(theme, newTheme);
		for (int j = 0; j < (int)listFrame[i].nextStep.size(); j++) {
			Animation& tmp = listFrame[i].nextStep[j];
			if (tmp.type == FillColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].fillColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].fillColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == OutlineColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].outlineColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].outlineColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == ValueColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].valueColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].valueColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == VariableColorNode) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].variableColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].variableColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == EdgeColor) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].outlineColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].outlineColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == AddEdge) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].outlineColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].outlineColor);
				}
				tmp.work.colors = listColor;
			}
			if (tmp.type == AddCircularEdge) {
				if (tmp.work.colors.empty()) {
					continue;
				}
				std::vector <sf::Color> listColor;
				for (int k = 0; k < tmp.work.colors.size(); k++) {
					sf::Color hereColor = tmp.work.colors[k];
					int resType = -1;
					for (int type = 0; type < numColorNodeType; type++) {
						if (colorNode[theme][type].outlineColor == hereColor) {
							resType = type;
							break;
						}
					}
					assert(resType != -1);
					listColor.push_back(colorNode[newTheme][resType].outlineColor);
				}
				tmp.work.colors = listColor;
			}
		}
	}
	theme = newTheme;
	for (int i = 0; i < numOperation; i++) {
		for (int j = 0; j < numMode[i]; j++) {
			for (int k = 1; k <= numStep[i][j]; k++) {
				codeText[i][j][k].setFillColor(codeNormalViewColor[theme]);
			}
		}
	}
}

void DataStructure::setSpeed(double newSpeed) {
	speed = newSpeed;
}


bool cmpAnimation(const Animation& a, const Animation& b) {
	return a.type < b.type;
}

void DataStructure::setNodeColor(std::vector <Animation>& animationList, std::vector <int> nodes, ColorTheme theme, std::vector <ColorNodeType> type)
{
	assert(nodes.size() == type.size());
	Animation tmp;
	tmp.type = FillColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].fillColor);
	}
	animationList.push_back(tmp);
	tmp.type = OutlineColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].outlineColor);
	}
	animationList.push_back(tmp);
	tmp.type = ValueColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].valueColor);
	}
	animationList.push_back(tmp);
	tmp.type = VariableColorNode;
	tmp.element.nodes = nodes;
	tmp.work.colors.clear();
	for (int i = 0; i < (int)nodes.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].variableColor);
	}
	animationList.push_back(tmp);
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

void DataStructure::setNodeValue(std::vector <Animation>& animationList, std::vector <int> nodes, std::vector <int> values) {
	Animation tmp;
	tmp.type = ValueNode;
	tmp.element.nodes = nodes;
	tmp.work.values = values;
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

void DataStructure::addEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = AddEdge;
	tmp.element.edges = edges;
	tmp.work.colors = std::vector <sf::Color>(edges.size(), colorNode[theme][type].outlineColor);
	animationList.push_back(tmp);
}

void DataStructure::addCircularEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = AddCircularEdge;
	tmp.element.edges = edges;
	tmp.work.colors = std::vector <sf::Color>(edges.size(), colorNode[theme][type].outlineColor);
	animationList.push_back(tmp);
}

void DataStructure::addEdge(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type) {
	assert(edges.size() == type.size());
	Animation tmp;
	tmp.type = AddEdge;
	tmp.element.edges = edges;
	for (int i = 0; i < edges.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].outlineColor);
	}
	animationList.push_back(tmp);
}

void DataStructure::deleteEdge(std::vector <Animation>& animationList, std::vector < std::pair <int, int> > edges) {
	Animation tmp;
	tmp.type = DeleteEdge;
	tmp.element.edges = edges;
	animationList.push_back(tmp);
}

void DataStructure::setEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = EdgeColor;
	tmp.element.edges = edges;
	tmp.work.colors = std::vector <sf::Color>(edges.size(), colorNode[theme][type].outlineColor);
	animationList.push_back(tmp);
}

void DataStructure::setEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type) {
	assert(edges.size() == type.size());
	Animation tmp;
	tmp.type = EdgeColor;
	tmp.element.edges = edges;
	for (int i = 0; i < type.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].outlineColor);
	}
	animationList.push_back(tmp);
}

void DataStructure::setCircularEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, ColorNodeType type) {
	Animation tmp;
	tmp.type = CircularEdgeColor;
	tmp.element.edges = edges;
	tmp.work.colors = std::vector <sf::Color>(edges.size(), colorNode[theme][type].outlineColor);
	animationList.push_back(tmp);
}

void DataStructure::setCircularEdgeColor(std::vector <Animation>& animationList, std::vector <std::pair <int, int>> edges, ColorTheme theme, std::vector <ColorNodeType> type) {
	assert(edges.size() == type.size());
	Animation tmp;
	tmp.type = CircularEdgeColor;
	tmp.element.edges = edges;
	for (int i = 0; i < type.size(); i++) {
		tmp.work.colors.push_back(colorNode[theme][type[i]].outlineColor);
	}
	animationList.push_back(tmp);
}

void DataStructure::switchEdge(std::vector <Animation>& animationList, std::vector <std::tuple <int, int, int> > edgeList) {
	Animation tmp;
	tmp.type = SwitchEdge;
	for (int i = 0; i < edgeList.size(); i++) {
		tmp.element.edges.push_back({ std::get<0>(edgeList[i]), std::get<1>(edgeList[i]) });
		tmp.work.goalNode.push_back(std::get<2>(edgeList[i]));
	}
	animationList.push_back(tmp);
}

void DataStructure::switchCircularEdge(std::vector <Animation>& animationList, std::vector <std::tuple <int, int, int> > edgeList) {
	Animation tmp;
	tmp.type = SwitchCircularEdge;
	for (int i = 0; i < edgeList.size(); i++) {
		tmp.element.edges.push_back({ std::get<0>(edgeList[i]), std::get<1>(edgeList[i]) });
		tmp.work.goalNode.push_back(std::get<2>(edgeList[i]));
	}
	animationList.push_back(tmp);
}

void DataStructure::doNothing(std::vector <Animation>& animationList) {
	Animation tmp;
	tmp.type = DoNothing;
	animationList.push_back(tmp);
}

void DataStructure::setCurOperation(int val) {
	errorTime = sf::seconds(0.f);
	curOperation = val;
	curMode = 0;
	curStep = 0;
	curFrame = 0;
	for (int i = 0; i < numOperation; i++) {
		for (int j = 0; j < numMode[i]; j++) {
			for (int k = 1; k <= numStep[i][j]; k++) {
				codeText[i][j][k].setFillColor(codeNormalViewColor[theme]);
			}
		}
	}
}

void DataStructure::setCurMode(int val) {
	errorTime = sf::seconds(0.f);
	curMode = val;
	curStep = 0;
	curFrame = 0;
	for (int i = 0; i < numOperation; i++) {
		for (int j = 0; j < numMode[i]; j++) {
			for (int k = 1; k <= numStep[i][j]; k++) {
				codeText[i][j][k].setFillColor(codeNormalViewColor[theme]);
			}
		}
	}
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
	if (animation.type == ValueNode) {
		if (animation.element.nodes.size() != animation.work.values.size()) {
			assert(false);
		}
		for (int i = 0; i < animation.element.nodes.size(); i++) {
			graph.setNodeValue(animation.element.nodes[i], animation.work.values[i]);
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
	if (animation.type == AddCircularEdge) {
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
			graph.addCircularEdges(edgeList);
		}
		else {
			graph.addCircularEdges(edgeList, time);
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
	if (animation.type == SwitchCircularEdge) {
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
			graph.switchCircularEdges(edgeSwitchList);
		}
		else {
			graph.switchCircularEdges(edgeSwitchList, time);
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
	if (animation.type == CircularEdgeColor) {
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
			graph.setCircularEdgesColor(edgeList);
		}
		else {
			graph.setCircularEdgesColor(edgeList, time);
		}
	}
	if (animation.type == DoNothing) {
		
	}
}

void DataStructure::addAnimations(std::vector <Animation> animationList, sf::Time time, int line, std::string announcement) {
	sort(animationList.begin(), animationList.end(), cmpAnimation);
	Graph tmpGraph = listFrame.back().graph;
	for (Animation& animation : animationList) {
		updateAnimation(tmpGraph, animation);
	}
	listFrame.back().nextStep = animationList;
	listFrame.back().time = time;
	listFrame.push_back({ tmpGraph, {}, sf::seconds(0.f), line, announcement});
	curGraph = tmpGraph;
	mainGraph = tmpGraph;
}

void DataStructure::setIsAnimating(bool val) {
	isAnimating = val;
}

void DataStructure::animateFrame(int idFrame) {//from idFrame - 1 to idFrame
	if (idFrame < 1 || idFrame >= listFrame.size()) {
		return;
	}
	frameQueue.push_back({ idFrame, listFrame[idFrame - 1].time, delayTime, false});
}

void DataStructure::setFrame(int idFrame) {
	if (idFrame < 0 || idFrame >= listFrame.size()) {
		return;
	}
	curFrame = idFrame;
	curGraph = listFrame[idFrame].graph;
	curStep = listFrame[idFrame].line;
	clearFrameQueue();
	for (int i = idFrame + 1; i < listFrame.size(); i++) {
		animateFrame(i);
	}
}

void DataStructure::animateAllFrame() {
	setFrame(0);
}

void DataStructure::update(sf::Time deltaT) {
	updateFrameQueue(deltaT * (float)speed);
	sf::Time elapsedTime = deltaT < errorTime ? deltaT : errorTime;
	errorTime -= elapsedTime;
}

void DataStructure::draw(sf::RenderWindow& window) {
	curGraph.draw(window);
	/*sf::RectangleShape tmpRect = codeBoard;
	tmpRect.setFillColor(codeNormalBackGroundColor[theme]);
	window.draw(tmpRect);*/
	sf::FloatRect codeBoardRect = codeBoard.getGlobalBounds();
	Box tmpBox(codeBoardRect.left, codeBoardRect.top, codeBoardRect.width, codeBoardRect.height, {CodeOuterBox});
	tmpBox.draw(window, theme);
	if (codes[curOperation][curMode][curStep] != "") {
		double width = codeBoard.getGlobalBounds().width;
		double height = codeBoard.getGlobalBounds().height;
		double left = codeBoard.getGlobalBounds().left;
		double top = codeBoard.getGlobalBounds().top;
		double stepY = height / numStep[curOperation][curMode];
		double outlineSize = height / numStep[curOperation][curMode] * 0.2f;
		sf::RectangleShape highlightRect(sf::Vector2f(width,  stepY));
		highlightRect.setPosition(left, top + (curStep - 1) * stepY);
		highlightRect.setFillColor(codeHighlightBackGroundColor[theme]);
		window.draw(highlightRect);
	}
	for (int i = 1; i <= numStep[curOperation][curMode]; i++) {
		if (i == curStep) {
			codeText[curOperation][curMode][i].setFillColor(codeHightlightViewColor[theme]);
		}
		window.draw(codeText[curOperation][curMode][i]);
		if (i == curStep) {
			codeText[curOperation][curMode][i].setFillColor(codeNormalViewColor[theme]);
		}
	}
	if (!listFrame.empty()) {
		sf::RectangleShape tmpRect(sf::Vector2f(widthAnnouncement, heightAnnouncement));
		tmpRect.setPosition(xAnnouncement, yAnnouncement);
		tmpRect.setFillColor(announcementFillColor[theme]);
		window.draw(tmpRect);
		sf::Text announcementText = CompressWords(listFrame[curFrame].announcement, 
			xAnnouncement, yAnnouncement, widthAnnouncement, heightAnnouncement, 
			announcementFont, sizeLetterAnnouncement, announcementTextColor[theme]);
		window.draw(announcementText);
	}
	if (errorTime >= epsilonTime) {
		sf::Text errorText = CompressWords(error,
			xError, yError, widthError, heightError,
			announcementFont, sizeLetterError, errorTextColor[theme]);
		window.draw(errorText);
	}
}

void DataStructure::updateFrameQueue(sf::Time deltaT) {
	while (!frameQueue.empty()) {
		auto &cur = frameQueue.front();
		if (!isAnimating && (delayTime - std::get<2>(cur) < epsilonTime && delayTime - std::get<2>(cur) > -epsilonTime)) {
			break;
		}
		frameQueue.pop_front();
		int idFrame = std::get<0>(cur);
		sf::Time time = std::get<1>(cur);
		sf::Time delayTime = std::get<2>(cur);
		if (delayTime < epsilonTime) {
			if (!std::get<3>(cur)) {
				curFrame = idFrame;
				curStep = listFrame[idFrame].line;
				curGraph = listFrame[idFrame - 1].graph;
				for (Animation& animation : listFrame[idFrame - 1].nextStep) {
					updateAnimation(curGraph, animation, time);
				}
			}
			sf::Time elapsedTime = (time < deltaT ? time : deltaT);
			curGraph.update(elapsedTime);
			deltaT -= elapsedTime;
			time -= elapsedTime;
			if (time >= epsilonTime) {
				frameQueue.push_front({idFrame, time, sf::seconds(0.f), true});
			}
		}
		else {
			sf::Time elapsedTime = (delayTime < deltaT ? delayTime : deltaT);
			deltaT -= elapsedTime;
			delayTime -= elapsedTime;
			frameQueue.push_front({ idFrame, time, delayTime, false });
		}
		if (deltaT < epsilonTime) break;
	}
}

void DataStructure::clearFrameQueue() {
	frameQueue.clear();
}