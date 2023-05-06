#include "ReadFromFile.h"
#include "Box.h"

static HWND hwnd;
static TCHAR szFileName[MAX_PATH];

ReadFromFile::ReadFromFile(double _x, double _y, double _width, double _height,
    double _xWarning, double _yWarning, double _widthWarning, double _heightWarning,
    sf::Font* _font, int _maxSize, int _minValue, int _maxValue) :
    x(_x), y(_y), width(_width), height(_height), 
    xWarning(_xWarning), yWarning(_yWarning), widthWarning(_widthWarning), heightWarning(_heightWarning),
    font(_font), maxSize(_maxSize), minValue(_minValue), maxValue(_maxValue),
    isDisplaying(false), displayingWarning(false), fileName("Choose file") {}

void ReadFromFile::handleMousePressed(double mouseX, double mouseY) {
    if (mouseX < x || mouseX > x + width || mouseY < y || mouseY > y + height || !isDisplaying) {
        return;
    }
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0";
    ofn.lpstrFile = szFileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
    ofn.lpstrDefExt = L"txt";
    if (GetOpenFileName(&ofn) == TRUE) {
        std::wstring filePath(ofn.lpstrFile);
        std::size_t lastSlashPos = filePath.find_last_of('\\');
        std::wstring wfileName = filePath.substr(lastSlashPos + 1);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string fileNameUtf8 = converter.to_bytes(wfileName);
        fileName = fileNameUtf8;
        std::cout << fileName << "\n";

        std::wstring filePath2(ofn.lpstrFile);
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter2;
        address = converter2.to_bytes(filePath2);
        std::cout << address << "\n";
        setWarning();
    }
    else {
        // User cancelled the dialog
    }
    ofn.lpstrFile = NULL;
    ofn.lpstrFileTitle = NULL;
    ofn.lpstrFilter = NULL;
    ofn.lpstrCustomFilter = NULL;
    ofn.nMaxFile = 0;
    ofn.nMaxCustFilter = 0;
    ofn.lpstrTitle = NULL;
    ofn.lpstrInitialDir = NULL;
}

void ReadFromFile::handleMouseMove(double mouseX, double mouseY, sf::RenderWindow& window) {
    if (mouseX < x || mouseX > x + width || mouseY < y || mouseY > y + height || !isDisplaying) {
        return;
    }
    window.setMouseCursor(handCursor);
}

void ReadFromFile::draw(sf::RenderWindow& window, ColorTheme theme) {
    if (fileName != "Choose file") {
        setWarning();
    }
    if (isDisplaying) {
        Box box(x, y, width, height, { ColorBoxType::UploadBox }, fileName, font, 30, true, 1);
        box.draw(window, theme);
        if (displayingWarning) {
            sf::RectangleShape tmpRect(sf::Vector2f(widthWarning, heightWarning));
            tmpRect.setPosition(xWarning, yWarning);
            tmpRect.setFillColor(warningFillColor[theme]);
            window.draw(tmpRect);
            sf::Text WarningText = CompressWords(warning,
                xWarning, yWarning, widthWarning, heightWarning,
                font, 25, warningTextColor[theme]);
            window.draw(WarningText);
        }
    }
}

std::vector <int> ReadFromFile::getListInt() {
    std::ifstream fi(address);
    std::vector <int> tmp;
    while (!fi.eof()) {
        std::string line;
        std::getline(fi, line);
        int i = 0;
        std::string valText;
        std::string curText = line + ",";
        while (i < curText.size()) {
            if (curText[i] == ',' || curText[i] == ' ') {
                if (!valText.empty()) {
                    tmp.push_back(stringToInt(valText));
                    valText.clear();
                    if (tmp.size() > maxSize) {
                        return { -4 };
                    }
                }
                i++;
                continue;
            }
            if (curText[i] < '0' || curText[i] > '9') {
                fi.close();
                return { -1 };
            }
            valText.push_back(curText[i]);
            if (valText.size() > 9) {
                fi.close();
                return { -3 };
            }
            if (stringToInt(valText) < minValue || stringToInt(valText) > maxValue) {
                fi.close();
                return { -2 };
            }
            i++;
        }
    }
    fi.close();
    return tmp;
}

void ReadFromFile::setWarning() {
    std::vector <int> tmp = getListInt();
    if (!tmp.empty() && tmp[0] == -1) {
        displayingWarning = true;
        warning = "Illegar character found, character must be space, comma, or number (0..9)!";
        return;
    }
    if (!tmp.empty() && (tmp[0] == -2 || tmp[0] == -3)) {
        displayingWarning = true;
        warning = "Value must be in [";
        warning = warning + intToString(minValue) + "," + intToString(maxValue) + "]!";
        return;
    }
    if (!tmp.empty() && (tmp[0] == -4)) {
        displayingWarning = true;
        warning = "Maximum size is " + intToString(maxSize);
        return;
    }
    displayingWarning = false;
}

void ReadFromFile::setDisplaying(bool val) {
    isDisplaying = val;
}

bool ReadFromFile::getDisplaying() {
    return isDisplaying;
}

void ReadFromFile::reset() {
    isDisplaying = false;
    displayingWarning = false;
    fileName = "Choose file";
    address = address = "";
}