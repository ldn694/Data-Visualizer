#include "BackButton.h"

BackButton::BackButton(double x, double y, double width, double height) :
	arrow("Images/back.png", x + width * 0.5, y + height * 0.5, width * 0.649929, height * 0.7, backButtonNormalOutlineColor),
	square("Images/curved_square.png", x + width * 0.5, y + height * 0.5, width, height, backButtonNormalOutlineColor),
	innerSquare("Images/curved_square.png", x + width * 0.5, y + height * 0.5, width * 0.85, height * 0.85, backButtonNormalFillColor)
{

}

bool BackButton::handleMousePressed(double x, double y) {
	return square.isMousePressed(x, y);
}

void BackButton::draw(sf::RenderWindow& window, ColorTheme theme) {
	square.draw(window, theme);
	innerSquare.draw(window, theme);
	arrow.draw(window, theme);
}