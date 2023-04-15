#pragma once
#include "DataStructure.h"
struct Queue : public DataStructure {
private:
	struct Data {
		int id, value, dNext;
	};
	std::vector <Data> queue;

public:
	Queue(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getTailValue();
	int getHeadID();
	int getTailID();
	std::vector <int> getIDList(int l = 0, int r = 0);
	void createRandom(int n = -1, std::vector <int> values = {}, bool sorted = false);
	void enqueue(int value);
	void dequeue();
	void peekFront();
	void peekBack();
};
