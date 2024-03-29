#include <cassert>
#include <iostream>
#include "Stage.h"

Stage::Stage(sf::RenderWindow& _window, std::vector <std::string> _operationName, std::vector <std::vector <std::string> > _modeName,
	std::vector <std::vector <std::vector <std::string> > > _valueName,
	std::vector <std::vector <std::vector <TypingBoxMode> > > _typingMode,
	std::vector <std::vector <std::vector <std::pair <int, int> > > > _valueBound,
	ColorTheme _theme, DataStructure* _ds) :
	window(_window), operationName(_operationName), modeName(_modeName), valueName(_valueName), typingMode(_typingMode), valueBound(_valueBound), theme(_theme),
	ingameSettings(widthBox * 2, HEIGHT_RES - heightBox * 3, WIDTH_RES - widthBox * 4, heightBox * 3, nullptr, _theme),
	backButton(0, 0, widthBox / 4, widthBox / 4),
	readFromFile(widthBox / 2, HEIGHT_RES - heightBox * 3 / 4, widthBox, heightBox / 2,
				0, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox, font(fontType::Prototype), maxSizeData, 0, maxValueData),
	ds(_ds), 
	lightBulb("Images/full_bulb.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 8 / 46 * 30, widthBox / 8, bulbColor),
	darkBulb("Images/empty_bulb.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 8 / 46 * 30, widthBox / 8, bulbColor),
	themeBox("Images/curved_square.png", WIDTH_RES - widthBox / 8, widthBox / 8, widthBox / 4, widthBox / 4, backButtonNormalFillColor)
{
	numOperation = operationName.size();
	operationBox.resize(numOperation);
	curOperation = 0;
	operating = false;
	operationSelecting = false;
	for (int i = 0; i < numOperation; i++) {
		operationBox[i] = Box(0, HEIGHT_RES - heightBox * 3, widthBox, heightBox, { CommandBoxNormal, CommandBoxSelected },
						operationName[i], font(fontType::Prototype), 50, WITH_BORDER, outlineBox);
		if (i != 0) {
			operationBox[i].setDrawable(false);
		}
	}

	outerGoBox = Box(widthBox, HEIGHT_RES - heightBox * 3, widthBox, heightBox, { CommandBoxNormal });
	goBox = Box(widthBox * 1.25f, HEIGHT_RES - heightBox * 2.75f, widthBox / 2.0f, heightBox / 2.0f, { GoBoxNormal, GoBoxSelected },
				"GO", font(fontType::Prototype), 30);

	assert(modeName.size() == numOperation);
	numMode.resize(numOperation);
	modeBox.resize(numOperation);
	for (int i = 0; i < numOperation; i++) {
		numMode[i] = modeName[i].size();
		modeBox[i].resize(numMode[i]);
		for (int j = 0; j < numMode[i]; j++) {
			modeBox[i][j] = Box(0, HEIGHT_RES - heightBox * 2, 2 * widthBox, heightBox, { CommandBoxNormal },
							modeName[i][j], font(fontType::Prototype), 30);
			modeBox[i][j].setDrawable(false);
		}
	}
	if (numOperation) {
		modeBox[0][0].setDrawable(true);
	}
	curMode = 0;

	prevModeButton = TriangleButton(widthBox / 5.0f, HEIGHT_RES - heightBox * 1.5f, 20, 3, -90.f);
	nextModeButton = TriangleButton(2 * widthBox - widthBox / 5.0f, HEIGHT_RES - heightBox * 1.5f, 20, 3, 90.f);
	upwardTriangle.setPointCount(3);
	upwardTriangle.setRadius(10);
	upwardTriangle.setOutlineThickness(0);
	upwardTriangle.setOrigin(upwardTriangle.getLocalBounds().left + upwardTriangle.getLocalBounds().width / 2, upwardTriangle.getLocalBounds().top + upwardTriangle.getLocalBounds().height / 2);
	upwardTriangle.setPosition(widthBox - widthBox * 0.06f, HEIGHT_RES - heightBox * 2.5f);
	upwarding = true;

	numValue.resize(numOperation);
	assert(valueName.size() == numOperation);
	assert(valueBound.size() == numOperation);
	assert(typingMode.size() == numOperation);
	for (int i = 0; i < numOperation; i++) {
		assert(valueName[i].size() == numMode[i]);
		assert(valueBound[i].size() == numMode[i]);
		assert(typingMode[i].size() == numMode[i]);
		numValue[i].resize(numMode[i]);
		for (int j = 0; j < numValue[i].size(); j++) {
			assert(valueName[i][j].size() == valueBound[i][j].size());
			assert(typingMode[i][j].size() == valueBound[i][j].size());
			numValue[i][j] = valueName[i][j].size();
		}
	}
	if (numOperation && numMode[0]) {
		updateModeBox(0);
	}
}

void Stage::setDS(DataStructure* newDS) {
	ingameSettings.setDS(newDS);
	ds = newDS;
}

void Stage::setDSName(std::string name) {
	dsName.setString(name);
	dsName.setFont(*font(fontType::Prototype));
	dsName.setCharacterSize(50);
	dsName.setOrigin(dsName.getLocalBounds().left + dsName.getLocalBounds().width / 2, dsName.getLocalBounds().top + dsName.getLocalBounds().height / 2);
	dsName.setPosition(WIDTH_RES / 2, 50);
}

void Stage::updateModeBox(int newMode) {
	for (int i = 0; i < numMode[curOperation]; i++) {
		modeBox[curOperation][i].setDrawable(false);
	}
	modeBox[curOperation][newMode].setDrawable(true);
	curMode = newMode;
	if (ds != nullptr) {
		ds->setCurMode(curMode);
	}
	if (modeName[curOperation][curMode] == "Upload File") {
		valueTypingBox.clear();
		readFromFile.reset();
		readFromFile.setDisplaying(true);
	}
	else {
		readFromFile.reset();
		valueTypingBox.resize(numValue[curOperation][curMode]);
		for (int i = 0; i < numValue[curOperation][curMode]; i++) {
			valueTypingBox[i] = BigTypingBox(2 * widthBox / numValue[curOperation][curMode] * i, HEIGHT_RES - heightBox, 2 * widthBox / numValue[curOperation][curMode], heightBox, widthBox / 3, outlineBox, valueName[curOperation][curMode][i],
				0, HEIGHT_RES - heightBox * 4 - outlineBox * 2, widthBox * 2, heightBox,
				typingMode[curOperation][curMode][i], font(fontType::Prototype), typingModeMaxCharacter[typingMode[curOperation][curMode][i]], valueBound[curOperation][curMode][i].first, valueBound[curOperation][curMode][i].second);
		}
	}
}

bool Stage::handleMousePressed(double x, double y) {
	handleMouseMove(x, y);
	if (!operationSelecting) {
		if (operationBox[curOperation].isInside(x, y)) {
			upwardTriangle.setRotation(180.f);
			operationSelecting = true;
			//operationBox[curOperation].setColorMode(CommandBoxSelected);
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
		upwardTriangle.setRotation(0.f);
		bool flag = false;
		for (int i = 0; i < numOperation; i++) {
			if (operationBox[i].isInside(x, y)) {
				operationSelecting = false;
				if (curOperation != i) {
					for (int j = 0; j < numMode[curOperation]; j++) {
						modeBox[curOperation][j].setDrawable(false);
					}
					curOperation = i;
					ds->setCurOperation(i);
					ds->resetAnimation();
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
	ingameSettings.handleMousePressed(x, y);
	readFromFile.handleMousePressed(x, y);
	if (themeBox.isMousePressed(x, y)) {
		setTheme(ColorTheme((theme + 1) % numColorTheme));
	}
	return backButton.handleMousePressed(x, y);
}

void Stage::handleKeyPressed(int key) {
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		if (valueTypingBox[i].isReading())
		{
			valueTypingBox[i].readKey(key);
		}
	}
	ingameSettings.handleKeyPressed(key);
	if (key == int(sf::Keyboard::Enter)) {
		operating = true;
	}
}

void Stage::handleMouseMove(double x, double y) {
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		if (valueTypingBox[i].handleMouseMove(x, y, window)) {
			return;
		}
	}
	window.setMouseCursor(arrowCursor);
	ingameSettings.handleMouseMove(x, y, window);
	for (int i = 0; i < numOperation; i++) {
		if (i == curOperation) {
			if (operationBox[i].handleMouseMove(x, y, window)) {
				upwarding = false;
			}
			else {
				upwarding = true;
			}
		}
		else {
			operationBox[i].handleMouseMove(x, y, window);
		}
	}
	goBox.handleMouseMove(x, y, window);
	prevModeButton.handleMouseMove(x, y, window);
	nextModeButton.handleMouseMove(x, y, window);
	themeBox.handleMouseMove(x, y, window);
	backButton.handleMouseMove(x, y, window);
	readFromFile.handleMouseMove(x, y, window);
}

void Stage::handleMouseReleased(double x, double y) {
	ingameSettings.handleMouseReleased(x, y);
}

void Stage::draw() {
	themeBox.draw(window, theme);
	if (theme == LightTheme) {
		lightBulb.draw(window, theme);
		dsName.setFillColor(BlackColor);
	}
	else {
		darkBulb.draw(window, theme);
		dsName.setFillColor(WhiteColor);
	}
	window.draw(dsName);
	outerGoBox.draw(window, theme);
	goBox.draw(window, theme);
	for (int i = 0; i < numOperation; i++) {
		for (int j = 0; j < numMode[i]; j++) {
			modeBox[i][j].draw(window, theme);
		}
	}
	prevModeButton.draw(window, theme);
	nextModeButton.draw(window, theme);
	if (theme == LightTheme) {
		if (upwarding) {
			upwardTriangle.setFillColor(BlackColor);
		}
		else {
			upwardTriangle.setFillColor(WhiteColor);
		}
	}
	else {
		if (upwarding) {
			upwardTriangle.setFillColor(WhiteColor);
		}
		else {
			upwardTriangle.setFillColor(BlackColor);
		}
	}
	if (numValue[curOperation][curMode]) {
		for (int i = 0; i < numValue[curOperation][curMode]; i++) {
			valueTypingBox[i].drawAll(window, theme);
		}
	}
	else {
		Box emptyBox(0, HEIGHT_RES - heightBox, widthBox * 2, heightBox, { CommandBoxNormal });
		emptyBox.draw(window, theme);
	}
	readFromFile.draw(window, theme);
	for (int i = 0; i < numOperation; i++) {
		operationBox[i].draw(window, theme);
	}
	ingameSettings.draw(window, theme);
	backButton.draw(window, theme);
	window.draw(upwardTriangle);
}

void Stage::stageUpdate(sf::Time deltaT) {
	for (int i = 0; i < numValue[curOperation][curMode]; i++) {
		valueTypingBox[i].update(deltaT);
	}
	ingameSettings.update(deltaT);
}

void Stage::setTheme(ColorTheme newTheme) {
	theme = newTheme;
	ds->setTheme(theme);
}