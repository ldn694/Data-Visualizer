#include "BackButton.h"

BackButton::BackButton(double x, double y, double width, double height) :
	arrow("Images/back.png", x + width * 0.5, y + height * 0.5, width * 0.649929, height * 0.7, backButtonNormalOutlineColor),
	square("Images/curved_square.png", x + width * 0.5, y + height * 0.5, width, height, backButtonNormalOutlineColor),
	innerSquare("Images/curved_square.png", x + width * 0.5, y + height * 0.5, width * 0.9, height * 0.9, backButtonNormalFillColor)
{

}

bool BackButton::handleMousePressed(double x, double y) {
	return square.isMousePressed(x, y);
}

void BackButton::handleMouseMove(double x, double y, sf::RenderWindow& window) {
	if (square.isMousePressed(x, y)) {
		window.setMouseCursor(handCursor);
	}
}

void BackButton::draw(sf::RenderWindow& window, ColorTheme theme) {
	square.draw(window, theme);
	innerSquare.draw(window, theme);
	arrow.draw(window, theme);
}