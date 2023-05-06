#include "IngameSettings.h"
#include "Box.h"

IngameSettings::IngameSettings(double _x, double _y, double _width, double _height, DataStructure* _ds, ColorTheme theme) :
	x(_x), y(_y), width(_width), height(_height), ds(_ds),
	mediaControl(_x + _width * 0.1, _y + _height * 1 / 30, _width * 0.8, _height * 8 / 30, _ds),
	themeChoices(_x, _y + _height * 1 / 3, _width / 2, _height * 2 / 3, {"Light Theme", "Dark Theme"}, font(fontType::Prototype), theme),
	speedChoices(_x + _width * 0.5, _y + _height * 1 / 3, _width / 2, _height * 2 / 3, { "x0.25", "x0.5", "x1.0", "x2.0", "x4.0" }, font(fontType::Prototype), 2)
{

}

void IngameSettings::setDS(DataStructure* newDS) {
	ds = newDS;
	mediaControl.setDS(newDS);
}

int IngameSettings::handleMousePressed(double x, double y) {
	mediaControl.handleMousePressed(x, y);
	if (speedChoices.handleMousePressed(x, y)) {
		ds->setSpeed(speedList[speedChoices.getChoice()]);
	}
	if (themeChoices.handleMousePressed(x, y)) {
		return themeChoices.getChoice();
	};
	return -1;
}

void IngameSettings::handleMouseMove(double x, double y, sf::RenderWindow& window) {
	mediaControl.handleMouseMove(x, y, window);
}

void IngameSettings::handleMouseReleased(double x, double y) {
	mediaControl.handleMouseReleased(x, y);
}

void IngameSettings::handleKeyPressed(int key) {
	mediaControl.handleKeyPressed(key);
}

void IngameSettings::draw(sf::RenderWindow& window, ColorTheme theme) {
	Box outerBox(x, y, width, height, { MediaBox });
	outerBox.draw(window, theme);
	mediaControl.draw(window, theme);
	themeChoices.draw(window, theme);
	speedChoices.draw(window, theme);
}