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
    setWindowSizeInChar();
}

void EditorViewer::setCameraBounds(int width, int height)
{
    window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
    setWindowSizeInChar();
}

void EditorViewer::moveRight() 
{
    if (fileObject->getLine(cursorPos.second).size() >= cursorPos.first) 
        cursorPos.first++;
    if (cursorPos.first >= currentPos.first + windowSizeInChar.first)
        currentPos.first++;
}
void EditorViewer::moveLeft() 
{
    if (cursorPos.first > 1) cursorPos.first--;
    if (cursorPos.first < currentPos.first)
        currentPos.first--;
}
void EditorViewer::moveDown() 
{   
    if (cursorPos.second == fileObject->getNumOfLines()) return;
    cursorPos.second++;
    if (cursorPos.second > currentPos.second + windowSizeInChar.second - 5 &&
    (currentPos.second + windowSizeInChar.second < fileObject->getNumOfLines()))
        currentPos.second++;

    cursorPos.first = std::min((int)fileObject->getLine(cursorPos.second).size()+1,
                                cursorPos.first);
}
void EditorViewer::moveUp() 
{
    if (cursorPos.second == 1) return;
    cursorPos.second--;
    if (cursorPos.second < currentPos.second + 5 && currentPos.second > 1)
        currentPos.second--;

    cursorPos.first = std::min((int)fileObject->getLine(cursorPos.second).size()+1,
                                cursorPos.first);
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
