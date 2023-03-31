#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* font) :
	theme(_theme),
	DataStructure(radius, outlineSize, lineThickness, colorNode[_theme][normal].fillColor, colorNode[_theme][normal].outlineColor, colorNode[_theme][normal].valueColor, colorNode[_theme][normal].variableColor, edgeType, font) {}

int SinglyLinkedList::getSize() {
	return (int)linkedList.size();
}

int SinglyLinkedList::getHeadValue() {
	return linkedList[0].value;
}

int SinglyLinkedList::getHeadID() {
	return linkedList[0].id;
}

std::vector <int> SinglyLinkedList::getIDList(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(linkedList[i].id);
	}
	return id;
}

int SinglyLinkedList::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : linkedList) {
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

void SinglyLinkedList::createRandom() {
	int n = rand() % 10 + 1;
	linkedList.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	linkedList.clear();
	std::vector <int> nodeList;
	std::vector <std::pair <int, int> > edgeList;
	std::vector <sf::Color> color;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (5 * n - 5))) / 2;
	double y = HEIGHT_RES / 3;
	for (int i = 0; i < n; i++) {
		int value = rand() % 100 + 1;
		linkedList.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
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
	tmp.type = AddEdge;
	tmp.element.edges = edgeList;
	tmp.work.colors = color;
	animationList.push_back(tmp);
	addAnimations(animationList, stepTime);
	animateAllFrame();
}

void SinglyLinkedList::insertFront(int value) {
	int id = getEmptyID();
	resetAnimation();
	if (getSize() == 0) {
		std::vector <Animation> animationList;
		addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		linkedList.push_back({ id, value, -1 });
		addAnimations(animationList, stepTime);
		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		addAnimations(animationList, stepTime);
		animateAllFrame();
		return;
	}
	int head = getHeadID();
	std::vector <Animation> animationList;
	addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3 * 2);
	setNodeColor(animationList, { id }, theme, highlight);
	addAnimations(animationList, stepTime);

	animationList.clear();
	addEdge(animationList, id, head, theme, highlight);
	addAnimations(animationList, stepTime);


	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	setEdgeColor(animationList, id, head, theme, normal);
	addAnimations(animationList, stepTime);

	animationList.clear();
	Node defaultNode = defaultGraph.getDefaultNode();
	translateNode(animationList, getIDList(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	linkedList.insert(linkedList.begin(), { id, value, head });
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime);

	animationList.clear();
	setNodeColor(animationList, { id }, theme, normal);
	addAnimations(animationList, stepTime);
	animateAllFrame();
}

void SinglyLinkedList::eraseFront() {
	resetAnimation();
	if (getSize() == 0) {
		return;
	}
	int head = getHeadID();
	std::vector <Animation> animationList;
	setNodeColor(animationList, { head }, theme, highlight);
	addAnimations(animationList, stepTime);

	if (getSize() > 1) {
		animationList.clear();
		setEdgeColor(animationList, head, linkedList[1].id, theme, highlight2);
		setNodeColor(animationList, { linkedList[1].id }, theme, highlight2);
		addAnimations(animationList, stepTime);
	}

	animationList.clear();
	deleteNode(animationList, head);
	Node defaultNode = defaultGraph.getDefaultNode();
	if (getSize() > 1) {
		translateNode(animationList, getIDList(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	}
	addAnimations(animationList, stepTime);
	linkedList.erase(linkedList.begin());

	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		addAnimations(animationList, stepTime);
	}

	animateAllFrame();
}