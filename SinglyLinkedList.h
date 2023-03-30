#pragma once
#include "DataStructure.h"

struct SinglyLinkedList : public DataStructure {
private:
	struct Data {
		int id, value, dNext;
	};
	std::vector <Data> linkedList;
	ColorTheme theme;

public:
	SinglyLinkedList(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getHeadID();
	int getTailID();
	std::vector <int> getIDList(int l = 0, int r = 0);
	void createRandom();
	void insertFront(int value);
	void insertBack(int value);
	void eraseFront();
	void eraseBack();
};