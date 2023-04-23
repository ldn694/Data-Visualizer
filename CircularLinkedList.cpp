#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "CircularLinkedList.h"

CircularLinkedList::CircularLinkedList(double radius, double outlineSize, double lineThickness,
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
					"	vtx->next = head",
					"	return;",
					"}",
					"vtx->next = head;",
					"tail->next = vtx;",
					"head = vtx;"
				},
				{	//Insert back
					"",
					"Vertex* vtx = new Vertex(v);",
					"if (head == NULL) {",
					"	head = tail = vtx;",
					"	vtx->next = head",
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
					"	delete cur;",
					"	return;",
					"}",
					"while (aft->next != NULL) {",
					"	cur = cur->next; aft = aft->next;",
					"}",
					"delete aft; tail = cur;",
					"cur->next = NULL;"
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

int CircularLinkedList::getSize() {
	return (int)cll.size();
}

int CircularLinkedList::getHeadValue() {
	return cll[0].value;
}

int CircularLinkedList::getTailValue() {
	return cll.back().value;
}

int CircularLinkedList::getHeadID() {
	return cll[0].id;
}

int CircularLinkedList::getTailID() {
	return cll.back().id;
}

int CircularLinkedList::getID(int i) {
	return cll[i].id;
}

std::vector <int> CircularLinkedList::getListID(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(cll[i].id);
	}
	return id;
}

std::vector < std::pair <int, int>> CircularLinkedList::getEdgeID(int l, int r) {
	std::vector <std::pair <int, int>> edges;
	for (int i = l; i < r; i++) {
		edges.push_back({ cll[i].id, cll[i + 1].id });
	}
	return edges;
}

int CircularLinkedList::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : cll) {
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

void CircularLinkedList::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	cll.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	cll.clear();
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
		cll.push_back({ i, value,  (i < n - 1 ? i + 1 : -1) });
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
	addCircularEdge(animationList, { {n - 1, 0} }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Created a singly linked list of length " + intToString(n));
	animateAllFrame();
}

void CircularLinkedList::search(int v) {
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
			if (cll[i].value == v) {
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

void CircularLinkedList::insertFront(int v) {
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
		cll.insert(cll.begin(), { id, v, -1 });

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
	setEdgeColor(animationList, { {id, getHeadID()} }, theme, normal);
	addAnimations(animationList, stepTime, 7, "head now points to vtx");

	animationList.clear();
	translateNode(animationList, getListID(0, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	cll.insert(cll.begin(), { id, v, getHeadID() });
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void CircularLinkedList::insertBack(int v) {
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
		cll.insert(cll.begin(), { id, v, -1 });

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
	cll.back().dNext = id;
	addAnimations(animationList, stepTime, 7, "tail now points to vtx");

	animationList.clear();
	translateNode(animationList, getListID(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
	cll.push_back({ id, v, -1 });
	moveNode(animationList, id, WIDTH_RES - (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2, HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	setNodeColor(animationList, { id }, theme, normal);
	deleteVariables(animationList, { id }, { "vtx" });
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void CircularLinkedList::insertMiddle(int i, int v) {
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
			addEdge(animationList, { {id, getID(i)} }, theme, highlight2);
			addAnimations(animationList, stepTime, 6, "cur->next now points to vtx while vtx->next points to aft.");

			animationList.clear();
			deleteVariables(animationList, { id }, { "vtx" });
			deleteVariables(animationList, { getID(i - 1) }, { "cur" });
			deleteVariables(animationList, { getID(i) }, { "aft" });
			deleteVariables(animationList, { getID(k) }, { "k = " + intToString(k) });
			cll[i - 1].dNext = id;
			cll.insert(cll.begin() + i, { id, v, cll[i].id });
			setNodeColor(animationList, getListID(0, getSize() - 1), theme, normal);
			setEdgeColor(animationList, getEdgeID(0, i + 1), theme, normal);
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
	translateNode(animationList, getListID(i + 1, getSize() - 1), 2.5f * defaultNode.getRadius(), 0);
	moveNode(animationList, id, (WIDTH_RES - (defaultNode.getRadius() * (5 * getSize() - 5))) / 2 + 5 * i * defaultNode.getRadius(), HEIGHT_RES / 3);
	mergeMoveNode(animationList);
	translateNode(animationList, getListID(0, i - 1), -2.5f * defaultNode.getRadius(), 0);
	mergeMoveNode(animationList);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");
	animateAllFrame();
}

void CircularLinkedList::removeFront() {
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
		deleteVariables(animationList, { getTailID() }, { "tail" });
		addAnimations(animationList, stepTime, 4, "head is now NULL (empty list), so tail is now also NULL");
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
		addAnimations(animationList, stepTime, 4, "head is not NULL, so the condition is false. Proceed to next step");
	}
	animationList.clear();
	deleteNode(animationList, { getHeadID() });
	addAnimations(animationList, stepTime, 5, "delete temp");

	cll.erase(cll.begin());
	if (getSize() > 0) {
		animationList.clear();
		setNodeColor(animationList, { getHeadID() }, theme, normal);
		translateNode(animationList, getListID(0, getSize() - 1), -2.5f * defaultNode.getRadius(), 0);
		addAnimations(animationList, stepTime, 0, "Re-format for visualization");
	}
	animateAllFrame();
}

void CircularLinkedList::removeBack() {
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

	if (getSize() == 1) {
		animationList.clear();
		addVariables(animationList, { getHeadID() }, { "cur" });
		setNodeColor(animationList, { getHeadID() }, theme, highlight);
		addAnimations(animationList, stepTime, 2, "Created 2 pointer cur, aft. cur points to head while aft points to head->next (which is NULL).");

		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 3, "aft is NULL, so the condition is true");

		animationList.clear();
		deleteVariables(animationList, { getHeadID() }, { "head", "tail" });
		addAnimations(animationList, stepTime, 4, "head and tail now both point to NULL (empty list)");

		animationList.clear();
		deleteNode(animationList, { getHeadID() });
		addAnimations(animationList, stepTime, 5, "delete cur");

		animationList.clear();
		doNothing(animationList);
		cll.pop_back();
		addAnimations(animationList, stepTime, 6, "The function stops here. The list is now empty.");

		animateAllFrame();
		return;
	}
	animationList.clear();
	addVariables(animationList, { getHeadID() }, { "cur" });
	setNodeColor(animationList, { getHeadID(), getID(1) }, theme, { highlight, highlight2 });
	addVariables(animationList, { getID(1) }, { "aft" });
	setEdgeColor(animationList, { {getHeadID(), getID(1)} }, theme, highlight2);
	addAnimations(animationList, stepTime, 2, "Created 2 pointer cur, aft. cur points to head while aft points to head->next.");

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 3, "aft is not NULL, so the condition is false.");

	int i = 0;
	while (true) {
		if (i + 2 >= getSize()) {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 8, "aft->next is NULL (aft == tail), so the condition is false and the loop stops.");
			break;
		}
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 8, "aft->next is not NULL, so the condition is true and the loop continues.");

		animationList.clear();
		deleteVariables(animationList, { getID(i) }, { "cur" });
		deleteVariables(animationList, { getID(i + 1) }, { "aft" });
		addVariables(animationList, { getID(i + 1) }, { "cur" });
		addVariables(animationList, { getID(i + 2) }, { "aft" });
		setNodeColor(animationList, { getID(i), getID(i + 1), getID(i + 2) }, theme, { lowlight, highlight, highlight2 });
		setEdgeColor(animationList, { {getID(i), getID(i + 1)}, {getID(i + 1), getID(i + 2)} }, theme, { highlight, normal });
		addAnimations(animationList, stepTime, 9, "cur points to cur->next, aft points to aft->next.");
		i++;
	}
	animationList.clear();
	deleteNode(animationList, { getTailID() });
	translateNode(animationList, getListID(0, getSize() - 1), 2.5 * defaultNode.getRadius(), 0);
	addVariables(animationList, { getID(getSize() - 2) }, { "tail" });
	addAnimations(animationList, stepTime, 11, "delete aft, tail now points to cur.");

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 12, "cur->next (which is now also tail->next) now points to NULL.");
	cll.pop_back();
	cll.back().dNext = -1;

	animationList.clear();
	setNodeColor(animationList, getListID(0, getSize() - 1), theme, normal);
	setEdgeColor(animationList, getEdgeID(0, getSize() - 1), theme, normal);
	deleteVariables(animationList, { getTailID() }, { "cur" });
	addAnimations(animationList, stepTime, 0, "Re-format for visualizing.");

	animateAllFrame();
}

void CircularLinkedList::removeMiddle(int i) {
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
			switchEdge(animationList, { {getID(i - 1), getID(i), getID(i + 1)} });
			setNodeColor(animationList, { getID(i + 1) }, theme, highlight3);
			addAnimations(animationList, stepTime, 5, "cur->next now points to aft->next");

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

			cll.erase(cll.begin() + i);

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

void CircularLinkedList::updateFront(int v) {
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
	cll[0].value = v;

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void CircularLinkedList::updateBack(int v) {
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
	cll.back().value = v;

	animationList.clear();
	setNodeColor(animationList, { getTailID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void CircularLinkedList::updateMiddle(int i, int v) {
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

void CircularLinkedList::peekFront() {
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
	addAnimations(animationList, stepTime, 2, "Return value stored at front of list: " + intToString(cll[0].value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}

void CircularLinkedList::peekBack() {
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
	addAnimations(animationList, stepTime, 2, "Return value stored at back of list: " + intToString(cll.back().value));

	animationList.clear();
	setNodeColor(animationList, { getHeadID() }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-layout for visualization");

	animateAllFrame();
}