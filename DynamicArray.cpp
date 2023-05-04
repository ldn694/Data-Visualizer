#pragma once

#include <iostream>
#include <vector>
#include "Template.h"
#include "DynamicArray.h"

DynamicArray::DynamicArray(double radius, double outlineSize, double lineThickness,
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
			{	//Allocate
				{
					"",
					"int* a = new a[n];",
					"size = n;"
				}
			},
			{	//Insert
				{	//Insert front
					"",
					"int* b = new b[++size];",
					"for (int i = 1; i < size; i++) {",
					"	b[i] = a[i - 1];",
					"}",
					"b[0] = v;",
					"delete[] a;",
					"a = b;"
				},
				{	//Insert back
					"",
					"int* b = new b[++size];",
					"for (int i = 0; i < size - 1; i++) {",
					"	b[i] = a[i];",
					"}",
					"b[size - 1] = v;",
					"delete[] a;",
					"a = b;"
				},
				{	//Insert middle
					"",
					"int* b = new b[++size];",
					"for (int k = 0; k < i; k++) {",
					"	b[k] = a[k];",
					"}",
					"b[i] = v;",
					"for (int k = i + 1; k < size; k++) {",
					"	b[k] = a[k - 1];",
					"}",
					"delete[] a;",
					"a = b;"
				}
			},
			{	//Delete
				{	//Delete front
					"",
					"if (size == 0) return;",
					"int* b = new b[--size];",
					"for (int i = 0; i < size; i++) {",
					"	b[i] = a[i + 1];",
					"}",
					"delete[] a;",
					"a = b;"
				},
				{	//Delete back
					"",
					"if (size == 0) return;",
					"int* b = new b[--size];",
					"for (int i = 0; i < size; i++) {",
					"	b[i] = a[i];",
					"}",
					"delete[] a;",
					"a = b;"
				},
				{	//Delete middle
					"",
					"int* b = new b[--size];",
					"for (int k = 0; k < i; k++) {",
					"	b[k] = a[k];",
					"}",
					"for (int k = i; k < size; k++) {",
					"	b[k] = a[k + 1];",
					"}",
					"delete[] a;",
					"a = b;"
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
					"if (i < 0 || i >= size) return;",
					"arr[i] = v;"
				}
			},
			{	//Access
				{
					"",
					"if (i < 0 || i >= size) return;",
					"return arr[i];"
				}
			}
		},
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 3, widthBox * 2, heightBox * 3, font(fontType::Consolas),
		WIDTH_RES - widthBox * 2, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox, font(fontType::Consolas),
		0, HEIGHT_RES - heightBox * 4, widthBox * 2, heightBox, font(fontType::Arial)) {
	size = 0;
}

int DynamicArray::getSize() {
	return (int)arr.size();
}

int DynamicArray::getCapa() {
	return (int)arr.capacity();
}

int DynamicArray::getHeadValue() {
	return arr[0].value;
}

int DynamicArray::getTailValue() {
	return arr.back().value;
}

int DynamicArray::getValue(int i) {
	return arr[i].value;
}

int DynamicArray::getHeadID() {
	return arr[0].id;
}

int DynamicArray::getTailID() {
	return arr.back().id;
}

int DynamicArray::getID(int i) {
	return arr[i].id;
}

std::vector <int> DynamicArray::getListID(int l, int r) {
	std::vector <int> id;
	for (int i = l; i <= r; i++) {
		id.push_back(arr[i].id);
	}
	return id;
}

int DynamicArray::getEmptyID() {
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

void DynamicArray::createTempArray(std::vector <Animation>& animationList, int size) {
	animationList.clear();
	std::vector <int> nodeList;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (3 * size - 3))) / 2;
	double y = HEIGHT_RES / 2;
	for (int i = 0; i < size; i++) {
		int id = getEmptyID();
		arr.push_back({ id, 0 });
		nodeList.push_back(id);
		nodeInfo.push_back({ 0, x, y });
		x += defaultNode.getRadius() * 3;
		addVariables(animationList, { id }, { intToString(i) });
	}
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = nodeList;
	tmp.work.nodeInfos = nodeInfo;
	animationList.push_back(tmp);
}

void DynamicArray::allocate(int n) {
	arr.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	std::vector <Animation> animationList;
	std::vector <int> nodeList;
	std::vector <std::tuple <int, double, double> > nodeInfo;
	Node defaultNode = defaultGraph.getDefaultNode();
	double x = (WIDTH_RES - (defaultNode.getRadius() * (3 * n - 3))) / 2;
	double y = HEIGHT_RES / 3;
	for (int i = 0; i < n; i++) {
		arr.push_back({ i, 0 });
		nodeList.push_back(i);
		nodeInfo.push_back({ 0, x, y });
		x += defaultNode.getRadius() * 3;
	}
	Animation tmp;
	tmp.type = AddNode;
	tmp.element.nodes = nodeList;
	tmp.work.nodeInfos = nodeInfo;
	animationList.push_back(tmp);
	for (int i = 0; i < n; i++) {
		addVariables(animationList, { i }, { intToString(i) });
	}
	addAnimations(animationList, stepTime, 1, "Allocated new dynamic array of length " + intToString(n));

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 2, "size is now assigned to " + intToString(n));
	size = n;

	animateAllFrame();
}

void DynamicArray::createRandom(int n, std::vector <int> values, bool sorted) {
	if (n == -1) {
		n = rand() % maxSizeData + 1;
	}
	if (!values.empty() && values[0] < 0) {
		return;
	}
	arr.clear();
	mainGraph = defaultGraph;
	resetAnimation();
	if (n == 0) {
		std::vector <Animation> animationList;
		doNothing(animationList);
		addAnimations(animationList, stepTime, 0, "Created a Dynamic Array of length 0");
		animateAllFrame();
		return;
	}
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
	addAnimations(animationList, stepTime, 0, "Created a Dynamic array of length " + intToString(n));
	animateAllFrame();
	size = n;
}

void DynamicArray::insertFront(int v) {
	if (size + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	resetAnimation();

	std::vector <Animation> animationList;
	animationList.clear();
	size++;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 1, "size is increased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int i = 1, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			i++;
		}
		if (i >= size) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 2, "We assign i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size - 1 + i - 1) }, { "i = " + intToString(i - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 2, "i is increased by 1, now i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size - 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size - 1 + i) }, theme, { highlight });
			addAnimations(animationList, stepTime, 2, "We assign i = " + intToString(i) + ", as i < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size - 1 + i - 1) }, { "i = " + intToString(i - 1) });
			addVariables(animationList, { getID(size - 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size - 1 + i), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 2, "i is increased by 1, now i = " + intToString(i) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(i - 1) }, theme, highlight2);
		setNodeValue(animationList, { getID(size - 1 + i) }, { getValue(i - 1) });
		addAnimations(animationList, stepTime, 3, "b[" + intToString(i) + "] is assigned to " + intToString(getValue(i - 1)) + "(= a[" + intToString(i - 1) + "]).");
		arr[size - 1 + i].value = arr[i - 1].value;
		pre = size - 1 + i;
		another_pre = i - 1;
		firstTime = true;
	}

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1) }, theme, highlight);
	setNodeValue(animationList, { getID(size - 1) }, { v });
	addAnimations(animationList, stepTime, 5, "b[0] is now assigned to " + intToString(v) + " (inserted element).");
	arr[size - 1].value = v;

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1) }, theme, normal);
	deleteNode(animationList, getListID(0, size - 2));
	addAnimations(animationList, stepTime, 6, "Delete a.");
	for (int i = 0; i < size - 1; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 7, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::insertBack(int v) {
	if (size + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	resetAnimation();

	std::vector <Animation> animationList;
	animationList.clear();
	size++;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 1, "size is increased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int i = 0, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			i++;
		}
		if (i >= size - 1) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 2, "We assign i = " + intToString(i) + " >= size - 1 (size - 1 = " + intToString(size - 1) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size - 1 + i - 1) }, { "i = " + intToString(i - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 2, "i is increased by 1, now i = " + intToString(i) + " >= size - 1 (size - 1 = " + intToString(size - 1) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size - 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size - 1 + i) }, theme, { highlight });
			addAnimations(animationList, stepTime, 2, "We assign i = " + intToString(i) + ", as i < size - 1 (size - 1 = " + intToString(size - 1) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size - 1 + i - 1) }, { "i = " + intToString(i - 1) });
			addVariables(animationList, { getID(size - 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size - 1 + i), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 2, "i is increased by 1, now i = " + intToString(i) + " < size - 1 (size - 1 = " + intToString(size - 1) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(i) }, theme, highlight2);
		setNodeValue(animationList, { getID(size - 1 + i) }, { getValue(i) });
		addAnimations(animationList, stepTime, 3, "b[" + intToString(i) + "] is assigned to " + intToString(getValue(i)) + "(= a[" + intToString(i) + "]).");
		arr[size - 1 + i].value = arr[i].value;
		pre = size - 1 + i;
		another_pre = i;
		firstTime = true;
	}

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1 + size - 1) }, theme, highlight);
	setNodeValue(animationList, { getID(size - 1 + size - 1) }, { v });
	addAnimations(animationList, stepTime, 5, "b[" + intToString(size - 1) + "] is now assigned to " + intToString(v) + " (inserted element).");
	arr[size - 1 + size - 1].value = v;

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1 + size - 1) }, theme, normal);
	deleteNode(animationList, getListID(0, size - 2));
	addAnimations(animationList, stepTime, 6, "Delete a.");
	for (int i = 0; i < size - 1; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 7, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::insertMiddle(int index, int v) {
	if (size + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (size < 2) {
		setError(true, "There is no position in the middle!");
		return;
	}
	if (index < 1 || index > size - 1) {
		setError(true, "i must be in [1, " + intToString(size - 1) + "]!");
		return;
	}
	if (v < 0) {
		v = rand() % (maxValueData + 1);
	}
	resetAnimation();

	std::vector <Animation> animationList;
	animationList.clear();
	size++;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 1, "size is increased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int k = 0, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			k++;
		}
		if (k >= index) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 2, "We assign k = " + intToString(k) + " >= i (i = " + intToString(index) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size - 1 + k - 1) }, { "k = " + intToString(k - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 2, "k is increased by 1, now k = " + intToString(k) + " >= i (i = " + intToString(index) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size - 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size - 1 + k) }, theme, { highlight });
			addAnimations(animationList, stepTime, 2, "We assign k = " + intToString(k) + ", as k < i (i = " + intToString(index) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size - 1 + k - 1) }, { "k = " + intToString(k - 1) });
			addVariables(animationList, { getID(size - 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size - 1 + k), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 2, "k is increased by 1, now k = " + intToString(k) + " < i (i = " + intToString(index) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(k) }, theme, highlight2);
		setNodeValue(animationList, { getID(size - 1 + k) }, { getValue(k) });
		addAnimations(animationList, stepTime, 3, "b[" + intToString(k) + "] is assigned to " + intToString(getValue(k)) + "(= a[" + intToString(k) + "]).");
		arr[size - 1 + k].value = arr[k].value;
		pre = size - 1 + k;
		another_pre = k;
		firstTime = true;
	}

	animationList.clear();
	setNodeColor(animationList, { getID(size - 1 + index) }, theme, highlight);
	setNodeValue(animationList, { getID(size - 1 + index) }, { v });
	addAnimations(animationList, stepTime, 5, "b[" + intToString(index) + "] is now assigned to " + intToString(v) + " (inserted element).");
	arr[size - 1 + index].value = v;

	k = index + 1; pre = -1; another_pre = -1; firstTime = false;
	while (true) {
		if (firstTime) {
			k++;
		}
		if (k >= size) {
			if (!firstTime) {
				animationList.clear();
				setNodeColor(animationList, { getID(size - 1 + index) }, theme, normal);
				addAnimations(animationList, stepTime, 6, "We assign k = " + intToString(k) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size - 1 + k - 1) }, { "k = " + intToString(k - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 6, "k is increased by 1, now k = " + intToString(k) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			setNodeColor(animationList, { getID(size - 1 + index) }, theme, normal);
			addVariables(animationList, { getID(size - 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size - 1 + k) }, theme, { highlight });
			addAnimations(animationList, stepTime, 6, "We assign k = " + intToString(k) + ", as k < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size - 1 + k - 1) }, { "k = " + intToString(k - 1) });
			addVariables(animationList, { getID(size - 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size - 1 + k), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 6, "k is increased by 1, now k = " + intToString(k) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(k - 1) }, theme, highlight2);
		setNodeValue(animationList, { getID(size - 1 + k) }, { getValue(k - 1) });
		addAnimations(animationList, stepTime, 7, "b[" + intToString(k) + "] is assigned to " + intToString(getValue(k - 1)) + "(= a[" + intToString(k - 1) + "]).");
		arr[size - 1 + k].value = arr[k - 1].value;
		pre = size - 1 + k;
		another_pre = k - 1;
		firstTime = true;
	}

	animationList.clear();
	deleteNode(animationList, getListID(0, size - 2));
	addAnimations(animationList, stepTime, 9, "Delete a.");
	for (int i = 0; i < size - 1; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 10, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::deleteFront() {
	resetAnimation();

	std::vector <Animation> animationList;

	if (size == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "size is 0 (empty array), no operation is perfomred.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "size is not 0, so the function continues.");

	animationList.clear();
	size--;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 2, "size is decreased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int i = 0, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			i++;
		}
		if (i >= size) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 3, "We assign i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size + 1 + i - 1) }, { "i = " + intToString(i - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 3, "i is increased by 1, now i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size + 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size + 1 + i) }, theme, { highlight });
			addAnimations(animationList, stepTime, 3, "We assign i = " + intToString(i) + ", as i < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size + 1 + i - 1) }, { "i = " + intToString(i - 1) });
			addVariables(animationList, { getID(size + 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size + 1 + i), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 3, "i is increased by 1, now i = " + intToString(i) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(i + 1) }, theme, highlight2);
		setNodeValue(animationList, { getID(size + 1 + i) }, { getValue(i + 1) });
		addAnimations(animationList, stepTime, 4, "b[" + intToString(i) + "] is assigned to " + intToString(getValue(i + 1)) + "(= a[" + intToString(i + 1) + "]).");
		arr[size + 1 + i].value = arr[i + 1].value;
		pre = size + 1 + i;
		another_pre = i + 1;
		firstTime = true;
	}

	animationList.clear();
	deleteNode(animationList, getListID(0, size));
	addAnimations(animationList, stepTime, 6, "Delete a.");
	for (int i = 0; i <= size; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 7, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::deleteBack() {
	resetAnimation();

	std::vector <Animation> animationList;

	if (size == 0) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "size is 0 (empty array), no operation is perfomred.");
		animateAllFrame();
		return;
	}

	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "size is not 0, so the function continues.");

	animationList.clear();
	size--;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 2, "size is decreased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int i = 0, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			i++;
		}
		if (i >= size) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 3, "We assign i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size + 1 + i - 1) }, { "i = " + intToString(i - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 3, "i is increased by 1, now i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size + 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size + 1 + i) }, theme, { highlight });
			addAnimations(animationList, stepTime, 3, "We assign i = " + intToString(i) + ", as i < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size + 1 + i - 1) }, { "i = " + intToString(i - 1) });
			addVariables(animationList, { getID(size + 1 + i) }, { "i = " + intToString(i) });
			setNodeColor(animationList, { getID(size + 1 + i), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 3, "i is increased by 1, now i = " + intToString(i) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(i) }, theme, highlight2);
		setNodeValue(animationList, { getID(size + 1 + i) }, { getValue(i) });
		addAnimations(animationList, stepTime, 4, "b[" + intToString(i) + "] is assigned to " + intToString(getValue(i)) + "(= a[" + intToString(i) + "]).");
		arr[size + 1 + i].value = arr[i].value;
		pre = size + 1 + i;
		another_pre = i;
		firstTime = true;
	}

	animationList.clear();
	deleteNode(animationList, getListID(0, size));
	addAnimations(animationList, stepTime, 6, "Delete a.");
	for (int i = 0; i <= size; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 7, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::deleteMiddle(int index) {
	if (size + 1 > maxSizeData) {
		setError(true, "Maximmum size of " + intToString(maxSizeData) + " reached!");
		return;
	}
	if (size < 2) {
		setError(true, "There is no position in the middle!");
		return;
	}
	if (index < 1 || index > size - 1) {
		setError(true, "i must be in [1, " + intToString(size - 1) + "]!");
		return;
	}
	resetAnimation();

	std::vector <Animation> animationList;
	animationList.clear();
	size--;
	createTempArray(animationList, size);
	addAnimations(animationList, stepTime, 1, "size is decreased by 1, now size is " + intToString(size) + ", created new Dynamic Array b of length " + intToString(size) + ".");

	int k = 0, pre = -1, another_pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			k++;
		}
		if (k >= index) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 2, "We assign k = " + intToString(k) + " >= i (i = " + intToString(index) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size + 1 + k - 1) }, { "k = " + intToString(k - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 2, "k is increased by 1, now k = " + intToString(k) + " >= i (i = " + intToString(index) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(size + 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size + 1 + k) }, theme, { highlight });
			addAnimations(animationList, stepTime, 2, "We assign k = " + intToString(k) + ", as k < i (i = " + intToString(index) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size + 1 + k - 1) }, { "k = " + intToString(k - 1) });
			addVariables(animationList, { getID(size + 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size + 1 + k), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 2, "k is increased by 1, now k = " + intToString(k) + " < i (i = " + intToString(index) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(k) }, theme, highlight2);
		setNodeValue(animationList, { getID(size + 1 + k) }, { getValue(k) });
		addAnimations(animationList, stepTime, 3, "b[" + intToString(k) + "] is assigned to " + intToString(getValue(k)) + "(= a[" + intToString(k) + "]).");
		arr[size + 1 + k].value = arr[k].value;
		pre = size + 1 + k;
		another_pre = k;
		firstTime = true;
	}

	k = index; pre = -1; another_pre = -1; firstTime = false;
	while (true) {
		if (firstTime) {
			k++;
		}
		if (k >= size) {
			if (!firstTime) {
				animationList.clear();
				setNodeColor(animationList, { getID(size + 1 + index) }, theme, normal);
				addAnimations(animationList, stepTime, 5, "We assign k = " + intToString(k) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(size + 1 + k - 1) }, { "k = " + intToString(k - 1) });
				setNodeColor(animationList, { getID(pre), getID(another_pre) }, theme, { normal, normal });
				addAnimations(animationList, stepTime, 5, "k is increased by 1, now k = " + intToString(k) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			setNodeColor(animationList, { getID(size + 1 + index) }, theme, normal);
			addVariables(animationList, { getID(size + 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size + 1 + k) }, theme, { highlight });
			addAnimations(animationList, stepTime, 5, "We assign k = " + intToString(k) + ", as k < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(size + 1 + k - 1) }, { "k = " + intToString(k - 1) });
			addVariables(animationList, { getID(size + 1 + k) }, { "k = " + intToString(k) });
			setNodeColor(animationList, { getID(size + 1 + k), getID(pre), getID(another_pre) }, theme, { highlight, normal, normal });
			addAnimations(animationList, stepTime, 5, "k is increased by 1, now k = " + intToString(k) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		animationList.clear();
		setNodeColor(animationList, { getID(k + 1) }, theme, highlight2);
		setNodeValue(animationList, { getID(size + 1 + k) }, { getValue(k + 1) });
		addAnimations(animationList, stepTime, 6, "b[" + intToString(k) + "] is assigned to " + intToString(getValue(k + 1)) + "(= a[" + intToString(k + 1) + "]).");
		arr[size + 1 + k].value = arr[k + 1].value;
		pre = size + 1 + k;
		another_pre = k + 1;
		firstTime = true;
	}

	animationList.clear();
	deleteNode(animationList, getListID(0, size));
	addAnimations(animationList, stepTime, 8, "Delete a.");
	for (int i = 0; i <= size; i++) {
		arr.erase(0);
	}

	animationList.clear();
	translateNode(animationList, getListID(0, size - 1), 0, HEIGHT_RES / 3 - HEIGHT_RES / 2);
	addAnimations(animationList, stepTime, 9, "a now points to b.");

	animateAllFrame();
}

void DynamicArray::search(int v) {
	resetAnimation();
	std::vector <Animation> animationList;

	int i = 0, pre = -1;
	bool firstTime = false;
	while (true) {
		if (firstTime) {
			i++;
		}
		if (i >= size) {
			if (!firstTime) {
				animationList.clear();
				doNothing(animationList);
				addAnimations(animationList, stepTime, 1, "We assign i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
			else {
				animationList.clear();
				deleteVariables(animationList, { getID(i - 1) }, { "i = " + intToString(i - 1) });
				if (pre != -1) {
					setNodeColor(animationList, { getID(pre) }, theme, { normal });
				}
				addAnimations(animationList, stepTime, 1, "i is increased by 1, now i = " + intToString(i) + " >= size (size = " + intToString(size) + "), so the condition is false, therefore the loop breaks here.");
				break;
			}
		}
		if (!firstTime) {
			animationList.clear();
			addVariables(animationList, { getID(i) }, { "i = " + intToString(i) });
			if (pre == -1) {
				setNodeColor(animationList, { getID(i) }, theme, { highlight });
			}
			else {
				setNodeColor(animationList, { getID(i), getID(pre) }, theme, { highlight, normal });
			}
			addAnimations(animationList, stepTime, 1, "We assign i = " + intToString(i) + ", as i < size (size = " + intToString(size) + "), the condition is true and the loop continues.");
		}
		else {
			animationList.clear();
			deleteVariables(animationList, { getID(i - 1) }, { "i = " + intToString(i - 1) });
			addVariables(animationList, { getID(i) }, { "i = " + intToString(i) });
			if (pre == -1) {
				setNodeColor(animationList, { getID(i) }, theme, { highlight });
			}
			else {
				setNodeColor(animationList, { getID(i), getID(pre) }, theme, { highlight, normal });
			}
			addAnimations(animationList, stepTime, 1, "i is increased by 1, now i = " + intToString(i) + " < size (size = " + intToString(size) + "), so the condition is true and the loop continues.");
		}

		if (arr[i].value == v) {
			animationList.clear();
			setNodeColor(animationList, { getID(i) }, theme, highlight2);
			addAnimations(animationList, stepTime * (float)2, 2, "Found value " + intToString(v) + " at position " + intToString(i) + ". The functions stop here");

			animationList.clear();
			setNodeColor(animationList, { getID(i) }, theme, normal);
			deleteVariables(animationList, { getID(i) }, { "i = " + intToString(i) });
			addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

			animateAllFrame();
			return;
		}
		else {
			animationList.clear();
			doNothing(animationList);
			addAnimations(animationList, stepTime, 2, "a[" + intToString(i) + "] does not equal to " + intToString(v) + ". So the condition is false and the functions continues.");
		}

		pre = i;
		firstTime = true;
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 4, "We finished traversing the array and could not find " + intToString(v) + ", the funtion stops here.");
	animateAllFrame();
}

void DynamicArray::updateVal(int i, int v) {
	resetAnimation();
	std::vector <Animation> animationList;
	if (i < 0 || i >= size) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "There is no position " + intToString(i) + " in the array (out of range). The function stops here.");
		animateAllFrame();
		return;
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "The requested position i = " + intToString(i) + " is valid.The function continues.");

	animationList.clear();
	setNodeColor(animationList, { getID(i) }, theme, highlight);
	setNodeValue(animationList, { getID(i) }, { v });
	addAnimations(animationList, stepTime, 2, "a[" + intToString(i) + "] is now assigned to " + intToString(v) + ".");
	arr[i].value = v;

	animationList.clear();
	setNodeColor(animationList, { getID(i) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}

void DynamicArray::access(int i) {
	resetAnimation();
	std::vector <Animation> animationList;
	if (i < 0 || i >= size) {
		animationList.clear();
		doNothing(animationList);
		addAnimations(animationList, stepTime, 1, "There is no position " + intToString(i) + " in the array (out of range). The function stops here.");
		animateAllFrame();
		return;
	}
	animationList.clear();
	doNothing(animationList);
	addAnimations(animationList, stepTime, 1, "The requested position i = " + intToString(i) + " is valid.The function continues.");

	animationList.clear();
	setNodeColor(animationList, { getID(i) }, theme, highlight);
	addAnimations(animationList, stepTime, 2, "The value at position " + intToString(i) + " is " + intToString(arr[i].value) + ".");

	animationList.clear();
	setNodeColor(animationList, { getID(i) }, theme, normal);
	addAnimations(animationList, stepTime, 0, "Re-format for visualization.");

	animateAllFrame();
}