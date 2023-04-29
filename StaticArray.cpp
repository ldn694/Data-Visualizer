#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "StaticArray.h"

StaticArray::StaticArray(double radius, double outlineSize, double lineThickness,
	ColorTheme _theme, EdgeType edgeType, sf::Font* _font, int numPointCircle) :
	DataStructure(radius, outlineSize, lineThickness, _theme, edgeType, _font, numPointCircle,
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
			{	//Insert
				{	//Insert front
					"",
					"size++;",
					"for (int i = size - 1; i > 0; i--) {",
					"	a[i] = a[i - 1];",
					"}",
					"a[0] = v;"
				},
				{	//Insert back
					"",
					"size++;",
					"a[size - 1] = v;"
				},
				{	//Insert middle
					"",
					"size++;",
					"for (int k = size - 1; k > 0; k--) {",
					"	a[k] = a[k - 1];",
					"}",
					"a[i] = v;"
				}
			},
			{	//Delete
				{	//Delete front
					"",
					"if (size == 0) return;",
					"for (int i = 0; i < size - 1; i++) {",
					"	a[i] = a[i + 1];",
					"}",
					"size--;",
					"a[size] = 0;"
				},
				{	//Delete back
					"",
					"if (size == 0) return;",
					"size--;",
					"a[size] = 0;"
				},
				{	//Delete middle
					"",
					"for (int k = i; k < size - 1; k++) {",
					"	a[k] = a[k + 1];",
					"}",
					"size--;",
					"a[size] = 0;"
				}
			},
			{	//Search
				{
					"",
					"for (int i = 0; i < size; i++) {",
					"	if (arr[i] == v) return i;",
					"}",
					"return NOT_FOUND;"
				}
			},
			{	//Update
				{
					"",
					"arr[i] = v;"
				}
			}, 
			{	//Access
				{
					"",
					"return arr[i];"
				}
			}
		},
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 3, widthBox * 2, heightBox * 3, font(fontType::Consolas),
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox, font(fontType::Consolas),
		0, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Arial)) {
}

int StaticArray::getSize() {
	return (int)arr.size();
}

int StaticArray::getCapa() {
	return (int)arr.capacity();
}

int StaticArray::getHeadValue() {
	return arr[0].value;
}

int StaticArray::getTailValue() {
	return arr.back().value;
}

int StaticArray::getHeadID() {
	return arr[0].id;
}

int StaticArray::getTailID() {
	return arr.back().id;
}

int StaticArray::getID(int i) {
	return arr[i].id;
}

std::vector <int> StaticArray::getListID(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(arr[i].id);
	}
	return id;
}

int StaticArray::getEmptyID() {
	int id = 0;
	while (true) {
		bool flag = false;
		for (auto& dComp : arr) {
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

void StaticArray::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	arr.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	std::vector <int> nodeList;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (3 * n - 3))) / 2;
	double y = HEIGHT_RES / 3;
	std::vector <int> valueList;
	for (int i = 0; i < n; i++) {
		int value = (values.empty() ? rand() % maxValueData + 1 : values[i]);
		valueList.push_back(value);
	}
	if (sorted) {
		std::sort(valueList.begin(), valueList.end());
	}
	for (int i = 0; i < n; i++) {
		int value = valueList[i];
		arr.push_back({ i, value });
		nodeList.push_back(i);
		nodeInfo.push_back({ value, x, y });
		x += defaultNode.getRadius() * 3;
	}
	std::vector <Animation> animationList;
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = nodeList;
	tmp.work.nodeInfos = nodeInfo;
	animationList.push_back(tmp);
	for (int i = 0; i < n; i++) {
		addVariables(animationList, { i }, { intToString(i) });
	}
	addAnimations(animationList, stepTime, 0, "Created a static array of length " + intToString(n));
	animateAllFrame();
	size = capa = n;
}

void StaticArray::insertFront(int v) {
	resetAnimation();
	if (size + 1 > capa) {
		setError(true, "Maximmum size of " + intToString(capa) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}

	std::vector <Animation> animationList;

	animationList.clear();
}

void StaticArray::insertBack(int v) {
	resetAnimation();
	if (size + 1 > capa) {
		setError(true, "Maximmum size of " + intToString(capa) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	
	std::vector <Animation> animationList;

	animationList.clear();
	setNodeColor(animationList, { getID(size) }, theme, normal);
	addAnimations(animationList, stepTime, 2, "size is increased by 1, now size is " + intToString(size + 1));
	size++;

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1) }, theme, highlight);
	setNodeValue(animationList, { getID(size - 1) }, {v});
	addAnimations(animationList, stepTime, 1, "a[" + intToString(size - 1) + "] is assigned to " + intToString(v) + ".");

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void StaticArray::deleteBack() {
	resetAnimation();
	if (getSize() == 0) {
		std::vector <Animation> animationList;
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "The array is currently empty (size = 0), no operation is performed.");
		animateAllFrame();
		return;
	}
	std::vector <Animation> animationList;

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "The array is currently not empty (size > 0), proceed to next step.");

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1) }, theme, faded);
	size--;
	addAnimations(animationList, stepTime, 2, "size is decrease by 1, now size = " + intToString(size));

	animationList.clear();
	setNodeValue(animationList, { getID(size) }, {0});
	addAnimations(animationList, stepTime, 3, "a[" + intToString(size) + "] is now assigned to 0 (deleted element).");

	animateAllFrame();
}

void StaticArray::search(int v) {

}

void StaticArray::updateVal(int i, int v) {

}

void StaticArray::access(int i) {

}