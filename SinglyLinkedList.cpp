#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "SinglyLinkedList.h"

SinglyLinkedList::SinglyLinkedList(double radius, double outlineSize, double lineThickness,
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
					"vtx->next = head;",
					"head = vtx;"
				},
				{	//Insert back
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"	return;",
					"}",
					"tail->next = vtx;",
					"tail = vtx;"
				},
				{	//Insert middle
					"",
					"Vertex* cur = head; int k = 0;",
					"while (cur != NULL) {",
					"	if (k == i - 1) {",
					"		Vertex* vtx = new Vertex(v);",
					"		Vertex* aft = cur->next;",
					"		cur->next = vtx; vtx->next = aft;",
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
					"if (head == NULL) tail = NULL;",
					"delete temp;"
				},
				{	//Remove back
					"",
					"if (head == NULL) return;",
					"Vertex* cur = head, aft = cur->next;",
					"if (aft == NULL) {",
					"	head = tail = NULL;",
					"	delete(cur);",
					"	return;",
					"}",
					"while (aft->next != NULL) {",
					"	cur = cur->next; aft = aft->next;",
					"}",
					"cur->next = NULL;",
					"delete aft; tail = cur;"
				},
				{	//Remove middle
					"",
					"Vertex* cur = head; int k = 0;",
					"while (cur != NULL) {",
					"	if (k == i - 1) {",
					"		Vertex* aft = cur->next;",
					"		cur->next = aft->next;",
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

int SinglyLinkedList::getSize() {
	return (int)sll.size();
}

int SinglyLinkedList::getHeadValue() {
	return sll[0].value;
}

int SinglyLinkedList::getTailValue() {
	return sll.back().value;
}

int SinglyLinkedList::getHeadID() {
	return sll[0].id;
}

int SinglyLinkedList::getTailID() {
	return sll.back().id;
}

int SinglyLinkedList::getID(int i) {
	return sll[i].id;
}

std::vector <int> SinglyLinkedList::getIDList(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(sll[i].id);
	}
	return id;
}

std::vector < std::pair <int, int>> SinglyLinkedList::getEdgeID(int l, int r) {
	std::vector <std::pair <int, int>> edges;
	for (int i = l; i < r; i++) {
		edges.push_back({ sll[i].id, sll[i + 1].id });
	}
	return edges;
}

int SinglyLinkedList::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : sll) {
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

void SinglyLinkedList::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	sll.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	sll.clear();
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
		sll.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
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
	addVariables(animationList, { n - 1 }, { "tail" });
	addAnimations(animationList, stepTime, 0, "Created a singly linked list of length " + intToString(n));
	animateAllFrame();
}

void SinglyLinkedList::search(int v) {
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
			if (sll[i].value == v) {
				animationList.clear();
				setNodeColor(animationList, { getID(i) }, theme, highlight2);
				addAnimations(animationList, stepTime * float(2.0), 4, "Found " + intToString(v) + " at position " + intToString(i) + ". The function stops here");

				animationList.clear();
				deleteVariables(animationList, { getID(i) }, { "cur", "i = " + intToString(i) });
				setNodeColor(animationList, { getIDList(0, getSize() - 1)}, theme, normal);
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
	setNodeColor(animationList, getIDList(0, getSize() - 1), theme, normal);
	setEdgeColor(animationList, { getEdgeID(0, getSize() - 1) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");
	animateAllFrame();
}

void SinglyLinkedList::insertFront(int v) {
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
		sll.insert(sll.begin(), { id, v, -1 });

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
	addEdge(animationList, { {id, getHeadID()} }, theme, highlight);
	addAnimations(animationList, stepTime, 6, "vtx->next now points to head");

	animationList.clear();
	setNodeColor(animationList, { id }, theme, highlight2);
	deleteVariables(animationList, { getHeadID() }, { "head" });
	addVariables(animationList, { id }, { "head" });
	setEdgeColor(animationList, { {id, getHeadID()}}, theme, normal);
	addAnimations(animationList, stepTime, 7, "head now points to vtx");

	animationList.clear();
	translateNode(animationList, getIDList(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	sll.insert(sll.begin(), { id, v, getHeadID()});
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void SinglyLinkedList::insertBack(int v) {
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
		sll.insert(sll.begin(), { id, v, -1 });

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
	addEdge(animationList, { {getTailID(), id} }, theme, highlight);
	addAnimations(animationList, stepTime, 6, "tail->next now points to vtx.");

	animationList.clear();
	deleteVariables(animationList, { getTailID() }, { "tail" });
	addVariables(animationList, { id }, { "tail" });
	setEdgeColor(animationList, { {getTailID(), id} }, theme, normal);
	setNodeColor(animationList, { id }, theme, highlight2);
	sll.back().dNext = id;
	addAnimations(animationList, stepTime, 7, "tail now points to vtx");

	animationList.clear();
	translateNode(animationList, getIDList(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	sll.push_back({ id, v, -1 });
	moveNode(animationList, id, WIDTH_RES - (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void SinglyLinkedList::insertMiddle(int i, int v) {
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
	addVariables(animationList, { getHeadID() }, { "cur", "k = 0"});
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
			addEdge(animationList, {{id, getID(i)}}, theme, highlight2);
			addAnimations(animationList, stepTime, 6, "cur->next now points to vtx while vtx->next points to aft.");

			animationList.clear();
			deleteVariables(animationList, { id }, { "vtx" });
			deleteVariables(animationList, { getID(i - 1) }, { "cur" });
			deleteVariables(animationList, { getID(i) }, { "aft" });
			deleteVariables(animationList, { getID(k) }, { "k = " + intToString(k) });
			sll[i - 1].dNext = id;
			sll.insert(sll.begin() + i, { id, v, sll[i].id });
			setNodeColor(animationList, getIDList(0, getSize() - 1), theme, normal);
			setEdgeColor(animationList, getEdgeID(0, getSize() - 1), theme, normal);
			addAnimations(animationList, stepTime, 7, "The function stops here.");
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
			addAnimations(animationList, stepTime, 9, "cur now points to cur->next, k increase by 1.");
		}
	}
	animationList.clear();
	translateNode(animationList, getIDList(i + 1, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * i * defaultNode.getRadius(), HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	translateNode(animationList, getIDList(0, i - 1), -2.5f * defaultNode.getRadius(), 0);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void SinglyLinkedList::removeBack() {
	resetAnimation();
	std::vector <Animation> animationList;
	if (getSize() == 0) {
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "List is empty, no action is performed");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0);

		animateAllFrame();
		return;
	}
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "sll is not empty, proceed to next step");
	animationList.clear();
	int head = getHeadID();
	Node defaultNode = defaultGraph.getDefaultNode();
	if (getSize() == 1) {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "Created new pointer temp pointing to head");

		animationList.clear();
		deleteVariables(animationList, { head }, { "head" });
		addAnimations(animationList, stepTime, 3, "head->next is null, so head is now also null (empty list)");

		animationList.clear();
		doNothing(animationList);
		deleteVariables(animationList, { head }, { "tail" });
		addAnimations(animationList, stepTime, 4, "List is now empty, so tail is also null");

		animationList.clear();
		deleteNode(animationList, head);
		addAnimations(animationList, stepTime, 5, "Delete temp, the list is empty");

		animationList.clear();
		setNodeColor(animationList, { head }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	}
	else {
		setNodeColor(animationList, { head }, theme, highlight);
		addVariables(animationList, { head }, { "temp" });
		addAnimations(animationList, stepTime, 2, "Created new pointer temp pointing to head");

		animationList.clear();
		setEdgeColor(animationList, { {head, sll[1].id} }, theme, highlight2);
		setNodeColor(animationList, { sll[1].id }, theme, highlight2);
		deleteVariables(animationList, { head }, { "head" });
		addVariables(animationList, { sll[1].id }, { "head" });
		addAnimations(animationList, stepTime, 3, "head now points to head->next");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 4, "List is not empty (head != null), proceed to next step");

		animationList.clear();
		deleteNode(animationList, head);
		translateNode(animationList, getIDList(1, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 5, "delete temp");
	}
	sll.erase(sll.begin());
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	}
	animateAllFrame();
}

void SinglyLinkedList::peekFront() {
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
	addAnimations(animationList, stepTime, 2, "Return value stored at front of list: " + intToString(sll[0].value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}

void SinglyLinkedList::peekBack() {
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
	addAnimations(animationList, stepTime, 2, "Return value stored at back of list: " + intToString(sll.back().value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}