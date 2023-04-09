#include "PlayButton.h"
#include "Template.h"

PlayButton::PlayButton(double x, double y, double radius, DataStructure* _ds) :
	circle("Images/Circle.png", x, y, radius * 2, radius * 2, playButtonCircleColor),
	triangle("Images/Triangle.png", x, y, radius * 1, radius * 1, playButtonTriangleColor),
	pause("Images/Pause.png", x, y, radius, radius, playButtonTriangleColor),
	replay("Images/Replay.png", x, y, radius * 1.2, radius * 1.2, playButtonTriangleColor),
	ds(_ds)
{
	triangle.setOrigin(triangle.sprite.getLocalBounds().width / 3, triangle.sprite.getLocalBounds().height / 2);
	replay.setOrigin(replay.sprite.getLocalBounds().width * 0.5 * 60 / 52, replay.sprite.getLocalBounds().height * 0.5 * 52 / 60);
}

void PlayButton::setDS(DataStructure* newDS) {
	ds = newDS;
}

void PlayButton::handleMousePressed(double mouseX, double mouseY) {
	if (circle.isMousePressed(mouseX, mouseY)) {
		if (ds->frameQueue.empty() && ds->listFrame.size() > 1) {
			ds->setIsAnimating(true);
			ds->setFrame(0);
		}
		else {
			ds->setIsAnimating(ds->isAnimating ^ 1);
		}
	}
}

void PlayButton::draw(sf::RenderWindow& window, ColorTheme theme) {
	circle.draw(window, theme);
	if (!ds->isAnimating) {
		triangle.draw(window, theme);
	}
	else {
		if (!ds->frameQueue.empty() || ds->listFrame.size() <= 1) {
			pause.draw(window, theme);
		}
		else {
			replay.draw(window, theme);
		}
	}
}