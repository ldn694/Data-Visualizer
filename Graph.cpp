#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Graph.h"
#include "Template.h"
#include "Node.h"
#include "Edge.h"
#include "CircularEdge.h"

//-------------------------------------------------------
//Graph

bool Graph::cmpEdgeInfo:: operator() (const EdgeInfo& a, const EdgeInfo& b) const {
	if (a.priority != b.priority) {
		return a.priority > b.priority;
	}
	if (a.v != b.v) {
		return a.v < b.v;
	}
	if (a.color.r != b.color.r) {
		return a.color.r < b.color.r;
	}
	if (a.color.g != b.color.g) {
		return a.color.g < b.color.g;
	}
	if (a.color.b != b.color.b) {
		return a.color.b < b.color.b;
	}
	return a.color.a < b.color.a;
}

bool Graph::cmpCircularEdgeInfo:: operator() (const CircularEdgeInfo& a, const CircularEdgeInfo& b) const {
	if (a.priority != b.priority) {
		return a.priority > b.priority;
	}
	if (a.v != b.v) {
		return a.v < b.v;
	}
	if (a.color.r != b.color.r) {
		return a.color.r < b.color.r;
	}
	if (a.color.g != b.color.g) {
		return a.color.g < b.color.g;
	}
	if (a.color.b != b.color.b) {
		return a.color.b < b.color.b;
	}
	return a.color.a < b.color.a;
}

Graph::FakeNode::FakeNode(int _u, int _fakeID) :
	u(_u), fakeID(_fakeID) {}

Graph::NodeAnimation::NodeAnimation(std::vector <FakeNode> _nodes, sf::Time _totalTime, sf::Time _remainTime) :
	nodes(_nodes), totalTime(_totalTime), remainTime(_remainTime) {}

Graph::EdgeInfo::EdgeInfo(int _v, sf::Color _color, bool _display, int _priority):
	v(_v), color(_color), display(_display), priority(_priority) {}

Graph::CircularEdgeInfo::CircularEdgeInfo(int _v, sf::Color _color, double _progress, int _priority) :
	v(_v), color(_color), progress(_progress), priority(_priority) {}

Graph::FakeEdge::FakeEdge(int _u, int _v, int _fakeIDu, int _fakeIDv, int _fakeIDtmp) :
	u(_u), v(_v), fakeIDu(_fakeIDu), fakeIDv(_fakeIDv), fakeIDtmp(_fakeIDtmp) {}

Graph::EdgeAnimation::EdgeAnimation(std::vector <FakeEdge> _edges, sf::Time _totalTime, sf::Time _remainTime) :
	edges(_edges), totalTime(_totalTime), remainTime(_remainTime) {}

Graph::FakeEdgeSwitch::FakeEdgeSwitch(int _u, int _v, int _newv, int _fakeID) :
	u(_u), v(_v), newv(_newv), fakeID(_fakeID) {}

Graph::EdgeSwitchAnimation::EdgeSwitchAnimation(std::vector <FakeEdgeSwitch> _edges, sf::Time _totalTime, sf::Time _remainTime) :
	edges(_edges), totalTime(_totalTime), remainTime(_remainTime) {}

Graph::Graph(double radius, double outlineSize, double _lineThickness,
		sf::Color fillColor, sf::Color outlineColor, sf::Color valueColor, sf::Color variableColor,
		EdgeType _idEdgeType, sf::Font* font, int numPointCircle) :
	defaultNode(0, 0, 0, radius, outlineSize, fillColor, outlineColor, valueColor, variableColor, font, true, numPointCircle), edgeType(_idEdgeType)
{
	lineThickness = _lineThickness;
	srand(time(0));
}

Node Graph::getDefaultNode() {
	return defaultNode;
}

int Graph::getSizeListNode() {
	return listNode.size();
}

int Graph::getFakeID() {
	int x;
	do {
		x = abs(rand()) % maxID;
	} while (listNode.find(x) != listNode.end());
	fakeIDList.insert(x);
	return x;
}

auto Graph::findV(int u, int v) {
	auto here = adj[u].end();
	for (auto cur = adj[u].begin(); cur != adj[u].end(); cur++) {
		if (cur->v == v) {
			here = cur;
			break;
		}
	}
	return here;
}

auto Graph::findCircularV(int u, int v) {
	auto here = circularAdj[u].end();
	for (auto cur = circularAdj[u].begin(); cur != circularAdj[u].end(); cur++) {
		if (cur->v == v) {
			here = cur;
			break;
		}
	}
	return here;
}

void Graph::toggleEdgeDisplay(int u, int v, bool display) {
	auto here = findV(u, v);
	if (here == adj[u].end()) {
		return;
	}
	EdgeInfo tmp = *here;
	tmp.display = display;
	adj[u].erase(here);
	adj[u].insert(tmp);
}

void Graph::toggleCircularEdgeProgress(int u, int v, double progress) {
	auto here = findCircularV(u, v);
	if (here == circularAdj[u].end()) {
		return;
	}
	CircularEdgeInfo tmp = *here;
	tmp.progress = progress;
	circularAdj[u].erase(here);
	circularAdj[u].insert(tmp);
}

void Graph::toggleEdgePriority(int u, int v, int priority) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findV(u, v);
	if (here == adj[u].end()) {
		return;
	}
	EdgeInfo tmp = *here;
	tmp.priority = priority;
	adj[u].erase(here);
	adj[u].insert(tmp);
}

void Graph::toggleCircularEdgePriority(int u, int v, int priority) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findCircularV(u, v);
	if (here == circularAdj[u].end()) {
		return;
	}
	CircularEdgeInfo tmp = *here;
	tmp.priority = priority;
	circularAdj[u].erase(here);
	circularAdj[u].insert(tmp);
}

void Graph::toggleNodeDisplay(int u, bool display) {
	listNode[u].setDisplay(display);
	std::vector <int> vList;
	for (auto& eComp : adj[u]) {
		int v = eComp.v;
		if (fakeIDList.find(v) != fakeIDList.end()) {
			continue;
		}
		vList.push_back(eComp.v);
	}
	for (int v : vList) {
		toggleEdgeDisplay(u, v, display);
	}
	vList.clear();
	for (auto& uComp : listNode) {
		int v = uComp.first;
		if (fakeIDList.find(v) != fakeIDList.end()) {
			continue;
		}
		auto here = findV(v, u);
		if (here != adj[v].end()) {
			vList.push_back(v);
		}
	}
	for (int v : vList) {
		toggleEdgeDisplay(v, u, display);
	}
}


void Graph::setFont(sf::Font* newFont) {
	defaultNode.setFont(newFont);
}

void Graph::draw(sf::RenderWindow& window) {
	//draw the first priority edge
	for (auto& uComp : listNode) {
		int u = uComp.first;
		for (auto& vComp : adj[u]) {
			if (!vComp.display || !vComp.priority) {
				continue;
			}
			int v = vComp.v;
			sf::Color lineColor = vComp.color;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			if (hypo - shorten * 2 >= epsilonDouble) {
				Edge edge(x1, y1, x2, y2, lineThickness, lineColor, edgeType, shorten, shorten);
				edge.draw(window);
			}
		}
	}
	//then the zero priority edge
	for (auto& uComp : listNode) {
		int u = uComp.first;
		for (auto &vComp : adj[u]) {
			if (!vComp.display || vComp.priority) {
				continue;
			}
			int v = vComp.v;
			sf::Color lineColor = vComp.color;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			double hypo = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
			if (hypo - shorten * 2 - (edgeType != Undirected ? 0.5 * lineThickness : 0) >= epsilonDouble) {
				Edge edge(x1, y1, x2, y2, lineThickness, lineColor, edgeType, shorten, shorten);
				edge.draw(window);
			}
		}
	}
	//draw the first priority circular edge
	for (auto& uComp : listNode) {
		int u = uComp.first;
		for (auto& vComp : circularAdj[u]) {
			if (!vComp.priority) {
				continue;
			}
			int v = vComp.v;
			sf::Color lineColor = vComp.color;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			CircularEdge edge(x1, y1, x2, y2, lineColor, lineThickness, shorten * 3, shorten * 3, shorten, vComp.progress);
			edge.draw(window);
		}
	}
	//then the zero priority circular edge
	for (auto& uComp : listNode) {
		int u = uComp.first;
		for (auto& vComp : circularAdj[u]) {
			if (vComp.priority) {
				continue;
			}
			int v = vComp.v;
			sf::Color lineColor = vComp.color;
			double x1 = listNode[u].getX();
			double y1 = listNode[u].getY();
			double x2 = listNode[v].getX();
			double y2 = listNode[v].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			CircularEdge edge(x1, y1, x2, y2, lineColor, lineThickness, shorten * 3, shorten * 3, shorten, vComp.progress);
			edge.draw(window);
		}
	}
	for (auto& uComp : listNode) {
		if (uComp.second.getDisplay()) {
			uComp.second.draw(window);
		}
	}
}

void Graph::addNode(int u, int value, double x, double y) {
	Node newNode = defaultNode;
	newNode.setValue(value);
	newNode.setXY(x, y);
	listNode[u] = newNode;
}

void Graph::addNode(int u, int value, double x, double y, sf::Time time) {
	addNode(u, value, x, y);
	listNode[u].setRadius(0.f);
	listNode[u].setOutline(0.f);
	listNode[u].addZooming(defaultNode.getRadius(), defaultNode.getOutlineSize(), time);
	nodeAddQueue.push_back(NodeAnimation({ FakeNode(u) }, time, time));
}

void Graph::addNodes(std::vector <std::tuple <int, int, double, double> > nodes) {
	for (auto& nComp : nodes) {
		int u = std::get<0>(nComp), value = std::get<1>(nComp);
		double x = std::get<2>(nComp), y = std::get<3>(nComp);
		addNode(u, value, x, y);
	}
}

void Graph::addNodes(std::vector <std::tuple <int, int, double, double> > nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (auto& nComp : nodes) {
		int u = std::get<0>(nComp), value = std::get<1>(nComp);
		double x = std::get<2>(nComp), y = std::get<3>(nComp);
		addNode(u, value, x, y);
		listNode[u].setRadius(0.f);
		listNode[u].setOutline(0.f);
		listNode[u].addZooming(defaultNode.getRadius(), defaultNode.getOutlineSize(), time);
		nodeList.push_back(FakeNode(u));
	}
	nodeAddQueue.push_back(NodeAnimation(nodeList, time, time));
}

void Graph::updateNodeAdd(sf::Time deltaT) {
	while (!nodeAddQueue.empty()) {
		NodeAnimation cur = nodeAddQueue.front();
		nodeAddQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.u].updateZooming(deltaT);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeAddQueue.push_front(cur);
		}
		else {
			/*for (auto& nComp : cur.nodes) {
				int u = nComp.u, fakeID = nComp.fakeID;
				deleteNode(fakeID);
				listNode[u].setDisplay(true);
			}*/
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::deleteNode(int pos) {
	listNode.erase(pos);
	adj.erase(pos);
	if (fakeIDList.find(pos) != fakeIDList.end()) {
		fakeIDList.erase(pos);
	}
	for (auto& uComp : listNode) {
		int u = uComp.first;
		while (true) {
			auto here = findV(u, pos);
			if (here != adj[u].end() && here->v == pos) {
				adj[u].erase(here);
			}
			else {
				break;
			}
		}
		while (true) {
			auto here = findCircularV(u, pos);
			if (here != circularAdj[u].end() && here->v == pos) {
				circularAdj[u].erase(here);
			}
			else {
				break;
			}
		}
	}
}

void Graph::deleteNode(int pos, sf::Time time) {
	int fakeID = getFakeID();
	addNode(fakeID, listNode[pos].getValue(), listNode[pos].getX(), listNode[pos].getY());
	listNode[fakeID].setRadius(listNode[pos].getRadius());
	listNode[fakeID].setOutline(listNode[pos].getOutlineSize());
	listNode[fakeID].addZooming(0.f, 0.f, time);
	nodeDeleteQueue.push_back(NodeAnimation({ FakeNode(pos, fakeID) }, time, time));
	std::vector <std::pair <int, int> > edges, circularEdges;
	for (auto& vComp : adj[pos]) {
		edges.push_back({ pos, vComp.v });
	}
	for (auto& vComp : circularAdj[pos]) {
		circularEdges.push_back({ pos, vComp.v });
	}
	for (auto& uComp : listNode) {
		int u = uComp.first;
		if (fakeIDList.find(u) != fakeIDList.end()) {
			continue;
		}
		auto here = findV(u, pos);
		if (here != adj[u].end()) {
			edges.push_back({ u, here->v });
		}
	}
	deleteEdges(edges, time);
	deleteCircularEdges(edges, time);
	deleteNode(pos);
}

void Graph::deleteNodes(std::vector <int> nodes) {
	for (int pos : nodes) {
		deleteNode(pos);
	}
}

void Graph::deleteNodes(std::vector <int> nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (int pos : nodes) {
		int fakeID = getFakeID();
		listNode[pos].setDisplay(false);
		addNode(fakeID, listNode[pos].getValue(), listNode[pos].getX(), listNode[pos].getY());
		listNode[fakeID].setRadius(listNode[pos].getRadius());
		listNode[fakeID].setOutline(listNode[pos].getOutlineSize());
		listNode[fakeID].addZooming(0.f, 0.f, time);
		nodeList.push_back(FakeNode(pos, fakeID));
	}
	nodeDeleteQueue.push_back(NodeAnimation(nodeList, time, time));
	std::vector <std::pair <int, int> > edges, circularEdges;
	for (int pos : nodes) {
		for (auto& vComp : adj[pos]) {
			edges.push_back({ pos, vComp.v });
		}
		for (auto& vComp : circularAdj[pos]) {
			circularEdges.push_back({ pos, vComp.v });
		}
		for (auto& uComp : listNode) {
			int u = uComp.first;
			if (fakeIDList.find(u) != fakeIDList.end()) {
				continue;
			}
			auto here = findV(u, pos);
			if (here != adj[u].end()) {
				edges.push_back({ u, here->v });
			}
		}
	}
	deleteEdges(edges, time);
	deleteCircularEdges(circularEdges, time);
	for (auto pos : nodes) {
		deleteNode(pos);
	}
}

void Graph::updateNodeDelete(sf::Time deltaT) {
	while (!nodeDeleteQueue.empty()) {
		NodeAnimation cur = nodeDeleteQueue.front();
		nodeDeleteQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.fakeID].updateZooming(deltaT);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeDeleteQueue.push_front(cur);
		}
		else {
			for (auto& nComp : cur.nodes) {
				int u = nComp.u, fakeID = nComp.fakeID;
				deleteNode(fakeID);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}



void Graph::moveNode(int pos, double x, double y) {
	listNode[pos].setXY(x, y);
}

void Graph::moveNode(int pos, double x, double y, sf::Time time) {
	listNode[pos].addMovement(x, y, time);
	nodeMoveQueue.push_back(NodeAnimation({FakeNode(pos)}, time, time));
}

void Graph::moveNodes(std::vector <std::tuple<int, double, double> > nodes) {
	for (auto& nComp : nodes) {
		int u = std::get<0>(nComp);
		double x = std::get<1>(nComp), y = std::get<2>(nComp);
		listNode[u].setXY(x, y);
	}
}

void Graph::moveNodes(std::vector <std::tuple<int, double, double> > nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (auto& nComp : nodes) {
		int pos = std::get<0>(nComp);
		double x = std::get<1>(nComp), y = std::get<2>(nComp);
		listNode[pos].addMovement(x, y, time);
		nodeList.push_back(FakeNode(pos, -1));
	}
	nodeMoveQueue.push_back(NodeAnimation(nodeList, time, time));
}

void Graph::translateNodes(std::vector <int> nodes, double dx, double dy) {
	std::vector <std::tuple <int, double, double>> nodeList;
	for (int i = 0; i < (int)nodes.size(); i++) {
		int pos = nodes[i];
		nodeList.push_back({ pos, listNode[pos].getX() + dx, listNode[pos].getY() + dy });
	}
	moveNodes(nodeList);
}

void Graph::translateNodes(std::vector <int> nodes, double dx, double dy, sf::Time time) {
	std::vector <std::tuple <int, double, double>> nodeList;
	for (int i = 0; i < (int)nodes.size(); i++) {
		int pos = nodes[i];
		nodeList.push_back({ pos, listNode[pos].getX() + dx, listNode[pos].getY() + dy});
	}
	moveNodes(nodeList, time);
}

void Graph::mergeNodeMove() {
	if (nodeMoveQueue.size() < 2) {
		return;
	}
	NodeAnimation First = nodeMoveQueue.front();
	nodeMoveQueue.pop_front();
	NodeAnimation Second = nodeMoveQueue.front();
	nodeMoveQueue.pop_front();
	std::vector <FakeNode> nodeList = First.nodes;
	for (auto& uComp : Second.nodes) {
		nodeList.push_back(uComp);
	}
	NodeAnimation Merge = NodeAnimation(nodeList, First.totalTime, First.remainTime);
	nodeMoveQueue.push_back(Merge);
}

void Graph::updateNodeMove(sf::Time deltaT) {
	while (!nodeMoveQueue.empty()) {
		NodeAnimation cur = nodeMoveQueue.front();
		nodeMoveQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.u].updateMovement(elapsedTime);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeMoveQueue.push_front(cur);
		}
		else {
			
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::addNodeVariable(int u, std::string variable) {
	listNode[u].addVariable(variable);
}

void Graph::deleteNodeVariable(int u, std::string variable) {
	listNode[u].eraseVariable(variable);
}

void Graph::setNodeFillColor(int pos, sf::Color color) {
	listNode[pos].setFillColor(color);
}

void Graph::setNodeFillColor(int pos, sf::Color color, sf::Time time) {
	listNode[pos].addFillColor(color, time);
	nodeFillColorQueue.push_back(NodeAnimation({ FakeNode(pos) }, time, time));
}

void Graph::setNodesFillColor(std::vector <std::pair<int, sf::Color>> nodes) {
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].setFillColor(color);
	}
}

void Graph::setNodesFillColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].addFillColor(color, time);
		nodeList.push_back(FakeNode(pos));
	}
	nodeFillColorQueue.push_back(NodeAnimation(nodeList, time, time));
}

void Graph::updateNodeFillColor(sf::Time deltaT) {
	while (!nodeFillColorQueue.empty()) {
		NodeAnimation cur = nodeFillColorQueue.front();
		nodeFillColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.u].updateFillColor(elapsedTime);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeFillColorQueue.push_front(cur);
		}
		else {

		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::setNodeOutlineColor(int pos, sf::Color color) {
	listNode[pos].setOutlineColor(color);
}

void Graph::setNodeOutlineColor(int pos, sf::Color color, sf::Time time) {
	listNode[pos].addOutlineColor(color, time);
	nodeOutlineColorQueue.push_back(NodeAnimation({ FakeNode(pos) }, time, time));
}

void Graph::setNodesOutlineColor(std::vector <std::pair<int, sf::Color>> nodes) {
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].setOutlineColor(color);
	}
}

void Graph::setNodesOutlineColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].addOutlineColor(color, time);
		nodeList.push_back(FakeNode(pos));
	}
	nodeOutlineColorQueue.push_back(NodeAnimation(nodeList, time, time));
}

void Graph::updateNodeOutlineColor(sf::Time deltaT) {
	while (!nodeOutlineColorQueue.empty()) {
		NodeAnimation cur = nodeOutlineColorQueue.front();
		nodeOutlineColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.u].updateOutlineColor(elapsedTime);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeOutlineColorQueue.push_front(cur);
		}
		else {

		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::setNodeValueColor(int pos, sf::Color color) {
	listNode[pos].setValueColor(color);
}

void Graph::setNodeValueColor(int pos, sf::Color color, sf::Time time) {
	listNode[pos].addValueColor(color, time);
	nodeValueColorQueue.push_back(NodeAnimation({ FakeNode(pos) }, time, time));
}

void Graph::setNodesValueColor(std::vector <std::pair<int, sf::Color>> nodes) {
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].setValueColor(color);
	}
}

void Graph::setNodesValueColor(std::vector <std::pair<int, sf::Color>> nodes, sf::Time time) {
	std::vector <FakeNode> nodeList;
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].addValueColor(color, time);
		nodeList.push_back(FakeNode(pos));
	}
	nodeValueColorQueue.push_back(NodeAnimation(nodeList, time, time));
}

void Graph::updateNodeValueColor(sf::Time deltaT) {
	while (!nodeValueColorQueue.empty()) {
		NodeAnimation cur = nodeValueColorQueue.front();
		nodeValueColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& nComp : cur.nodes) {
			listNode[nComp.u].updateValueColor(elapsedTime);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			nodeValueColorQueue.push_front(cur);
		}
		else {

		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::setNodeValue(int pos, int v) {
	listNode[pos].setValue(v);
}

void Graph::setNodeVariableColor(int pos, sf::Color color) {
	listNode[pos].setVariableColor(color);
}

void Graph::setNodesVariableColor(std::vector <std::pair<int, sf::Color>> nodes) {
	for (auto& nComp : nodes) {
		int pos = nComp.first;
		sf::Color color = nComp.second;
		listNode[pos].setVariableColor(color);
	}
}

void Graph::addEdge(int u, int v, sf::Color color) {
	adj[u].insert(EdgeInfo(v, color));
}

void Graph::addEdges(std::vector <std::tuple <int, int, sf::Color>> edges) {
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		addEdge(u, v, color);
	}
}

void Graph::addEdge(int u, int v, sf::Color color, sf::Time time) {
	addEdge(u, v, color);
	toggleEdgeDisplay(u, v, false);
	int fakeIDu = getFakeID();
	int fakeIDv = getFakeID();
	int fakeIDtmp = getFakeID();
	double x1 = listNode[u].getX(), y1 = listNode[u].getY();
	double x2 = listNode[v].getX(), y2 = listNode[v].getY();
	double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
	addNode(fakeIDu, 0, x1, y1);
	addNode(fakeIDv, 0, x2, y2);
	MovePoint(x1, y1, x2, y2, 2 * shorten);
	addNode(fakeIDtmp, 0, x1, y1);
	listNode[fakeIDu].setDisplay(false);
	listNode[fakeIDv].setDisplay(false);
	listNode[fakeIDtmp].setDisplay(false);
	addEdge(fakeIDu, fakeIDtmp, color);
	edgeAddQueue.push_back(EdgeAnimation({ FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp) }, time, time));
}

void Graph::addEdges(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		addEdge(u, v, color);
		toggleEdgeDisplay(u, v, false);
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		int fakeIDtmp = getFakeID();
		double x1 = listNode[u].getX(), y1 = listNode[u].getY();
		double x2 = listNode[v].getX(), y2 = listNode[v].getY();
		double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
		addNode(fakeIDu, 0, x1, y1);
		addNode(fakeIDv, 0, x2, y2);
		MovePoint(x1, y1, x2, y2, 2 * shorten);
		addNode(fakeIDtmp, 0, x1, y1);
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		listNode[fakeIDtmp].setDisplay(false);
		addEdge(fakeIDu, fakeIDtmp, color);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp));
	}
	edgeAddQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateEdgeAdd(sf::Time deltaT) {
	while (!edgeAddQueue.empty()) {
		EdgeAnimation cur = edgeAddQueue.front();
		edgeAddQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
			double x1 = listNode[fakeIDu].getX(), y1 = listNode[fakeIDu].getY();
			double x2 = listNode[fakeIDv].getX(), y2 = listNode[fakeIDv].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			MovePoint(x1, y1, x2, y2, 2 * shorten);
			double dx = elapsedTime / cur.totalTime * (x2 - x1);
			double dy = elapsedTime / cur.totalTime * (y2 - y1);
			moveNode(fakeIDtmp, listNode[fakeIDtmp].getX() + dx, listNode[fakeIDtmp].getY() + dy);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			edgeAddQueue.push_front(cur);
		}
		else {
			for (auto& eComp : cur.edges) {
				int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
				deleteNode(fakeIDu);
				deleteNode(fakeIDv);
				deleteNode(fakeIDtmp);
				toggleEdgeDisplay(u, v, true);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::addCircularEdge(int u, int v, sf::Color color) {
	circularAdj[u].insert(CircularEdgeInfo(v, color));
}

void Graph::addCircularEdge(int u, int v, sf::Color color, sf::Time time) {
	addCircularEdge(u, v, color);
	toggleCircularEdgeProgress(u, v, 0);
	int fakeIDu = getFakeID();
	int fakeIDv = getFakeID();
	int fakeIDtmp = getFakeID();
	addNode(fakeIDu, 0, listNode[u].getX(), listNode[u].getY());
	addNode(fakeIDv, 0, listNode[v].getX(), listNode[v].getY());
	listNode[fakeIDu].setDisplay(false);
	listNode[fakeIDv].setDisplay(false);
	addCircularEdge(fakeIDu, fakeIDv, color);
	toggleCircularEdgeProgress(fakeIDu, fakeIDv, 0);
	circularEdgeAddQueue.push_back(EdgeAnimation({ FakeEdge(u, v, fakeIDu, fakeIDv) }, time, time));
}

void Graph::addCircularEdges(std::vector <std::tuple <int, int, sf::Color>> edges) {
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		addCircularEdge(u, v, color);
	}
}

void Graph::addCircularEdges(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		addCircularEdge(u, v, color);
		toggleCircularEdgeProgress(u, v, 0);
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		addNode(fakeIDu, 0, listNode[u].getX(), listNode[u].getY());
		addNode(fakeIDv, 0, listNode[v].getX(), listNode[v].getY());
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		addCircularEdge(fakeIDu, fakeIDv, color);
		toggleCircularEdgeProgress(fakeIDu, fakeIDv, 0);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv));
	}
	circularEdgeAddQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateCircularEdgeAdd(sf::Time deltaT) {
	while (!circularEdgeAddQueue.empty()) {
		EdgeAnimation cur = circularEdgeAddQueue.front();
		circularEdgeAddQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv;
			double dProgress = elapsedTime / cur.totalTime;
			toggleCircularEdgeProgress(fakeIDu, fakeIDv, findCircularV(fakeIDu, fakeIDv)->progress + dProgress);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			circularEdgeAddQueue.push_front(cur);
		}
		else {
			for (auto& eComp : cur.edges) {
				int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv;
				deleteNodes({ fakeIDu, fakeIDv });
				toggleCircularEdgeProgress(u, v, 1);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::deleteEdge(int u, int v) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	while (true) {
		auto here = findV(u, v);
		if (here == adj[u].end()) {
			break;
		}
		adj[u].erase(here);
	}
}

void Graph::deleteEdge(int u, int v, sf::Time time) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findV(u, v);
	if (here == adj[u].end()) {
		return;
	}
	int fakeIDu = getFakeID();
	int fakeIDv = getFakeID();
	int fakeIDtmp = getFakeID();
	double x1 = listNode[u].getX(), y1 = listNode[u].getY();
	double x2 = listNode[v].getX(), y2 = listNode[v].getY();
	double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
	addNode(fakeIDu, 0, x1, y1);
	addNode(fakeIDv, 0, x2, y2);
	addNode(fakeIDtmp, 0, x2, y2);
	listNode[fakeIDu].setDisplay(false);
	listNode[fakeIDv].setDisplay(false);
	listNode[fakeIDtmp].setDisplay(false);
	addEdge(fakeIDu, fakeIDtmp, here->color);
	deleteEdge(u, v);
	edgeDeleteQueue.push_back(EdgeAnimation({ FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp) }, time, time));
}

void Graph::deleteEdges(std::vector <std::pair<int, int>> edges) {
	for (std::pair <int, int> edge : edges)
	{
		int u = edge.first, v = edge.second;
		deleteEdge(u, v);
	}
}

void Graph::deleteEdges(std::vector <std::pair<int, int>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (std::pair <int, int> edge : edges)
	{
		int u = edge.first, v = edge.second;
		if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
			continue;
		}
		auto here = findV(u, v);
		if (here == adj[u].end()) {
			continue;
		}
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		int fakeIDtmp = getFakeID();
		double x1 = listNode[u].getX(), y1 = listNode[u].getY();
		double x2 = listNode[v].getX(), y2 = listNode[v].getY();
		double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
		addNode(fakeIDu, 0, x1, y1);
		addNode(fakeIDv, 0, x2, y2);
		addNode(fakeIDtmp, 0, x2, y2);
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		listNode[fakeIDtmp].setDisplay(false);
		addEdge(fakeIDu, fakeIDtmp, here->color);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp));
		deleteEdge(u, v);
	}
	edgeDeleteQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateEdgeDelete(sf::Time deltaT) {
	while (!edgeDeleteQueue.empty()) {
		EdgeAnimation cur = edgeDeleteQueue.front();
		edgeDeleteQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
			double x1 = listNode[fakeIDu].getX(), y1 = listNode[fakeIDu].getY();
			double x2 = listNode[fakeIDv].getX(), y2 = listNode[fakeIDv].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			MovePoint(x1, y1, x2, y2, 2 * shorten);
			double dx = elapsedTime / cur.totalTime * (x1 - x2);
			double dy = elapsedTime / cur.totalTime * (y1 - y2);
			moveNode(fakeIDtmp, listNode[fakeIDtmp].getX() + dx, listNode[fakeIDtmp].getY() + dy);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			edgeDeleteQueue.push_front(cur);
		}
		else {
			for (auto &eComp : cur.edges) {
				int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
				deleteNode(fakeIDu);
				deleteNode(fakeIDv);
				deleteNode(fakeIDtmp);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::deleteCircularEdge(int u, int v) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	while (true) {
		auto here = findCircularV(u, v);
		if (here == circularAdj[u].end()) {
			break;
		}
		circularAdj[u].erase(here);
	}
}

void Graph::deleteCircularEdges(std::vector <std::pair<int, int>> edges) {
	for (std::pair <int, int> edge : edges)
	{
		int u = edge.first, v = edge.second;
		deleteCircularEdge(u, v);
	}
}

void Graph::deleteCircularEdges(std::vector <std::pair<int, int>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (std::pair <int, int> edge : edges)
	{
		int u = edge.first, v = edge.second;
		if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
			continue;
		}
		auto here = findCircularV(u, v);
		if (here == circularAdj[u].end()) {
			continue;
		}
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		double x1 = listNode[u].getX(), y1 = listNode[u].getY();
		double x2 = listNode[v].getX(), y2 = listNode[v].getY();
		addNode(fakeIDu, 0, x1, y1);
		addNode(fakeIDv, 0, x2, y2);
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		addCircularEdge(fakeIDu, fakeIDv, here->color);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv));
		deleteCircularEdge(u, v);
	}
	circularEdgeDeleteQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateCircularEdgeDelete(sf::Time deltaT) {
	while (!circularEdgeDeleteQueue.empty()) {
		EdgeAnimation cur = circularEdgeDeleteQueue.front();
		circularEdgeDeleteQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv;
			double dProgress = elapsedTime / cur.totalTime;
			toggleCircularEdgeProgress(fakeIDu, fakeIDv, findCircularV(fakeIDu, fakeIDv)->progress - dProgress);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			circularEdgeDeleteQueue.push_front(cur);
		}
		else {
			for (auto& eComp : cur.edges) {
				int fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv;
				deleteNode(fakeIDu);
				deleteNode(fakeIDv);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::switchEdge(int u, int v, int newv) {
	if (v == newv || findV(u, v) == adj[u].end()) {
		return;
	}
	auto here = findV(u, v);
	EdgeInfo tmp = *here;
	tmp.v = newv;
	adj[u].erase(here);
	adj[u].insert(tmp);
}

void Graph::switchEdge(int u, int v, int newv, sf::Time time) {
	if (v == newv || findV(u, v) == adj[u].end()) {
		return;
	}
	toggleEdgeDisplay(u, v, false);
	int fakeID = getFakeID();
	addNode(fakeID, 0, listNode[v].getX(), listNode[v].getY());
	listNode[fakeID].setDisplay(false);
	addEdge(u, fakeID, findV(u, v)->color);
	edgeSwitchQueue.push_back(EdgeSwitchAnimation({ FakeEdgeSwitch(u, v, newv, fakeID) }, time, time));
	switchEdge(u, v, newv);
}

void Graph::switchEdges(std::vector <std::tuple<int, int, int>> edgesSwitch) {
	for (auto& eComp : edgesSwitch) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp), newv = std::get<2>(eComp);
		switchEdge(u, v, newv);
	}
}

void Graph::switchEdges(std::vector <std::tuple<int, int, int>> edgesSwitch, sf::Time time) {
	std::vector <FakeEdgeSwitch> edgeSwitchList;
	for (auto& eComp : edgesSwitch) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp), newv = std::get<2>(eComp);
		if (v == newv || findV(u, v) == adj[u].end()) {
			return;
		}
		toggleEdgeDisplay(u, v, false);
		int fakeID = getFakeID();
		addNode(fakeID, 0, listNode[v].getX(), listNode[v].getY());
		listNode[fakeID].setDisplay(false);
		addEdge(u, fakeID, findV(u, v)->color);
		edgeSwitchList.push_back(FakeEdgeSwitch(u, v, newv, fakeID));
		switchEdge(u, v, newv);
	}
	edgeSwitchQueue.push_back(EdgeSwitchAnimation(edgeSwitchList, time, time));
}

void Graph::updateEdgeSwitch(sf::Time deltaT) {
	while (!edgeSwitchQueue.empty()) {
		EdgeSwitchAnimation cur = edgeSwitchQueue.front();
		edgeSwitchQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& vComp : cur.edges) {
			int u = vComp.u, v = vComp.v, newv = vComp.newv, fakeID = vComp.fakeID;
			double dx = elapsedTime / cur.remainTime * (listNode[newv].getX() - listNode[fakeID].getX());
			double dy = elapsedTime / cur.remainTime * (listNode[newv].getY() - listNode[fakeID].getY());
			moveNode(fakeID, listNode[fakeID].getX() + dx, listNode[fakeID].getY() + dy);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			edgeSwitchQueue.push_front(cur);
		}
		else {
			for (auto& vComp : cur.edges) {
				int u = vComp.u, v = vComp.v, newv = vComp.newv, fakeID = vComp.fakeID;
				deleteNode(fakeID);
				toggleEdgeDisplay(u, newv, true);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::switchCircularEdge(int u, int v, int newv) {
	if (v == newv || findCircularV(u, v) == circularAdj[u].end()) {
		return;
	}
	auto here = findCircularV(u, v);
	CircularEdgeInfo tmp = *here;
	tmp.v = newv;
	circularAdj[u].erase(here);
	circularAdj[u].insert(tmp);
}

void Graph::switchCircularEdge(int u, int v, int newv, sf::Time time) {
	if (v == newv || findCircularV(u, v) == circularAdj[u].end()) {
		return;
	}
	toggleCircularEdgeProgress(u, v, 0);
	int fakeID = getFakeID();
	addNode(fakeID, 0, listNode[v].getX(), listNode[v].getY());
	listNode[fakeID].setDisplay(false);
	addCircularEdge(u, fakeID, findCircularV(u, v)->color);
	circularEdgeSwitchQueue.push_back(EdgeSwitchAnimation({ FakeEdgeSwitch(u, v, newv, fakeID) }, time, time));
	switchCircularEdge(u, v, newv);
}

void Graph::switchCircularEdges(std::vector <std::tuple<int, int, int>> edgesSwitch) {
	for (auto& eComp : edgesSwitch) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp), newv = std::get<2>(eComp);
		switchCircularEdge(u, v, newv);
	}
}

void Graph::switchCircularEdges(std::vector <std::tuple<int, int, int>> edgesSwitch, sf::Time time) {
	std::vector <FakeEdgeSwitch> edgeSwitchList;
	for (auto& eComp : edgesSwitch) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp), newv = std::get<2>(eComp);
		if (v == newv || findCircularV(u, v) == circularAdj[u].end()) {
			return;
		}
		toggleCircularEdgeProgress(u, v, 0);
		int fakeID = getFakeID();
		addNode(fakeID, 0, listNode[v].getX(), listNode[v].getY());
		listNode[fakeID].setDisplay(false);
		addCircularEdge(u, fakeID, findCircularV(u, v)->color);
		edgeSwitchList.push_back(FakeEdgeSwitch(u, v, newv, fakeID));
		switchCircularEdge(u, v, newv);
	}
	circularEdgeSwitchQueue.push_back(EdgeSwitchAnimation(edgeSwitchList, time, time));
}

void Graph::updateCircularEdgeSwitch(sf::Time deltaT) {
	while (!circularEdgeSwitchQueue.empty()) {
		EdgeSwitchAnimation cur = circularEdgeSwitchQueue.front();
		circularEdgeSwitchQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& vComp : cur.edges) {
			int u = vComp.u, v = vComp.v, newv = vComp.newv, fakeID = vComp.fakeID;
			double dx = elapsedTime / cur.remainTime * (listNode[newv].getX() - listNode[fakeID].getX());
			double dy = elapsedTime / cur.remainTime * (listNode[newv].getY() - listNode[fakeID].getY());
			moveNode(fakeID, listNode[fakeID].getX() + dx, listNode[fakeID].getY() + dy);
		}
		deltaT -= elapsedTime;
		cur.remainTime -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			circularEdgeSwitchQueue.push_front(cur);
		}
		else {
			for (auto& vComp : cur.edges) {
				int u = vComp.u, v = vComp.v, newv = vComp.newv, fakeID = vComp.fakeID;
				deleteNode(fakeID);
				toggleCircularEdgeProgress(u, newv, 1);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::setEdgeColor(int u, int v, sf::Color color) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findV(u, v);
	if (here == adj[u].end()) {
		return;
	}
	EdgeInfo tmp = *here;
	tmp.color = color;
	adj[u].erase(here);
	adj[u].insert(tmp);
}

void Graph::setEdgeColor(int u, int v, sf::Color color, sf::Time time) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findV(u, v);
	if (here == adj[u].end()) {
		return;
	}
	sf::Color prevColor = here->color;
	setEdgeColor(u, v, color);
	toggleEdgeDisplay(u, v, false);
	int fakeIDu = getFakeID();
	int fakeIDv = getFakeID();
	int fakeIDtmp = getFakeID();
	double x1 = listNode[u].getX(), y1 = listNode[u].getY();
	double x2 = listNode[v].getX(), y2 = listNode[v].getY();
	double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
	addNode(fakeIDu, 0, x1, y1);
	addNode(fakeIDv, 0, x2, y2);
	MovePoint(x1, y1, x2, y2, 2 * shorten);
	addNode(fakeIDtmp, 0, x1, y1);
	listNode[fakeIDu].setDisplay(false);
	listNode[fakeIDv].setDisplay(false);
	listNode[fakeIDtmp].setDisplay(false);
	addEdge(fakeIDu, fakeIDtmp, color);
	addEdge(fakeIDu, fakeIDv, prevColor);
	toggleEdgePriority(fakeIDu, fakeIDv, 1);
	edgeColorQueue.push_back(EdgeAnimation({ FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp) }, time, time));
}

void Graph::setEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges) {
	std::vector <FakeEdge> edgeList;
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		setEdgeColor(u, v, color);
	}
}

void Graph::setEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
			continue;
		}
		auto here = findV(u, v);
		if (here == adj[u].end()) {
			continue;
		}
		sf::Color prevColor = here->color;
		setEdgeColor(u, v, color);
		toggleEdgeDisplay(u, v, false);
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		int fakeIDtmp = getFakeID();
		double x1 = listNode[u].getX(), y1 = listNode[u].getY();
		double x2 = listNode[v].getX(), y2 = listNode[v].getY();
		double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
		addNode(fakeIDu, 0, x1, y1);
		addNode(fakeIDv, 0, x2, y2);
		MovePoint(x1, y1, x2, y2, 2 * shorten);
		addNode(fakeIDtmp, 0, x1, y1);
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		listNode[fakeIDtmp].setDisplay(false);
		addEdge(fakeIDu, fakeIDtmp, color);
		addEdge(fakeIDu, fakeIDv, prevColor);
		toggleEdgePriority(fakeIDu, fakeIDv, 1);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp));
	}
	edgeColorQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateEdgeColor(sf::Time deltaT) {
	while (!edgeColorQueue.empty()) {
		EdgeAnimation cur = edgeColorQueue.front();
		edgeColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
			double x1 = listNode[fakeIDu].getX(), y1 = listNode[fakeIDu].getY();
			double x2 = listNode[fakeIDv].getX(), y2 = listNode[fakeIDv].getY();
			double shorten = defaultNode.getRadius() + defaultNode.getOutlineSize();
			MovePoint(x1, y1, x2, y2, 2 * shorten);
			double dx = elapsedTime / cur.totalTime * (x2 - x1);
			double dy = elapsedTime / cur.totalTime * (y2 - y1);
			moveNode(fakeIDtmp, listNode[fakeIDtmp].getX() + dx, listNode[fakeIDtmp].getY() + dy);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			edgeColorQueue.push_front(cur);
		}
		else {
			for (auto& eComp : cur.edges) {
				int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
				deleteNode(fakeIDu);
				deleteNode(fakeIDv);
				deleteNode(fakeIDtmp);
				toggleEdgeDisplay(u, v, true);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}

void Graph::setCircularEdgeColor(int u, int v, sf::Color color) {
	if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
		return;
	}
	auto here = findCircularV(u, v);
	if (here == circularAdj[u].end()) {
		return;
	}
	CircularEdgeInfo tmp = *here;
	tmp.color = color;
	circularAdj[u].erase(here);
	circularAdj[u].insert(tmp);
}

void Graph::setCircularEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges) {
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		setCircularEdgeColor(u, v, color);
	}
}

void Graph::setCircularEdgesColor(std::vector <std::tuple <int, int, sf::Color>> edges, sf::Time time) {
	std::vector <FakeEdge> edgeList;
	for (auto& eComp : edges) {
		int u = std::get<0>(eComp), v = std::get<1>(eComp);
		sf::Color color = std::get<2>(eComp);
		if (listNode.find(u) == listNode.end() || listNode.find(v) == listNode.end()) {
			continue;
		}
		auto here = findCircularV(u, v);
		if (here == circularAdj[u].end()) {
			continue;
		}
		sf::Color prevColor = here->color;
		setCircularEdgeColor(u, v, color);
		toggleCircularEdgeProgress(u, v, 0);
		int fakeIDu = getFakeID();
		int fakeIDv = getFakeID();
		int fakeIDtmp = getFakeID();
		addNode(fakeIDu, 0, listNode[u].getX(), listNode[u].getY());
		addNode(fakeIDv, 0, listNode[v].getX(), listNode[v].getY());
		addNode(fakeIDtmp, 0, listNode[v].getX(), listNode[v].getY());
		listNode[fakeIDu].setDisplay(false);
		listNode[fakeIDv].setDisplay(false);
		listNode[fakeIDtmp].setDisplay(false);
		addCircularEdge(fakeIDu, fakeIDv, prevColor);
		addCircularEdge(fakeIDu, fakeIDtmp, color);
		toggleCircularEdgeProgress(fakeIDu, fakeIDv, 1);
		toggleCircularEdgeProgress(fakeIDu, fakeIDtmp, 0);
		toggleCircularEdgePriority(fakeIDu, fakeIDv, 1);
		edgeList.push_back(FakeEdge(u, v, fakeIDu, fakeIDv, fakeIDtmp));
	}
	circularEdgeColorQueue.push_back(EdgeAnimation(edgeList, time, time));
}

void Graph::updateCircularEdgeColor(sf::Time deltaT) {
	while (!circularEdgeColorQueue.empty()) {
		EdgeAnimation cur = circularEdgeColorQueue.front();
		circularEdgeColorQueue.pop_front();
		sf::Time elapsedTime = (cur.remainTime < deltaT ? cur.remainTime : deltaT);
		for (auto& eComp : cur.edges) {
			int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
			double dProgress = elapsedTime / cur.totalTime;
			toggleCircularEdgeProgress(fakeIDu, fakeIDtmp, findCircularV(fakeIDu, fakeIDtmp)->progress + dProgress);
		}
		cur.remainTime -= elapsedTime;
		deltaT -= elapsedTime;
		if (cur.remainTime >= epsilonTime) {
			circularEdgeColorQueue.push_front(cur);
		}
		else {
			for (auto& eComp : cur.edges) {
				int u = eComp.u, v = eComp.v, fakeIDu = eComp.fakeIDu, fakeIDv = eComp.fakeIDv, fakeIDtmp = eComp.fakeIDtmp;
				deleteNode(fakeIDu);
				deleteNode(fakeIDv);
				deleteNode(fakeIDtmp);
				toggleCircularEdgeProgress(u, v, 1);
			}
		}
		if (deltaT < epsilonTime) break;
	}
}


void Graph::setTheme(ColorTheme preTheme, ColorTheme curTheme) {
	stopAnimation();
	for (auto& uComp : listNode) {
		Node& node = uComp.second;
		int u = uComp.first;
		int resType = -1;
		for (int type = 0; type < numColorNodeType; type++) {
			ColorNode here = colorNode[preTheme][type];
			if (node.getFillColor() == here.fillColor && node.getOutlineColor() == here.outlineColor
				&& node.getValueColor() == here.valueColor && node.getVariableColor() == here.variableColor) {
				resType = type;
				break;
			}
		}
		if (resType == -1) {
			std::cout << u << " " << node.getX() << " " << node.getY() << " " << (int)node.getFillColor().r << " " << (int)node.getFillColor().g << " " << (int)node.getFillColor().b << "\n";
		}
		assert(resType != -1);
		ColorNode colorHere = colorNode[curTheme][resType];
		setNodeFillColor(u, colorHere.fillColor);
		setNodeOutlineColor(u, colorHere.outlineColor);
		setNodeValueColor(u, colorHere.valueColor);
		setNodeVariableColor(u, colorHere.variableColor);
	}
	std::vector <std::tuple <int, int, sf::Color>> listEdge;
	for (auto& uComp : listNode) {
		Node& node = uComp.second;
		int u = uComp.first;
		for (auto& vComp : adj[u]) {
			int resType = -1;
			for (int type = 0; type < numColorNodeType; type++) {
				ColorNode here = colorNode[preTheme][type];
				if (vComp.color == here.outlineColor) {
					resType = type;
					break;
				}
			}
			assert(resType != -1); 
			listEdge.push_back({ u, vComp.v, colorNode[curTheme][resType].outlineColor });
		}
	}
	setEdgesColor(listEdge);
	listEdge.clear();
	for (auto& uComp : listNode) {
		Node& node = uComp.second;
		int u = uComp.first;
		for (auto& vComp : circularAdj[u]) {
			int resType = -1;
			for (int type = 0; type < numColorNodeType; type++) {
				ColorNode here = colorNode[preTheme][type];
				if (vComp.color == here.outlineColor) {
					resType = type;
					break;
				}
			}
			assert(resType != -1);
			listEdge.push_back({ u, vComp.v, colorNode[curTheme][resType].outlineColor });
		}
	}
	setCircularEdgesColor(listEdge);
	defaultNode.setFillColor(colorNode[curTheme][normal].fillColor);
	defaultNode.setOutlineColor(colorNode[curTheme][normal].outlineColor);
	defaultNode.setValueColor(colorNode[curTheme][normal].valueColor);
	defaultNode.setVariableColor(colorNode[curTheme][normal].variableColor);
}

void Graph::update(sf::Time deltaT) {
	updateNodeAdd(deltaT);
	updateNodeDelete(deltaT);
	updateNodeMove(deltaT);
	updateNodeFillColor(deltaT);
	updateNodeOutlineColor(deltaT);
	updateNodeValueColor(deltaT);
	updateEdgeAdd(deltaT);
	updateCircularEdgeAdd(deltaT);
	updateEdgeDelete(deltaT);
	updateCircularEdgeDelete(deltaT);
	updateEdgeSwitch(deltaT);
	updateCircularEdgeSwitch(deltaT);
	updateEdgeColor(deltaT);
	updateCircularEdgeColor(deltaT);
}

void Graph::stopAnimation() {
	while (!fakeIDList.empty()) {
		int x = *(fakeIDList.begin());
		deleteNode(x);
	}	
	for (auto& uComp : listNode) {
		int u = uComp.first;
		toggleNodeDisplay(u, true);
		uComp.second.stopAnimation();
		std::vector <int> listV;
		for (auto& vComp : adj[u]) {
			listV.push_back(vComp.v);
		}
		for (int v : listV) {
			toggleEdgeDisplay(u, v, 1);
		}
		listV.clear();
		for (auto& vComp : circularAdj[u]) {
			listV.push_back(vComp.v);
		}
		for (int v : listV) {
			toggleCircularEdgeProgress(u, v, 1);
		}
	}
	nodeAddQueue.clear();
	nodeDeleteQueue.clear(); 
	nodeMoveQueue.clear();
	edgeAddQueue.clear(); 
	circularEdgeAddQueue.clear();
	edgeDeleteQueue.clear();
	circularEdgeDeleteQueue.clear();
	edgeSwitchQueue.clear();
	circularEdgeSwitchQueue.clear();
	edgeColorQueue.clear();
	circularEdgeColorQueue.clear();
}

//-------------------------------------------------------