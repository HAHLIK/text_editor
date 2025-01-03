#include "editorViewer.h"
#include <iostream>


EditorViewer::EditorViewer() {}
EditorViewer::~EditorViewer() {}

void EditorViewer::setFontColor(const sf::Color& color) {this->fontColor = sf::Color(color);}
void EditorViewer::setBgColor(const sf::Color& color) {this->bgColor = sf::Color(color);}
void EditorViewer::setFont(const sf::Font& font) {this->font = font;}

void EditorViewer::init(sf::RenderWindow& window, FileObject& fileObject)                                                    
{
    this->window = &window;
    this->fileObject = &fileObject;
    this->setWindowSizeInChar();
}
void EditorViewer::save() {
    if (fileSaved) return;
    fileObject->save();
    fileSaved = true;
 }
void EditorViewer::close() { window->close(); }

void EditorViewer::setCameraBounds(int width, int height)
{
    window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
    this->setWindowSizeInChar();
}

void EditorViewer::moveCursorRight() 
{
    if (fileObject->getLine(cursorPos.second).size() >= cursorPos.first) 
        cursorPos.first++;
    else if (cursorPos.second < fileObject->getNumOfLines()) {
        cursorPos.second++;
        cursorPos.first = 1;
    }
    this->normalizeCamera();
}

void EditorViewer::moveCursorLeft() 
{
    if (cursorPos.first > 1) cursorPos.first--;
    else if (cursorPos.second > 1) {
        cursorPos.second--;
        cursorPos.first = fileObject->getLine(cursorPos.second).size() + 1;
    }
    this->normalizeCamera();
}

void EditorViewer::moveCursorDown() 
{   
    if (cursorPos.second == fileObject->getNumOfLines()) return;
    cursorPos.second++;
    cursorPos.first = std::min((int)fileObject->getLine(cursorPos.second).size()+1,
                                cursorPos.first);
    this->normalizeCamera();
}

void EditorViewer::moveCursorUp() 
{
    if (cursorPos.second == 1) return;
    cursorPos.second--;
    cursorPos.first = std::min((int)fileObject->getLine(cursorPos.second).size()+1,
                                cursorPos.first);
    this->normalizeCamera();
}

void EditorViewer::scrolleUp() {
    if (currentPos.second <= 1) return;
    currentPos.second--; 
}

void EditorViewer::scrolleDown() {
    if (currentPos.second >= (int)fileObject->getNumOfLines() - windowSizeInChar.second) return;
    currentPos.second++;
}

void EditorViewer::home(bool mode) {
    if (mode) cursorPos.second = 1;
    cursorPos.first = 1;
    this->normalizeCamera();
}

void EditorViewer::end(bool mode) {
    if (mode) cursorPos.second = fileObject->getNumOfLines();
    cursorPos.first = fileObject->getLine(cursorPos.second).size() + 1;
    this->normalizeCamera();
}


void EditorViewer::draw() const
{
    window->clear(bgColor);

    std::string stringBuffer;
    sf::Text textBuffer;
    textBuffer.setFont(font);
    textBuffer.setCharacterSize(fontSize);

    auto startIt = fileObject->linesBuffer.begin();
    std::advance(startIt, currentPos.second-1);
    int endLine = std::min(windowSizeInChar.second, (int)fileObject->getNumOfLines()- currentPos.second);

    int i = 0;
    for (auto it = startIt; i <= endLine; ++i, ++it)
    {
        stringBuffer = std::to_string(i + currentPos.second);
        stringBuffer.insert(0, LEFT_BOARD_WIDTH/2 - stringBuffer.size()/2, ' ');

        textBuffer.setString(stringBuffer);
        textBuffer.setPosition(sf::Vector2f(0.f, 
            lineHeight * (i + 1)));
        textBuffer.setFillColor(sf::Color(150, 150, 150));

        window->draw(textBuffer);

        stringBuffer = "";
        for (int nChar = currentPos.first; nChar <= it->size(); ++nChar)
            stringBuffer += (*it)[nChar-1];
        textBuffer.setString(stringBuffer);
        textBuffer.setFillColor(fontColor);
        textBuffer.setPosition(sf::Vector2f(fontSize/2 * LEFT_BOARD_WIDTH,                                                                                                                   
            lineHeight * (i + 1)));

        window->draw(textBuffer);
    }

//Draw cursor
    sf::RectangleShape CursorRect(sf::Vector2f(fontSize/10, lineHeight));
    CursorRect.setFillColor(sf::Color::White);
    CursorRect.setPosition((cursorPos.first - currentPos.first + LEFT_BOARD_WIDTH) * fontSize/2, 
                          (cursorPos.second - currentPos.second + 1) * lineHeight);
    window->draw(CursorRect);

//Draw board line
    sf::RectangleShape boardLine(sf::Vector2f(fontSize/20, window->getSize().y));
    boardLine.setFillColor(sf::Color(130, 130, 130));
    boardLine.setPosition(sf::Vector2f(fontSize/2 * (LEFT_BOARD_WIDTH - 1), 0.f));
    window->draw(boardLine);

//Draw HotBar file
    sf::RectangleShape HotBar(sf::Vector2f(sf::Vector2f(window->getSize()).x, lineHeight));
    HotBar.setFillColor(sf::Color(52, 52, 52));
    HotBar.setOutlineColor(sf::Color(40, 40, 40));
    HotBar.setOutlineThickness(2);
    HotBar.setPosition(0, 0);

    if (fileSaved)
        textBuffer.setString("> " + fileObject->fileName);
    else
        textBuffer.setString("> " + fileObject->fileName + " [E]");
        
    textBuffer.setCharacterSize(fontSize - 2);
    textBuffer.setFillColor(sf::Color(190, 190, 190));

    textBuffer.setPosition(fontSize, lineHeight/10);

    window->draw(HotBar);
    window->draw(textBuffer);
}


void EditorViewer::setWindowSizeInChar()
{
    if (this->window == nullptr) return;
    this->windowSizeInChar.first = window->getSize().x / charWidth - LEFT_BOARD_WIDTH;
    this->windowSizeInChar.second = window->getSize().y / lineHeight - 1;
}

void EditorViewer::normalizeCamera()
{
    if (cursorPos.first < currentPos.first + 2) 
        currentPos.first = std::max(cursorPos.first - 2, 1);
    else if(cursorPos.first > currentPos.first + windowSizeInChar.first - 2)
        currentPos.first = std::max(cursorPos.first - windowSizeInChar.first + 2, 1);
    if (cursorPos.second < currentPos.second + 5)
        currentPos.second = std::max(cursorPos.second - 5, 1);
    else if (cursorPos.second > currentPos.second + windowSizeInChar.second - 5) 
        currentPos.second = std::max(std::min(cursorPos.second - windowSizeInChar.second + 5, 
            (int)fileObject->getNumOfLines() - windowSizeInChar.second), 1);
}

void EditorViewer::normalizeCursor()
{
    cursorPos.first = std::max(std::min(cursorPos.first, 
        (int)fileObject->getLine(cursorPos.second).size() + 1), 1);
    cursorPos.second = std::min(cursorPos.second, 
        (int)fileObject->getNumOfLines());
}

std::pair<int, int> EditorViewer::windowCoordToDocCoord(std::pair<int, int> windowCoord) const
{
    std::pair<int, int> docCoord;
    docCoord.first = std::max(windowCoord.first / charWidth - 10, 0) + currentPos.first;
    docCoord.second = std::max(windowCoord.second / lineHeight - 1, 0) + currentPos.second;
    return docCoord;
}
