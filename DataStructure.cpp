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
	std::vector <std::vector <std::string> > _codes, double x, double y, double width, double height, sf::Font* codeFont,
	double _xAnnouncement, double _yAnnouncement, double _widthAnnouncement, double _heightAnnouncement, sf::Font* _announcementFont) :
	theme(_theme), codes(_codes),
	xAnnouncement(_xAnnouncement), yAnnouncement(_yAnnouncement), widthAnnouncement(_widthAnnouncement), heightAnnouncement(_heightAnnouncement), announcementFont(_announcementFont),
	defaultGraph(Graph(radius, outlineSize, lineThickness, colorNode[_theme][normal].fillColor, colorNode[_theme][normal].outlineColor, colorNode[_theme][normal].valueColor, colorNode[_theme][normal].variableColor, idEdgeType, font))
{
	isAnimating = false;
	mainGraph = defaultGraph;
	curGraph = defaultGraph;
	listFrame.push_back({ defaultGraph, {} });
	speed = 1.0f;
	
	numOperation = codes.size();
	numStep.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		assert(!codes[i].empty());
		assert(codes[0][0] == "");
		numStep[i] = codes[i].size() - 1;
	}
	codeText.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		codeText[i].resize(numStep[i] + 1);
		double stepY = height / numStep[i];
		double outlineSize = height / numStep[i] * 0.2f;
		double maxHeight = height / numStep[i] * 0.6f;
		double charSize = 10000.f;
		for (int j = 1; j <= numStep[i]; j++) {
			double l = 0, r = maxHeight, res = 0;
			for (int cnt = 0; cnt < 60; cnt++) {
				double mid = (l + r) / 2.0f;
				sf::Text text;
				text.setString(codes[i][j]);
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
		for (int j = 1; j <= numStep[i]; j++) {
			codeText[i][j].setString(codes[i][j]);
			codeText[i][j].setFont(*codeFont);
			codeText[i][j].setCharacterSize(charSize);
			codeText[i][j].setPosition(x + outlineSize, curY);
			codeText[i][j].setFillColor(codeNormalViewColor[theme]);
			curY += stepY;
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
	for (int i = 0; i < numOperation; i++) {
		for (int j = 1; j <= numStep[i]; j++) {
			codeText[i][j].setFillColor(codeNormalViewColor[theme]);
		}
	}
}

void DataStructure::setSpeed(double newSpeed) {
	speed = newSpeed;
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

void DataStructure::doNothing(std::vector <Animation>& animationList) {
	Animation tmp;
	tmp.type = DoNothing;
	animationList.push_back(tmp);
}

void DataStructure::setCurOperation(int val) {
	curOperation = val;
	curStep = 0;
	curFrame = 0;
	for (int i = 0; i < numOperation; i++) {
		for (int j = 1; j <= numStep[i]; j++) {
			codeText[i][j].setFillColor(codeNormalViewColor[theme]);
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
}

void DataStructure::draw(sf::RenderWindow& window) {
	curGraph.draw(window);
	/*sf::RectangleShape tmpRect = codeBoard;
	tmpRect.setFillColor(codeNormalBackGroundColor[theme]);
	window.draw(tmpRect);*/
	sf::FloatRect codeBoardRect = codeBoard.getGlobalBounds();
	Box tmpBox(codeBoardRect.left, codeBoardRect.top, codeBoardRect.width, codeBoardRect.height, {CodeOuterBox});
	tmpBox.draw(window, theme);
	if (codes[curOperation][curStep] != "") {
		double width = codeBoard.getGlobalBounds().width;
		double height = codeBoard.getGlobalBounds().height;
		double left = codeBoard.getGlobalBounds().left;
		double top = codeBoard.getGlobalBounds().top;
		double stepY = height / numStep[curOperation];
		double outlineSize = height / numStep[curOperation] * 0.2f;
		sf::RectangleShape highlightRect(sf::Vector2f(width,  stepY));
		highlightRect.setPosition(left, top + (curStep - 1) * stepY);
		highlightRect.setFillColor(codeHighlightBackGroundColor[theme]);
		window.draw(highlightRect);
	}
	for (int i = 1; i <= numStep[curOperation]; i++) {
		if (i == curStep) {
			codeText[curOperation][i].setFillColor(codeHightlightViewColor[theme]);
		}
		window.draw(codeText[curOperation][i]);
		if (i == curStep) {
			codeText[curOperation][i].setFillColor(codeNormalViewColor[theme]);
		}
	}
	if (!listFrame.empty()) {
		std::string resText, cur, tmp;
		sf::Text tmpText;
		tmpText.setFont(*announcementFont);
		tmpText.setCharacterSize(sizeLetterAnnouncement);
		std::vector <std::string> words;
		cur = listFrame[curFrame].announcement + " ";
		for (char x : cur) {
			if (x == ' ') {
				words.push_back(tmp);
				tmp.clear();
			}
			else {
				tmp.push_back(x);
			}
		}
		cur.clear();
		tmp.clear();
		for (int i = 0; i < words.size(); i++) {
			tmp = cur + " " + words[i];
			tmpText.setString(tmp);
			if (tmpText.getLocalBounds().width > widthAnnouncement) {
				resText = resText + cur + "\n";
				cur = words[i];
			}
			else {
				cur = tmp;
			}
		}
		resText = resText + cur;
		while (!resText.empty() && resText[0] == ' ') {
			resText.erase(0, 1);
		}
		sf::RectangleShape tmpRect(sf::Vector2f(widthAnnouncement - outlineBox, heightAnnouncement - outlineBox));
		tmpRect.setPosition(xAnnouncement + outlineBox, yAnnouncement - outlineBox);
		tmpRect.setFillColor(announcementFillColor[theme]);
		window.draw(tmpRect);
		tmpText.setString(resText);
		tmpText.setOrigin(tmpText.getLocalBounds().left + tmpText.getLocalBounds().width / 2.0f, tmpText.getLocalBounds().top + tmpText.getLocalBounds().height / 2.0f);
		tmpText.setPosition(tmpRect.getGlobalBounds().left + tmpRect.getGlobalBounds().width / 2.0f, tmpRect.getGlobalBounds().top + tmpRect.getGlobalBounds().height / 2.0f);
		tmpText.setFillColor(announcementTextColor[theme]);
		window.draw(tmpText);
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