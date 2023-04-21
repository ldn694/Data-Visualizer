#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* _font) :
	DataStructure(radius, outlineSize, lineThickness, _theme, edgeType, _font,
		{
			{	//Create
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
			{	//Search
				{
					"",
					"if (head == NULL) return NOT_FOUND;",
					"Vertex* cur = head; int i = 0;",
					"while (cur != NULL) {",
					"   if (cur->value == v) return i;",
					"   cur = cur->next; i++;",
					"}",
					"return NOT_FOUND;"
				}
			},
			{	//Insert
				{	//Insert front
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"	return;",
					"}",
					"vtx->next = head; head->prev = vtx;",
					"head = vtx;"
				},
				{	//Insert back
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"	return;",
					"}",
					"tail->next = vtx; vtx->prev = tail;",
					"tail = vtx;"
				},
				{	//Insert middle
					"",
					"Vertex* cur = head; int k = 0;",
					"while (cur != NULL) {",
					"	if (k == i - 1) {",
					"		Vertex* vtx = new Vertex(v);",
					"		Vertex* aft = cur->next;",
					"		cur->next = vtx; vtx->prev = cur;",
					"		vtx->next = aft; aft->prev = vtx;",
					"		return;",
					"	}",
					"	cur = cur->next; k++;",
					"}"
				}
			},
			{	//Remove
				{	//Remove front
					"",
					"if (head == NULL) return;",
					"Vertex* temp = head;",
					"head = head->next;",
					"if (head == NULL)  {",
					"	tail = NULL;",
					"}",
					"else {",
					"	head->prev = NULL;",
					"}",
					"delete temp;"
				},
				{	//Remove back
					"",
					"if (tail == NULL) return;",
					"Vertex* temp = tail;",
					"tail = tail->prev;",
					"if (tail == NULL) {",
					"	head = NULL;",
					"}",
					"else {",
					"	tail->next = NULL;",
					"}",
					"delete temp;"
				},
				{	//Remove middle
					"",
					"Vertex* cur = head; int k = 0;",
					"while (cur != NULL) {",
					"	if (k == i - 1) {",
					"		Vertex* aft = cur->next;",
					"		cur->next = aft->next; aft->next->prev = cur",
					"		delete aft;",
					"		return;",
					"	 }",
					"	 k++; cur = cur->next;",
					"}"
				}
			},
			{	//Update
				{	//Update front
					"",
					"if (head == NULL) return;",
					"head->value = v;"
				},
				{	//Update back
					"",
					"if (tail == NULL) return;",
					"tail->value = v;"
				},
				{	//Update middle
					"",
					"Vertex* cur = head; int k = 0;",
					"while (cur != NULL) {",
					"	 if (k == i) {",
					"		cur->value = v;",
					"		return;",
					"	}",
					"	k++; cur = cur->next;",
					"}"
				}
			}
		},
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 3, widthBox * 2, heightBox * 3, font(fontType::Consolas),
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox, font(fontType::Consolas),
		0, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Arial)) {}

int DoublyLinkedList::getSize() {
	return (int)dll.size();
}

int DoublyLinkedList::getHeadValue() {
	return dll[0].value;
}

int DoublyLinkedList::getTailValue() {
	return dll.back().value;
}

int DoublyLinkedList::getHeadID() {
	return dll[0].id;
}

int DoublyLinkedList::getTailID() {
	return dll.back().id;
}

int DoublyLinkedList::getID(int i) {
	return dll[i].id;
}

std::vector <int> DoublyLinkedList::getListID(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(dll[i].id);
	}
	return id;
}

std::vector < std::pair <int, int>> DoublyLinkedList::getEdgeID(int l, int r) {
	std::vector <std::pair <int, int>> edges;
	for (int i = l; i < r; i++) {
		edges.push_back({ dll[i].id, dll[i + 1].id });
		edges.push_back({ dll[i + 1].id, dll[i].id });
	}
	return edges;
}

int DoublyLinkedList::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : dll) {
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

void DoublyLinkedList::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	dll.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	dll.clear();
	std::vector <int> nodeList;
	std::vector <std::pair <int, int> > edgeList;
	std::vector <sf::Color> color;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (5 * n - 5))) / 2;
	double y = HEIGHT_RES / 3;
	std::vector <int> valueList;
	for (int i = 0; i < n; i++) {
		int value = (values.empty() ? rand() % 100 + 1 : values[i]);
		valueList.push_back(value);
	}
	if (sorted) {
		std::sort(valueList.begin(), valueList.end());
	}
	for (int i = 0; i < n; i++) {
		int value = valueList[i];
		dll.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
		nodeList.push_back(i);
		nodeInfo.push_back({ value, x, y });
		x += defaultNode.getRadius() * 5;
		if (i < n - 1) {
			edgeList.push_back({ i, i + 1 });
			edgeList.push_back({ i + 1, i });
			color.push_back({ defaultNode.getOutlineColor() });
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
	addVariables(animationList, { n - 1 }, { "tail" });
	addAnimations(animationList, stepTime, 0, "Created a singly linked list of length " + intToString(n));
	animateAllFrame();
}

void DoublyLinkedList::search(int v) {
	resetAnimation();
	std::vector <Animation> animationList;

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty, so " + intToString(v) + " is not in the list.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty, proceed to next step.");

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur", "i = 0" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Created pointer cur pointing to head and assign i = 0.");
	int i = 0;

	while (true) {
		if (i >= getSize()) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "cur now equals to NULL, we finished traversing the list and now stop the loop.");
			break;
		}
		else {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "cur is not NULL, we have not finished traversing the list.");
			if (dll[i].value == v) {
				animationList.clear();
				setNodeColor(animationList, { getID(i) }, theme, highlight2);
				addAnimations(animationList, stepTime * float(2.0), 4, "Found " + intToString(v) + " at position " + intToString(i) + ". The function stops here");

				animationList.clear();
				deleteVariables(animationList, { getID(i) }, { "cur", "i = " + intToString(i) });
				setNodeColor(animationList, { getListID(0, getSize() - 1) }, theme, normal);
				setEdgeColor(animationList, getEdgeID(0, i), theme, normal);
				addAnimations(animationList, stepTime, 0, "Re-format for visualization.");
				animateAllFrame();
				return;
			}

			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 4, "Value at position " + intToString(i) + " is not " + intToString(v) + ", proceed to next step.");

			animationList.clear();
			deleteVariables(animationList, { getID(i) }, { "cur", "i = " + intToString(i) });
			i++;
			if (i < getSize()) {
				setEdgeColor(animationList, { {getID(i - 1), getID(i)} }, theme, highlight);
				addVariables(animationList, { getID(i) }, { "cur", "i = " + intToString(i) });
				setNodeColor(animationList, { getID(i - 1), getID(i) }, theme, { lowlight, highlight });
				addAnimations(animationList, stepTime, 5, "cur now points to cur->next, i increase by 1.");
			}
			else {
				setNodeColor(animationList, { getID(i - 1) }, theme, lowlight);
				addAnimations(animationList, stepTime, 5, "cur now points to cur->next (which is NULL), i increase by 1.");
			}
		}
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 7, "We finished traversing the list and could not find " + intToString(v) + ", the funtion stops here.");

	animationList.clear();
	setNodeColor(animationList, getListID(0, getSize() - 1), theme, normal);
	setEdgeColor(animationList, { getEdgeID(0, getSize() - 1) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");
	animateAllFrame();
}

void DoublyLinkedList::insertFront(int v) {
	if (getSize() + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	Node defaultNode = defaultGraph.getDefaultNode();
	int id = getEmptyID();
	resetAnimation();
	std::vector <Animation> animationList;

	if (getSize() == 0) {
		animationList.clear();
		addNode(animationList, id, v, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		addVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 1, "Created new vertex vtx storing value " + intToString(v) + ".");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "List is currently empty (head == NULL), so the condition is true");

		animationList.clear();
		addVariables(animationList, { id }, { "head", "tail" });
		addAnimations(animationList, stepTime, 3, "Both head and tail will now points to vtx.");

		animationList.clear();
		doNothing(animationList);
		deleteVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 4, "The function stops here.");

		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-format for visualization");
		dll.insert(dll.begin(), { id, v, -1 });

		animateAllFrame();
		return;
	}

	animationList.clear();
	addNode(animationList, id, v, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 - 5 * defaultNode.getRadius(), HEIGHT_RES / 3);
	setNodeColor(animationList, { id }, theme, highlight);
	addVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 1, "Created new vertex vtx storing value " + intToString(v) + ".");

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 2, "List is currently not empty (head != NULL), so the condition is false and we proceed to next step.");

	animationList.clear();
	addEdge(animationList, { {id, getHeadID()}, {getHeadID(), id} }, theme, highlight);
	addAnimations(animationList, stepTime, 6, "vtx->next now points to head, while head->prev points to vtx");

	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	deleteVariables(animationList, { getHeadID() }, { "head" });
	addVariables(animationList, { id }, { "head" });
	setEdgeColor(animationList, { {id, getHeadID()} , {getHeadID(), id}}, theme, normal);
	addAnimations(animationList, stepTime, 7, "head now points to vtx");

	animationList.clear();
	translateNode(animationList, getListID(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	dll.insert(dll.begin(), { id, v, getHeadID() });
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void DoublyLinkedList::insertBack(int v) {
	if (getSize() + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	int id = getEmptyID();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();
	resetAnimation();
	if (getSize() == 0) {
		animationList.clear();
		addNode(animationList, id, v, WIDTH_RES / 2, HEIGHT_RES / 3);
		setNodeColor(animationList, { id }, theme, highlight);
		addVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 1, "Created new vertex vtx storing value " + intToString(v) + ".");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "List is currently empty (head == NULL), so the condition is true");

		animationList.clear();
		addVariables(animationList, { id }, { "head", "tail" });
		addAnimations(animationList, stepTime, 3, "Both head and tail will now points to vtx.");

		animationList.clear();
		doNothing(animationList);
		deleteVariables(animationList, { id }, { "vtx" });
		addAnimations(animationList, stepTime, 4, "The function stops here.");

		animationList.clear();
		setNodeColor(animationList, { id }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-format for visualization");
		dll.insert(dll.begin(), { id, v, -1 });

		animateAllFrame();
		return;
	}

	animationList.clear();
	addNode(animationList, id, v, WIDTH_RES - (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * defaultNode.getRadius(), HEIGHT_RES / 3);
	setNodeColor(animationList, { id }, theme, highlight);
	addVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 1, "Created new vertex vtx storing value " + intToString(v) + ".");

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 2, "List is currently not empty (head != NULL), so the condition is false and we proceed to next step.");

	animationList.clear();
	addEdge(animationList, { {getTailID(), id}, {id, getTailID()}}, theme, highlight);
	addAnimations(animationList, stepTime, 6, "tail->next now points to vtx, while vtx->prev now points to tail");

	animationList.clear();
	deleteVariables(animationList, { getTailID() }, { "tail" });
	addVariables(animationList, { id }, { "tail" });
	setEdgeColor(animationList, { {getTailID(), id}, {id, getTailID()}}, theme, normal);
	setNodeColor(animationList, { id }, theme, highlight2);
	dll.back().dNext = id;
	addAnimations(animationList, stepTime, 7, "tail now points to vtx");

	animationList.clear();
	translateNode(animationList, getListID(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	dll.push_back({ id, v, -1 });
	moveNode(animationList, id, WIDTH_RES - (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void DoublyLinkedList::insertMiddle(int i, int v) {
	if (getSize() + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (getSize() < 2) {
		setError(true, "There is no position in the middle!");
		return;
	}
	if (i < 1 || i > getSize() - 1) {
		setError(true, "i must be in [1, " + intToString(getSize() - 1) + "]!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	int id = getEmptyID();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();
	resetAnimation();

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur", "k = 0" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 1, "Created new pointer cur points to head and assign k = 0");

	int k = 0;
	while (true) {
		if (k >= getSize()) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 2, "cur is NULL, so the loop stop and we finished traversing the list.");
			break;
		}
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "cur is not NULL, so the loop continues.");

		if (k == i - 1) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "k equals to " + intToString(i - 1) + ", so the condition is true.");

			animationList.clear();
			addNode(animationList, id, v, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * i * defaultNode.getRadius(), HEIGHT_RES / 2);
			setNodeColor(animationList, { id }, theme, highlight2);
			addVariables(animationList, { id }, { "vtx" });
			addAnimations(animationList, stepTime, 4, "Created new vertex vtx storing value " + intToString(v) + ".");

			animationList.clear();
			setNodeColor(animationList, { getID(i) }, theme, highlight3);
			addVariables(animationList, { getID(i) }, { "aft" });
			setEdgeColor(animationList, { {getID(i - 1), getID(i)} }, theme, highlight3);
			addAnimations(animationList, stepTime, 5, "Created new pointer aft pointing to cur->next.");

			animationList.clear();
			switchEdge(animationList, { {getID(i - 1), getID(i), id} });
			addEdge(animationList, { {id, getID(i - 1)} }, theme, highlight2);
			addAnimations(animationList, stepTime, 6, "cur->next now points to vtx, while vtx->prev points to cur.");

			animationList.clear();
			switchEdge(animationList, { {getID(i), getID(i - 1), id} });
			addEdge(animationList, { {id, getID(i)} }, theme, highlight3);
			addAnimations(animationList, stepTime, 7, "vtx->next now points to aft, while aft->prev points to vtx.");

			animationList.clear();
			deleteVariables(animationList, { id }, { "vtx" });
			deleteVariables(animationList, { getID(i - 1) }, { "cur" });
			deleteVariables(animationList, { getID(i) }, { "aft" });
			deleteVariables(animationList, { getID(k) }, { "k = " + intToString(k) });
			dll[i - 1].dNext = id;
			dll.insert(dll.begin() + i, { id, v, dll[i].id });
			setNodeColor(animationList, getListID(0, getSize() - 1), theme, normal);
			setEdgeColor(animationList, getEdgeID(0, i + 1), theme, normal);
			addAnimations(animationList, stepTime, 8, "The function stops here.");
			break;
		}
		else {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "k does not equal to " + intToString(i - 1) + " (k = " + intToString(k) + ") , so the condition is false.");

			animationList.clear();
			deleteVariables(animationList, { getID(k) }, { "cur", "k = " + intToString(k) });
			k++;
			setEdgeColor(animationList, { {getID(k - 1), getID(k)} }, theme, highlight);
			addVariables(animationList, { getID(k) }, { "cur", "k = " + intToString(k) });
			setNodeColor(animationList, { getID(k - 1), getID(k) }, theme, { lowlight, highlight });
			addAnimations(animationList, stepTime, 10, "cur now points to cur->next, k increase by 1.");
		}
	}
	animationList.clear();
	translateNode(animationList, getListID(i + 1, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * i * defaultNode.getRadius(), HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	translateNode(animationList, getListID(0, i - 1), -2.5f * defaultNode.getRadius(), 0);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void DoublyLinkedList::removeFront() {
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();
	resetAnimation();

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty (head == NULL), the function stops here.");
		animateAllFrame();
		return;
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty (head != NULL), proceed to the next step.");

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "temp" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Created pointer temp pointing to head");

	if (getSize() == 1) {
		animationList.clear();
		deleteVariables(animationList, { getHeadID() }, { "head" });
		addAnimations(animationList, stepTime, 3, "head now points to head->next, which is NULL.");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "head is now NULL, so the condtion is true.");

		animationList.clear();
		deleteVariables(animationList, { getTailID() }, { "tail" });
		addAnimations(animationList, stepTime, 5, "head is now NULL (empty list), so tail is now also NULL");
	}
	else {
		animationList.clear();
		deleteVariables(animationList, { getHeadID() }, { "head" });
		addVariables(animationList, { getID(1) }, { "head" });
		setNodeColor(animationList, { getID(1) }, theme, highlight2);
		setEdgeColor(animationList, { {getHeadID(), getID(1)} }, theme, highlight2);
		addAnimations(animationList, stepTime, 3, "head now points to head->next");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "head is not NULL, so the condition is false.");

		animationList.clear();
		deleteEdge(animationList, { {getID(1), getHeadID()} });
		addAnimations(animationList, stepTime, 8, "head->prev now points to NULL.");
	}
	animationList.clear();
	deleteNode(animationList, { getHeadID() });
	addAnimations(animationList, stepTime, 10, "delete temp");

	dll.erase(dll.begin());
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		translateNode(animationList, getListID(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 0, "Re-format for visualization");
	}
	animateAllFrame();
}

void DoublyLinkedList::removeBack() {
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();
	resetAnimation();

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty (tail == NULL), the function stops here.");
		animateAllFrame();
		return;
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty (tail != NULL), proceed to the next step.");

	animationList.clear();
	addVariables(animationList, { getTailID() }, { "temp" });
	setNodeColor(animationList, { getTailID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Created pointer temp pointing to head");

	if (getSize() == 1) {
		animationList.clear();
		deleteVariables(animationList, { getTailID() }, { "tail" });
		addAnimations(animationList, stepTime, 3, "tail now points to tail->prev, which is NULL.");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "tail is now NULL, so the condtion is true.");

		animationList.clear();
		deleteVariables(animationList, { getHeadID() }, { "head" });
		addAnimations(animationList, stepTime, 5, "tail is now NULL (empty list), so head is now also NULL");
	}
	else {
		animationList.clear();
		deleteVariables(animationList, { getTailID() }, { "tail" });
		addVariables(animationList, { getID(getSize() - 2) }, { "tail" });
		setNodeColor(animationList, { getID(getSize() - 2) }, theme, highlight2);
		setEdgeColor(animationList, { {getTailID(), getID(getSize() - 2)} }, theme, highlight2);
		addAnimations(animationList, stepTime, 3, "tail now points to tail->prev");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "tail is not NULL, so the condition is false.");

		animationList.clear();
		deleteEdge(animationList, { {getID(getSize() - 2), getTailID()} });
		addAnimations(animationList, stepTime, 8, "tail->next now points to NULL.");
	}
	animationList.clear();
	deleteNode(animationList, { getTailID() });
	addAnimations(animationList, stepTime, 10, "delete temp");

	dll.erase(dll.begin() + getSize() - 1);
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getTailID() }, theme, normal);
		translateNode(animationList, getListID(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 0, "Re-format for visualization");
	}
	animateAllFrame();
	std::queue <int> q;
}

void DoublyLinkedList::removeMiddle(int i) {
	if (getSize() < 3) {
		setError(true, "There is no position in the middle!");
		return;
	}
	if (i < 1 || i > getSize() - 2) {
		setError(true, "i must be in [1, " + intToString(getSize() - 2) + "]!");
		return;
	}
	resetAnimation();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur", "k = 0" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 1, "Created pointer cur pointing to head and assign k = 0.");
	int k = 0;

	while (true) {
		if (k >= getSize()) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 2, "cur now equals to NULL, we finished traversing the list and now stop the loop.");
			break;
		}
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 2, "cur is not NULL, we have not finished traversing the list.");
		if (k == i - 1) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 3, "k equals to i - 1 (k == i - 1 == " + intToString(i - 1) + "), so the condition is true.");

			animationList.clear();
			addVariables(animationList, { getID(i) }, { "aft" });
			setNodeColor(animationList, { getID(i) }, theme, highlight2);
			moveNode(animationList, getID(i), (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * i * defaultNode.getRadius(), HEIGHT_RES / 2);
			addAnimations(animationList, stepTime, 4, "Created pointer aft pointing to cur->next.");

			animationList.clear();
			switchEdge(animationList, { {getID(i - 1), getID(i), getID(i + 1)}, { getID(i + 1), getID(i), getID(i - 1) } });
			setNodeColor(animationList, { getID(i + 1) }, theme, highlight3);
			addAnimations(animationList, stepTime, 5, "cur->next now points to aft->next, while aft->next->prev now points to cur");

			animationList.clear();
			deleteNode(animationList, getID(i));
			translateNode(animationList, getListID(i + 1, getSize() - 1), -2.5 * defaultNode.getRadius(), 0);
			translateNode(animationList, getListID(0, i - 1), 2.5 * defaultNode.getRadius(), 0);
			mergeMoveNode(animationList);
			addAnimations(animationList, stepTime, 6, "delete aft");

			animationList.clear();
			setNodeColor(animationList, getListID(0, i + 1), theme, normal);
			setEdgeColor(animationList, getEdgeID(0, i + 1), theme, normal);
			deleteVariables(animationList, { getID(k) }, { "k = " + intToString(k), "cur" });
			addAnimations(animationList, stepTime, 7, "The function stops here.");

			dll.erase(dll.begin() + i);
			animateAllFrame();

			
			return;
		}
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 3, "k does not equal to i - 1, so the condition is false.");

		animationList.clear();
		deleteVariables(animationList, { getID(k) }, { "k = " + intToString(k), "cur" });
		addVariables(animationList, { getID(k + 1) }, { "k = " + intToString(k + 1), "cur" });
		setNodeColor(animationList, { getID(k), getID(k + 1) }, theme, { lowlight, highlight });
		setEdgeColor(animationList, { { getID(k), getID(k + 1) } }, theme, highlight);
		addAnimations(animationList, stepTime, 9, "cur now points to cur->next, increase k by 1.");
		k++;
	}

	animationList.clear();
	setNodeColor(animationList, getListID(0, getSize() - 1), theme, normal);
	setEdgeColor(animationList, { getEdgeID(0, getSize() - 1) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");
	animateAllFrame();
}

void DoublyLinkedList::updateFront(int v) {
	resetAnimation();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty. No action is performed.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty. Proceed to next step.");

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	setNodeValue(animationList, { getHeadID() }, { v });
	addAnimations(animationList, stepTime, 2, "head->value is now updated to " + intToString(v) + ".");
	dll[0].value = v;

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void DoublyLinkedList::updateBack(int v) {
	resetAnimation();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();

	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty. No action is performed.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty. Proceed to next step.");

	animationList.clear();
	setNodeColor(animationList, { getTailID() }, theme, highlight);
	setNodeValue(animationList, { getTailID() }, { v });
	addAnimations(animationList, stepTime, 2, "head->value is now updated to " + intToString(v) + ".");
	dll.back().value = v;

	animationList.clear();
	setNodeColor(animationList, { getTailID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void DoublyLinkedList::updateMiddle(int i, int v) {
	if (getSize() < 3) {
		setError(true, "There is no position in the middle!");
		return;
	}
	if (i < 1 || i > getSize() - 2) {
		setError(true, "i must be in [1, " + intToString(getSize() - 2) + "]!");
		return;
	}
	resetAnimation();
	std::vector <Animation> animationList;
	Node defaultNode = defaultGraph.getDefaultNode();

	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur", "k = 0" });
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 1, "Create pointer cur pointing to head and assign k = 0.");

	int k = 0;
	while (true) {
		if (k >= getSize()) {
			animationList.clear();
			setNodeColor(animationList, getListID(0, i), theme, normal);
			setEdgeColor(animationList, getEdgeID(0, i), theme, normal);
			addAnimations(animationList, stepTime, 2, "We have finished traversed the list (cur == NULL). The loop stops here.");
			animateAllFrame();
			break;
		}
		else {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 2, "We have not finished traversed the list (cur != NULL). The loop continues.");
			animateAllFrame();
			if (k == i) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 3, "k == i == " + intToString(i) + ", so the condition is true. We found the position " + intToString(i) + ".");

				animationList.clear();
				setNodeColor(animationList, { getID(i) }, theme, highlight2);
				setNodeValue(animationList, { getID(i) }, { v });
				addAnimations(animationList, stepTime, 4, "cur->value is now updated to " + intToString(v) + ".");

				animationList.clear();
				setNodeColor(animationList, getListID(0, i), theme, normal);
				setEdgeColor(animationList, getEdgeID(0, i), theme, normal);
				deleteVariables(animationList, { getID(i) }, { "cur", "k = " + intToString(k) });
				addAnimations(animationList, stepTime, 5, "The function stops here.");
				animateAllFrame();
				return;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(k) }, { "cur", "k = " + intToString(k) });
				addVariables(animationList, { getID(k + 1) }, { "cur", "k = " + intToString(k + 1) });
				if (k + 1 < getSize()) {
					setNodeColor(animationList, { getID(k), getID(k + 1) }, theme, { lowlight, highlight });
					setEdgeColor(animationList, { {getID(k), getID(k + 1)} }, theme, highlight);
				}
				addAnimations(animationList, stepTime, 7, "cur now points to cur->next and increase k by 1.");
				k++;
			}
		}
	}
}

void DoublyLinkedList::peekFront() {
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty, no action is performed");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0);

		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty, proceed to next step");

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Return value stored at front of list: " + intToString(dll[0].value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}

void DoublyLinkedList::peekBack() {
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty, no action is performed");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0);

		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "List is not empty, proceed to next step");

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "Return value stored at back of list: " + intToString(dll.back().value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}