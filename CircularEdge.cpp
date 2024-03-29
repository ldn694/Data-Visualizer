#include <algorithm>
#include "CircularEdge.h"
#include "Template.h"
#include "Edge.h"

CircularEdge::CircularEdge(double _x1, double _y1, double _x2, double _y2, sf::Color _color,
	double _thickness, double _upward, double _leftward, double _shorten, double _progress) :
	x1(_x1), y1(_y1), x2(_x2), y2(_y2), color(_color), thickness(_thickness), upward(_upward), shorten(_shorten), leftward(_leftward), progress(_progress)
{

}

void CircularEdge::draw(sf::RenderWindow &window) {
	double x3 = x1, y3 = std::min(y1, y2) - upward;
	double x4 = x1 - leftward - (x1 - x2), y4 = std::min(y1, y2) - upward;
	double x5 = x2 - leftward, y5 = y2;
	// 4------3
	// |      |
	// |      |
	// 5->2   1
	double totalLength = dist2p(x1, y1, x3, y3) - shorten + dist2p(x3, y3, x4, y4) + dist2p(x4, y4, x5, y5) + dist2p(x5, y5, x2, y2) - shorten;
	double upPart = (dist2p(x1, y1, x3, y3) - shorten) / totalLength;
	double leftPart = dist2p(x3, y3, x4, y4) / totalLength;
	double downPart = dist2p(x4, y4, x5, y5) / totalLength;
	double rightPart = (dist2p(x5, y5, x2, y2) - shorten) / totalLength;
	if (progress < upPart) { //up
		Edge upEdge(x1, y1, x3, y3, thickness, color, SinglyDirected, shorten, (upPart - progress) * totalLength - thickness * 0.5);
		upEdge.draw(window);
		return;
	}
	Edge upEdge(x1, y1, x3, y3, thickness, color, Undirected, shorten, -thickness * 0.5);
	upEdge.draw(window);
	progress -= upPart;

	if (progress < leftPart) { //left
		Edge leftEdge(x3, y3, x4, y4, thickness, color, SinglyDirected, 0, (leftPart - progress) * totalLength - thickness * 0.5);
		leftEdge.draw(window);
		return;
	}
	Edge leftEdge(x3, y3, x4, y4, thickness, color, Undirected, 0, -thickness * 0.5);
	leftEdge.draw(window);
	progress -= leftPart;

	if (progress < downPart) { //down
		Edge downEdge(x4, y4, x5, y5, thickness, color, SinglyDirected, 0, (downPart - progress) * totalLength - thickness * 0.5);
		downEdge.draw(window);
		return;
	}
	Edge downEdge(x4, y4, x5, y5, thickness, color, Undirected, 0, -thickness * 0.5);
	downEdge.draw(window);
	progress -= downPart;

	//right
	Edge rightEdge(x5, y5, x2, y2, thickness, color, SinglyDirected, 0, shorten + (rightPart - progress) * totalLength);
	rightEdge.draw(window);
}

void CircularEdge::setProgress(double newProgress) {
	progress = newProgress;
}
