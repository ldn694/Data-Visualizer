#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "Queue.h"

Queue::Queue(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* _font, int numPointCircle) :
	DataStructure(radius, outlineSize, lineThickness, _theme, edgeType, _font, numPointCircle,
		{
			{
				{
					""
				},
				{
					""
				},
				{
					""
				},
				{
					""
				},
				{
					""
				},
				{
					""
				}
			},
			{
				{
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"} else {",
					"	tail->next = vtx;",
					"	tail = vtx;",
					"}"
				},
				{
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"} else {",
					"	tail->next = vtx;",
					"	tail = vtx;",
					"}"
				}
			},
			{
				{
					"",
					"if (head == NULL) return;",
					"Vertex* temp = head;",
					"head = head->next;",
					"if (head == NULL) tail = NULL;",
					"delete temp;"
				}
			},
			{
				{
					"",
					"if (head == NULL) return;",
					"return head->value;"
				},
				{
					"",
					"if (head == NULL) return;",
					"return tail->value;"
				}
			},
			{
				{
					"",
					"Vertex* cur = head;",
					"while (cur != NULL) {",
					"	Vertex* nxt = cur->next",
					"	delete cur;",
					"	cur = cur->next;",
					"}"
				}
			}
		},
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 3, widthBox * 2, heightBox * 3, font(fontType::Consolas),
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox, font(fontType::Consolas),
		0, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Arial)) {}

int Queue::getSize() {
	return (int)queue.size();
}

int Queue::getHeadValue() {
	return queue[0].value;
}

int Queue::getTailValue() {
	return queue.back().value;
}

int Queue::getHeadID() {
	return queue[0].id;
}

int Queue::getTailID() {
	return queue.back().id;
}

std::vector <int> Queue::getListID(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(queue[i].id);
	}
	return id;
}

int Queue::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : queue) {
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

void Queue::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	queue.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	if (n == 0) {
		std::vector <Animation> animationList;
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0, "Created a queue of length 0");
		setCurOperationName("Create queue of length 0");
		animateAllFrame();
		return;
	}
	std::vector <int> nodeList;
	std::vector <std::pair <int, int> > edgeList;
	std::vector <sf::Color> color;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (5 * n - 5))) / 2;
	double y = HEIGHT_RES / 3;
	std::vector <int> valueList;
	for (int i = 0; i < n; i++) {
		int value = (values.empty() ? rand() % 100 : values[i]);
		valueList.push_back(value);
	}
	if (sorted) {
		std::sort(valueList.begin(), valueList.end());
	}
	for (int i = 0; i < n; i++) {
		int value = valueList[i];
		queue.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
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
	addVariables(animationList, { 0 }, { "head"});
	addVariables(animationList, { n - 1 }, { "tail" });
	addAnimations(animationList, stepTime, 0, "Created a queue of length " + intToString(n));
	setCurOperationName("Create queue of length " + intToString(n));
	animateAllFrame();
}

void Queue::add(int value) {
	if (getSize() + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (value < 0) {
		value = rand() % (maxValueData + 1);
	}
	int id = getEmptyID();
	setCurOperationName("Add " + intToString(value) + " into queue");
	resetAnimation();
	if (getSize() == 0) {
		std::vector <Animation> animationList;
		addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		queue.push_back({ id, value, -1 });
		addVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 1, "Create new vertex to store value " + intToString(value));

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "head is currently null (empty queue), so the condition is true");

		animationList.clear();
		addVariables(animationList, { id }, { "head", "tail"});
		setNodeColor(animationList, { id }, theme, highlight2);
		addAnimations(animationList, stepTime, 3, "Now head and tail both points to vtx");

		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		deleteVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
		animateAllFrame();
		return;
	}
	int tail = getTailID();
	std::vector <Animation> animationList;
	addNode(animationList, id, value, WIDTH_RES / 2, HEIGHT_RES / 2);
	setNodeColor(animationList, { id }, theme, highlight);
	addVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 1, "Create new vertex to store value " + intToString(value));

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 2, "head is not null (queue not empty), so the condition is false");

	animationList.clear();
	addEdge(animationList, { {tail, id} }, theme, highlight);
	addAnimations(animationList, stepTime, 5, "tail->next now points to vtx");

	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	setEdgeColor(animationList, { {tail, id} }, theme, normal);
	addVariables(animationList, { id }, { "tail" });
	deleteVariables(animationList, { getTailID() }, { "tail" });
	addAnimations(animationList, stepTime, 6, "tail now points to vtx");

	animationList.clear();
	Node defaultNode = defaultGraph.getDefaultNode();
	translateNode(animationList, getListID(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	queue.push_back({id, value, tail});
	moveNode(animationList, id, WIDTH_RES - (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void Queue::remove() {
	setCurOperationName("Remove element at head of queue");
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Queue is empty, no action is performed");

		animateAllFrame();
		return;
	}
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "Queue is not empty, proceed to next step");
	animationList.clear();
	int head = getHeadID();
	Node defaultNode = defaultGraph.getDefaultNode();
	if (getSize() == 1) {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "Created new pointer temp pointing to head");

		animationList.clear();
		deleteVariables(animationList, { head }, { "head" });
		addAnimations(animationList, stepTime, 3, "head->next is null, so head is now also null (empty queue)");

		animationList.clear();
		doNothing(animationList);
		deleteVariables(animationList, { head }, { "tail" });
		addAnimations(animationList, stepTime, 4, "Queue is now empty, so tail is also null");

		animationList.clear();
		deleteNode(animationList, head);
		addAnimations(animationList, stepTime, 5, "Delete temp, the queue is empty");
		
		animationList.clear();
		setNodeColor(animationList, { head }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	}
	else {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "Created new pointer temp pointing to head");

		animationList.clear();
		setEdgeColor(animationList, { {head, queue[1].id} }, theme, highlight2);
		setNodeColor(animationList, { queue[1].id }, theme, highlight2);
		deleteVariables(animationList, { head }, { "head" });
		addVariables(animationList, { queue[1].id }, { "head" });
		addAnimations(animationList, stepTime, 3, "head now points to head->next");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "Queue is not empty (head != null), proceed to next step");

		animationList.clear();
		deleteNode(animationList, head);
		translateNode(animationList, getListID(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 5, "delete temp");
	}
	queue.erase(0);
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	}
	animateAllFrame();
}

void Queue::peekFront() {
	setCurOperationName("Peek element at head of queue");
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Queue is empty, no action is performed");

		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "Queue is not empty, proceed to next step");

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Return value stored at front of queue: " + intToString(queue[0].value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}

void Queue::peekBack() {
	setCurOperationName("Peek element at tail of queue");
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Queue is empty, no action is performed");

		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "Queue is not empty, proceed to next step");

	animationList.clear();
	setNodeColor(animationList, { getTailID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Return value stored at back of queue: " + intToString(queue.back().value));

	animationList.clear();
	setNodeColor(animationList, { getTailID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}

void Queue::clear() {
	setCurOperationName("Clear queue");
	resetAnimation();
	std::vector <Animation> animationList;

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "Create new pointer cur pointing to head, which is currently NULL (empty stack).");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "cur is now NULL, so the condition is false and no operation is performed.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 1, "Create new pointer cur pointing to head.");

	while (true) {
		if (getSize() == 0) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 2, "cur is now NULL (empty stack), so the condition is false and the loops stops here.");
			break;
		}
		animationList.clear();
		deleteVariables(animationList, { getHeadID() }, { "nxt" });
		addAnimations(animationList, stepTime, 2, "cur is not NULL, so the condition is true and the loops continues.");

		if (getSize() == 1) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "Create new pointer nxt pointing to cur->next (which is NULL).");
		}
		else {
			animationList.clear();
			setEdgeColor(animationList, { {getHeadID(), queue[1].id} }, theme, highlight2);
			setNodeColor(animationList, { {queue[1].id} }, theme, highlight2);
			addVariables(animationList, { queue[1].id }, { "nxt" });
			addAnimations(animationList, stepTime, 3, "Create new pointer nxt pointing to cur->next.");
		}

		animationList.clear();
		deleteNode(animationList, { getHeadID() });
		addAnimations(animationList, stepTime, 4, "Delete cur.");
		queue.erase(0);

		if (getSize() == 0) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 5, "cur now points to nxt (which is NULL).");
		}
		else {
			animationList.clear();
			setNodeColor(animationList, { getHeadID() }, theme, highlight);
			addVariables(animationList, { getHeadID() }, { "cur" });
			addAnimations(animationList, stepTime, 5, "cur now points to nxt.");
		}
	}

	animateAllFrame();
}