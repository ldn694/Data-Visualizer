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
	std::cout << numPointCircle << "\n";
}

int StaticArray::getSize() {
	return (int)arr.size();
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
	arr.clear();
	std::vector <int> nodeList;
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
		arr.push_back({ i, value });
		nodeList.push_back(i);
		nodeInfo.push_back({ value, x, y });
		x += defaultNode.getRadius() * 5;
	}
	std::vector <Animation> animationList;
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = nodeList;
	tmp.work.nodeInfos = nodeInfo;
	animationList.push_back(tmp);
	addVariables(animationList, { 0 }, { "head" });
	addVariables(animationList, { n - 1 }, { "tail" });
	for (int i = 0; i < n; i++) {
		addVariables(animationList, { i }, { intToString(i) });
	}
	addAnimations(animationList, stepTime, 0, "Created a static array of length " + intToString(n));
	animateAllFrame();
}

void StaticArray::search(int v) {

}

void StaticArray::updateVal(int i, int v) {

}

void StaticArray::access(int i) {

}