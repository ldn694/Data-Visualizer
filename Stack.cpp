#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "Stack.h"

Stack::Stack(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* font) : 
	DataStructure(radius, outlineSize, lineThickness, _theme, edgeType, font) {}

int Stack::getSize() {
	return (int)stack.size();
}

int Stack::getHeadValue() {
	return stack[0].value;
}

int Stack::getHeadID() {
	return stack[0].id;
}

std::vector <int> Stack::getIDList(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(stack[i].id);
	}
	return id;
}

int Stack::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : stack) {
			if (dComp.id == id) {
				flag = true;
			}
		}
		if (!flag) {
			break;
		}
		id++;
	}
	return id;
}

void Stack::createRandom(int n) {
	if (n == -1) {
		n = rand() % 10 + 1;
	}
	stack.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	stack.clear();
	std::vector <int> nodeList;
	std::vector <std::pair <int, int> > edgeList;
	std::vector <sf::Color> color;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (5 * n - 5))) / 2;
	double y = HEIGHT_RES / 3;
	for (int i = 0; i < n; i++) {
		int value = rand() % 100 + 1;
		stack.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
		nodeList.push_back(i);
		nodeInfo.push_back({ value, x, y });
		x += defaultNode.getRadius() * 5;
		if (i < n - 1) {
			edgeList.push_back({ i, i + 1 });
			color.push_back({ defaultNode.getOutlineColor() });
		}
	}
	std::vector <Animation> animationList;
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = nodeList;
	tmp.work.nodeInfos = nodeInfo;
	animationList.push_back(tmp);
	if (n > 1) {
		tmp.type = AddEdge;
		tmp.element.edges = edgeList;
		tmp.work.colors = color;
		animationList.push_back(tmp);
	}
	addVariables(animationList, { 0 }, { "head" });
	addVariables(animationList, { getSize() - 1 }, { "tail" });
	addAnimations(animationList, stepTime);
	animateAllFrame();
}

void Stack::push(int value) {
	int id = getEmptyID();
	resetAnimation();
	if (getSize() == 0) {
		std::vector <Animation> animationList;
		addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		stack.push_back({ id, value, -1 });
		addVariables(animationList, { id }, { "head", "tail" ,"vtx"});
		addAnimations(animationList, stepTime);
		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		deleteVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime);
		animateAllFrame();
		return;
	}
	int head = getHeadID();
	std::vector <Animation> animationList;
	addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3 * 2);
	setNodeColor(animationList, { id }, theme, highlight);
	addVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime);

	animationList.clear();
	addEdge(animationList, id, head, theme, highlight);
	addAnimations(animationList, stepTime);


	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	setEdgeColor(animationList, id, head, theme, normal);
	addVariables(animationList, { id }, { "head" });
	deleteVariables(animationList, { getHeadID() }, { "head" });
	addAnimations(animationList, stepTime);

	animationList.clear();
	Node defaultNode = defaultGraph.getDefaultNode();
	translateNode(animationList, getIDList(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	stack.insert(stack.begin(), {id, value, head});
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime);

	animationList.clear();
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime);
	animateAllFrame();
}

void Stack::pop() {
	resetAnimation();
	if (getSize() == 0) {
		return;
	}
	int head = getHeadID();
	std::vector <Animation> animationList;
	setNodeColor(animationList, { head }, theme, highlight);
	addVariables(animationList, { head }, { "temp" });
	addAnimations(animationList, stepTime);

	if (getSize() > 1) {
		animationList.clear();
		setEdgeColor(animationList, head, stack[1].id, theme, highlight2);
		setNodeColor(animationList, { stack[1].id }, theme, highlight2);
		deleteVariables(animationList, { head }, { "head" });
		addVariables(animationList, { stack[1].id }, { "head" });
		addAnimations(animationList, stepTime);
	}

	animationList.clear();
	deleteNode(animationList, head);
	Node defaultNode = defaultGraph.getDefaultNode();
	if (getSize() > 1) {
		translateNode(animationList, getIDList(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	}
	addAnimations(animationList, stepTime);
	stack.erase(stack.begin());

	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		addAnimations(animationList, stepTime);
	}

	animateAllFrame();
}

void Stack::peek() {
	resetAnimation();
	if (getSize() == 0) {
		std::cout << "No nodes found!\n";
		return;
	}
	std::vector <Animation> animationList;
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime);
	std::cout << "Value stored at head is " << stack[0].value << "\n";

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime);

	animateAllFrame();
}