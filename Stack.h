#pragma once
#include "DataStructure.h"
struct Stack: public DataStructure {
private:
	struct Data {
		int id, value, dNext;
	};
	std::vector <Data> stack;
	
public:
	Stack(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, int numPointCircle = 30);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getHeadID();
	std::vector <int> getListID(int l = 0, int r = 0);
	void createRandom(int n = -1, std::vector <int> values = {}, bool sorted = false);
	void push(int value);
	void pop();
	void peek();
};