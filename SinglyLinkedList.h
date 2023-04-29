#pragma once
#include "DataStructure.h"
#include "MyVector.h"
struct SinglyLinkedList : public DataStructure {
private:
	struct Data {
		int id, value, dNext;
	};
	MyVector <Data> sll;

public:
	SinglyLinkedList(double radius = 0, double outlineSize = 0, double lineThickness = 0,
		ColorTheme theme = LightTheme, EdgeType edgeType = Undirected, sf::Font* font = nullptr, int numPointCircle = 30);
	int getEmptyID();
	int getSize();
	int getHeadValue();
	int getTailValue();
	int getHeadID();
	int getTailID();
	int getID(int i);
	std::vector < std::pair <int, int>> getEdgeID(int l = 0, int r = 0);
	std::vector <int> getListID(int l = 0, int r = 0);
	void createRandom(int n = -1, std::vector <int> values = {}, bool sorted = false);
	void search(int v);
	void insertFront(int v);
	void insertBack(int v);
	void insertMiddle(int i, int v);
	void removeFront();
	void removeBack();
	void removeMiddle(int i);
	void updateFront(int v);
	void updateBack(int v);
	void updateMiddle(int i, int v);
	void peekFront();
	void peekBack();
};
