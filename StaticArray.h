#pragma once
#include "DataStructure.h"
struct StaticArray : public DataStructure {
private:
	struct Data {
		int id, value;
	};
	std::vector <Data> arr;

public:
	StaticArray(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, int numPointCircle = 30);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getTailValue();
	int getHeadID();
	int getTailID();
	int getID(int i);
	std::vector <int> getListID(int l = 0, int r = 0);
	void createRandom(int n = -1, std::vector <int> values = {}, bool sorted = false);
	void search(int v);
	void updateVal(int i, int v);
	void access(int i);
};
