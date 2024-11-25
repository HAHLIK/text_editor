#include "editorViewer.h"


EditorViewer::EditorViewer() {}
EditorViewer::~EditorViewer() {}

void EditorViewer::setFontColor(const sf::Color& color) {this->fontColor = sf::Color(color);}
void EditorViewer::setBgColor(const sf::Color& color) {this->bgColor = sf::Color(color);}
void EditorViewer::setFont(const sf::Font& font) {this->font = font;}
void EditorViewer::setFontSize(int size) {
    this->fontSize = size;
    this-> lineHeight = fontSize * 1.5f;
}

void EditorViewer::init(sf::RenderWindow& window, const FileObject& fileObject)                                                    
{
    this->window = &window;
    this->fileObject = &fileObject;
    this->setWindowSizeInChar();
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
    if (cursorPos.second > currentPos.second + windowSizeInChar.second - 5 &&
    (currentPos.second + windowSizeInChar.second < fileObject->getNumOfLines()))
        currentPos.second++;

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
    if (currentPos.second >= fileObject->getNumOfLines() - windowSizeInChar.second) return;
    currentPos.second++;
}


void EditorViewer::draw() const
{
    window->clear(bgColor);

    int endLine = std::min(windowSizeInChar.second + currentPos.second,
        (int)fileObject->getNumOfLines());

    sf::Text textBuffer;
    textBuffer.setFont(font);
    textBuffer.setCharacterSize(fontSize);
 
    std::string bufferText;
    std::string bufferNLines;

    for (int nLine = currentPos.second; nLine <= endLine; ++nLine) 
    {
        std::string nLineString = std::to_string(nLine);
        nLineString.insert(0, LEFT_BOARD_WIDTH/2 - nLineString.size(), ' ');
        textBuffer.setString(nLineString);
        textBuffer.setPosition(sf::Vector2f(0.f, 
            lineHeight * (nLine - currentPos.second)));
        textBuffer.setFillColor(sf::Color(150, 150, 150));
        window->draw(textBuffer);

        std::string currentLine = fileObject->getLine(nLine);
        std::string bufferLine = "";
        for (int nChar = currentPos.first; nChar <= currentLine.size(); ++nChar)
            bufferLine += currentLine[nChar-1];
        textBuffer.setString(bufferLine);
        textBuffer.setFillColor(fontColor);
        textBuffer.setPosition(sf::Vector2f(fontSize/2 * LEFT_BOARD_WIDTH,                                                                                                                   
            lineHeight * (nLine - currentPos.second)));
        window->draw(textBuffer);
    }

    sf::RectangleShape CursorRect(sf::Vector2f(fontSize/10, lineHeight));
    CursorRect.setFillColor(sf::Color::White);
    CursorRect.setPosition((cursorPos.first - currentPos.first + LEFT_BOARD_WIDTH) * fontSize/2, 
                          (cursorPos.second - currentPos.second) * lineHeight);
    window->draw(CursorRect);

    sf::RectangleShape boardLine(sf::Vector2f(fontSize/20, window->getSize().y));
    boardLine.setFillColor(sf::Color(130, 130, 130));
    boardLine.setPosition(sf::Vector2f(fontSize/2 * (LEFT_BOARD_WIDTH - 1), 0.f));
    window->draw(boardLine);
}


void EditorViewer::setWindowSizeInChar()
{
    if (this->window == nullptr) return;
    this->windowSizeInChar.first = window->getSize().x / (fontSize/2) - LEFT_BOARD_WIDTH;
    this->windowSizeInChar.second = window->getSize().y / lineHeight;
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
        currentPos.second = std::min(cursorPos.second - windowSizeInChar.second + 5, 
            (int)fileObject->getNumOfLines() - windowSizeInChar.second);
}
