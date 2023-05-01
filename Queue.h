#pragma once
#include "DataStructure.h"
#include "MyVector.h"
struct Queue : public DataStructure {
private:
	struct Data {
		int id, value, dNext;
	};
	MyVector <Data> queue;

public:
	Queue(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, int numPointCircle = 30);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getTailValue();
	int getHeadID();
	int getTailID();
	std::vector <int> getListID(int l = 0, int r = 0);
	void createRandom(int n = -1, std::vector <int> values = {}, bool sorted = false);
	void add(int value);
	void remove();
	void peekFront();
	void peekBack();
	void clear();
};
