#include <cassert>
#include <iostream>
#include "Stage.h"

Stage::Stage(sf::RenderWindow &_window, std::vector <std::string> _operationName, std::vector <std::vector <std::string> > _modeName, ColorTheme _theme) : 
	window(_window), operationName(_operationName), modeName(_modeName), theme(_theme){
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

	valueTypingBox = TypingBox(widthBox * 0.25, HEIGHT_RES - heightBox * 0.9, widthBox * 0.75f, heightBox * 0.8, true, font(fontType::Arial));
	indexTypingBox = TypingBox(widthBox * 1.25, HEIGHT_RES - heightBox * 0.9, widthBox * 0.75f, heightBox * 0.8, true, font(fontType::Arial));
}

void Stage::updateModeBox(int newMode) {
	for (int i = 0; i < numMode[curOperation]; i++) {
		modeBox[curOperation][i].setDrawable(false);
	}
	modeBox[curOperation][newMode].setDrawable(true);
	curMode = newMode;
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
	valueTypingBox.clickOn(x, y);
	indexTypingBox.clickOn(x, y);
}

void Stage::handleKeyPressed(int key) {
	if (valueTypingBox.isReading()) {
		valueTypingBox.readKey(key);
	}
	if (indexTypingBox.isReading()) {
		indexTypingBox.readKey(key);
	}
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
	indexTypingBox.draw(window, theme);
	valueTypingBox.draw(window, theme);
}

void Stage::stageUpdate(sf::Time deltaT) {
	indexTypingBox.update(deltaT);
	valueTypingBox.update(deltaT);
}

void Stage::setTheme(ColorTheme newTheme) {
	theme = newTheme;
}