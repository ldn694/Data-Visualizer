#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "Stack.h"

Stack::Stack(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* _font) : 
	DataStructure(radius, outlineSize, lineThickness, _theme, edgeType, _font, 
		{
			{
				""
			},
			{
				"",
				"Vertex vtx = new Vertex(v)",
				"vtx.next = head",
				"head = vtx"
			},
			{
				"",
				"if empty, do nothing",
				"temp = head",
				"head = head.next",
				"delete temp"
			},
			{
				"",
				"if empty, return NOT_FOUND",
				"return head.item"
			}
		}, WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 3, widthBox * 2, heightBox * 3, font(fontType::Consolas),
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Consolas),
		0, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Arial))  {}

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

void Stack::createRandom(int n, std::vector <int> values) {
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
		int value = (values.empty() ? rand() % 100 + 1 : values[i]);
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
	addAnimations(animationList, stepTime, 0, "Created a stack of length " + intToString(n));
	animateAllFrame();
}

void Stack::push(int value) {
	if (getSize() + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	int id = getEmptyID();
	resetAnimation();
	if (getSize() == 0) {
		std::vector <Animation> animationList;
		addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		stack.push_back({ id, value, -1 });
		addVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 1, "Create new vertex to store value " + intToString(value));
		animationList.clear();
		addVariables(animationList, { id }, { "head" });
		setNodeColor(animationList, { id }, theme, highlight2);
		addAnimations(animationList, stepTime, 3, "Head is currently null, so head now points to vtx");
		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		deleteVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
		animateAllFrame();
		return;
	}
	int head = getHeadID();
	std::vector <Animation> animationList;
	addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 2);
	setNodeColor(animationList, { id }, theme, highlight);
	addVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 1, "Create new vertex to store value " + intToString(value));

	animationList.clear();
	addEdge(animationList, id, head, theme, highlight);
	addAnimations(animationList, stepTime, 2, "vtx.next points to head");


	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	setEdgeColor(animationList, id, head, theme, normal);
	addVariables(animationList, { id }, { "head" });
	deleteVariables(animationList, { getHeadID() }, { "head" });
	addAnimations(animationList, stepTime, 3, "head points to vtx");

	animationList.clear();
	Node defaultNode = defaultGraph.getDefaultNode();
	translateNode(animationList, getIDList(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	stack.insert(stack.begin(), {id, value, head});
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime, 3, "Re-layout for visualization");

	animationList.clear();
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void Stack::pop() {
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Stack is empty, no action is performed");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0);

		animateAllFrame();
		return;
	}
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "Stack is not empty, proceed to next step");
	animationList.clear();
	int head = getHeadID();
	Node defaultNode = defaultGraph.getDefaultNode();
	if (getSize() == 1) {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "temp points to head");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 3, "head->next is null, so head is now also null (empty stack)");

		animationList.clear();
		deleteNode(animationList, head);
		translateNode(animationList, getIDList(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 4, "delete temp, now stack is empty");
	}
	else {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "temp points to head");

		animationList.clear();
		setEdgeColor(animationList, head, stack[1].id, theme, highlight2);
		setNodeColor(animationList, { stack[1].id }, theme, highlight2);
		deleteVariables(animationList, { head }, { "head" });
		addVariables(animationList, { stack[1].id }, { "head" });
		addAnimations(animationList, stepTime, 3, "head points to head->next");

		animationList.clear();
		deleteNode(animationList, head);
		translateNode(animationList, getIDList(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 4, "delete temp");
	}
	stack.erase(stack.begin());
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	}
	animateAllFrame();
}

void Stack::peek() {
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Stack is empty, no action is performed");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0);

		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "Stack is not empty, proceed to next step");

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Return value stored at top of stack: " + intToString(stack[0].value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}