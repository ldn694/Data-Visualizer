#include <cassert>
#include <iostream>
#include "Stage.h"

Stage::Stage(sf::RenderWindow &_window, std::vector <std::string> _operationName, std::vector <std::vector <std::string> > _modeName, 
	std::vector <std::vector <std::vector <std::string> > > _valueName, 
	std::vector <std::vector <std::vector <std::pair <int, int> > > > _valueBound, 
	ColorTheme _theme) :
	window(_window), operationName(_operationName), modeName(_modeName), valueName(_valueName), valueBound(_valueBound), theme(_theme){
	numOperation = operationName.size();
	operationBox.resize(numOperation);
	curOperation = 0;
	operating = false;
	operationSelecting = false;
	for (int i = 0; i < numOperation; i++) {
		operationBox[i] = Box(0, HEIGHT_RES - heightBox * 3, widthBox, heightBox, { CommandBoxNormal, CommandBoxSelected },
						operationName[i], font(fontType::Arial), 50, WITH_BORDER, outlineBox);
		if (i != 0) {
			operationBox[i].setDrawable(false);
		}
	}

	outerGoBox = Box(widthBox, HEIGHT_RES - heightBox * 3, widthBox, heightBox, { CommandBoxNormal });
	goBox = Box(widthBox * 1.25f, HEIGHT_RES - heightBox * 2.75f, widthBox / 2.0f, heightBox / 2.0f, { GoBoxNormal },
				"GO", font(fontType::Arial), 30);

	assert(modeName.size() == numOperation);
	numMode.resize(numOperation);
	modeBox.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		numMode[i] = modeName[i].size();
		modeBox[i].resize(numMode[i]);
		for (int j = 0; j < numMode[i]; j++) {
			modeBox[i][j] = Box(0, HEIGHT_RES - heightBox * 2, 2 * widthBox, heightBox, { CommandBoxNormal },
							modeName[i][j], font(fontType::Arial), 30);
			modeBox[i][j].setDrawable(false);
		}
	}
	if (numOperation) {
		modeBox[0][0].setDrawable(true);
	}
	curMode = 0;

	prevModeButton = TriangleButton(widthBox / 5.0f, HEIGHT_RES - heightBox * 1.5f, 20, 5, -90.f);
	nextModeButton = TriangleButton(2 * widthBox - widthBox / 5.0f, HEIGHT_RES - heightBox * 1.5f, 20, 5, 90.f);

	numValue.resize(numOperation);
	assert(valueName.size() == numOperation);
	assert(valueBound.size() == numOperation);
	for (int i = 0; i < numOperation; i++) {
		assert(valueName[i].size() == numMode[i]);
		assert(valueBound[i].size() == numMode[i]);
		numValue[i].resize(numMode[i]);
		for (int j = 0; j < numValue[i].size(); j++) {
			assert(valueName[i][j].size() == valueBound[i][j].size());
			numValue[i][j] = valueName[i][j].size();
		}
	}
	if (numOperation && numMode[0]) {
		updateModeBox(0);
	}

	scrubber = Scrubber(2 * widthBox, HEIGHT_RES - heightBox, 2 * widthBox, heightScrubber, zipWidth);

}

void Stage::updateModeBox(int newMode) {
	for (int i = 0; i < numMode[curOperation]; i++) {
		modeBox[curOperation][i].setDrawable(false);
	}
	modeBox[curOperation][newMode].setDrawable(true);
	curMode = newMode;
	valueTypingBox.resize(numValue[curOperation][curMode]);
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		valueTypingBox[i] = BigTypingBox(0, HEIGHT_RES - heightBox, widthBox, heightBox, outlineBox, valueName[curOperation][curMode][i],
			true, font(fontType::Arial), valueBound[curOperation][curMode][i].first, valueBound[curOperation][curMode][i].second);
	}
}

void Stage::handleMousePressed(double x, double y) {
	if (!operationSelecting) {
		if (operationBox[curOperation].isInside(x, y)) {
			operationSelecting = true;
			operationBox[curOperation].setColorMode(CommandBoxSelected);
			double x1 = 0, y1 = HEIGHT_RES - heightBox * 3;
			for (int i = 0; i < numOperation; i++) {
				if (i == curOperation) {
					continue;
				}
				y1 -= heightBox;
				operationBox[i].setPosition(x1, y1);
				operationBox[i].setColorMode(CommandBoxNormal);
				operationBox[i].setDrawable(true);
			}
		}
	}
	else {
		bool flag = false;
		for (int i = 0; i < numOperation; i++) {
			if (operationBox[i].isInside(x, y)) {
				operationSelecting = false;
				if (curOperation != i) {
					for (int j = 0; j < numMode[curOperation]; j++) {
						modeBox[curOperation][j].setDrawable(false);
					}
					curOperation = i;
					updateModeBox(0);
				}
				for (int j = 0; j < numOperation; j++) {
					operationBox[j].setPosition(0, HEIGHT_RES - heightBox * 3);
					operationBox[j].setColorMode(CommandBoxNormal);
					operationBox[j].setDrawable(false);
				}
				operationBox[curOperation].setDrawable(true);
				flag = true;
				break;
			}
		}
		if (!flag) {
			operationSelecting = false;
			for (int i = 0; i < numOperation; i++) {
				operationBox[i].setPosition(0, HEIGHT_RES - heightBox * 3);
				operationBox[i].setColorMode(CommandBoxNormal);
				operationBox[i].setDrawable(false);
			}
			operationBox[curOperation].setDrawable(true);
		}
	}
	if (goBox.isInside(x, y)) {
		operating = true;
	}
	if (prevModeButton.isInside(x, y)) {
		updateModeBox((curMode + numMode[curOperation] - 1) % numMode[curOperation]);
	}
	if (nextModeButton.isInside(x, y)) {
		updateModeBox((curMode + numMode[curOperation] + 1) % numMode[curOperation]);
	}
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		valueTypingBox[i].clickOn(x, y);
	}
	scrubber.handleMousePressed(x, y);
}

void Stage::handleKeyPressed(int key) {
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		if (valueTypingBox[i].isReading()) {
			valueTypingBox[i].readKey(key);
		}
	}
	scrubber.handleKeyPressed(key);
}

void Stage::handleMouseMove(double x, double y) {
	scrubber.handleMouseMove(x, y);
}

void Stage::handleMouseReleased(double x, double y) {
	scrubber.handleMouseReleased(x, y);
}

void Stage::draw() {
	for (int i = 0; i < numOperation; i++) {
		operationBox[i].draw(window, theme);
	}
	outerGoBox.draw(window, theme);
	goBox.draw(window, theme);
	for (int i = 0; i < numOperation; i++) {
		for (int j = 0; j < numMode[i]; j++) {
			modeBox[i][j].draw(window, theme);
		}
	}
	prevModeButton.draw(window, theme);
	nextModeButton.draw(window, theme);
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		valueTypingBox[i].drawAll(window, theme);
	}
	scrubber.draw(window, theme);
}

void Stage::stageUpdate(sf::Time deltaT) {
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		valueTypingBox[i].update(deltaT);
	}
}

void Stage::setTheme(ColorTheme newTheme) {
	theme = newTheme;
}