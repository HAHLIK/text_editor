#include "editorViewer.h"


EditorViewer::EditorViewer() {}
EditorViewer::~EditorViewer() {}

void EditorViewer::setFontColor(const sf::Color& color) {this->fontColor = sf::Color(color);}
void EditorViewer::setBgColor(const sf::Color& color) {this->bgColor = sf::Color(color);}
void EditorViewer::setFont(const sf::Font& font) {this->font = font;}
void EditorViewer::setFontSize(int size) {this->fontSize = size;}

void EditorViewer::init(sf::RenderWindow& window, const FileObject& fileObject) {
    this->window = &window;
    this->fileObject = &fileObject;
}

void EditorViewer::setCameraBounds(int width, int height) {
    window->setView(sf::View(sf::FloatRect(0.f, 0.f, width, height)));
}

void EditorViewer::moveRight() {
    currentXPos++;
}
void EditorViewer::moveLeft() {
    if (currentXPos != 1) currentXPos--;
}
void EditorViewer::moveDown() {   
    if ((int)(window->getSize().y / fontSize / 1.55 + currentYPos) <= 
        fileObject->getNumOfLines())
    currentYPos++;
}
void EditorViewer::moveUp() {
    if (currentYPos != 1) currentYPos--;
}


void EditorViewer::draw() const
{
    window->clear(bgColor);

    int endLine = std::min(window->getSize().y / fontSize / 1.5f + currentYPos,
        (float)fileObject->getNumOfLines());

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    
    std::string bufferText;
    std::string bufferNLines;
    for (int nLine = currentYPos; nLine <= endLine; ++nLine) 
    {
        std::string nLineString = std::to_string(nLine);
        nLineString.insert(0, 5 - nLineString.size(), ' ');
        bufferNLines += nLineString + '\n';

        std::string currentLine = fileObject->getLine(nLine);
        std::string bufferLine = "";
        for (int nChar = currentXPos; nChar <= currentLine.size(); ++nChar)
            bufferLine += currentLine[nChar-1];
        bufferText += bufferLine + '\n';
    }

    text.setFillColor(sf::Color(150, 150, 150));
    text.setString(bufferNLines);
    window->draw(text);

    text.setFillColor(fontColor);
    text.setPosition(sf::Vector2f(fontSize*5.f, 0.f));
    text.setString(bufferText);
    window->draw(text);
}
