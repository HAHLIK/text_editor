#include "editorViewer.h"


EditorViewer::EditorViewer() {}
EditorViewer::~EditorViewer() {}

void EditorViewer::setFontColor(const sf::Color& color) {this->fontColor = sf::Color(color);}
void EditorViewer::setBgColor(const sf::Color& color) {this->bgColor = sf::Color(color);}
void EditorViewer::setFont(const sf::Font& font) {this->font = font;}
void EditorViewer::setFontSize(int size) {this->fontSize = size;}

void EditorViewer::draw(sf::RenderWindow& window, FileObject& fileObject)
{
    int numberOfLines = window.getSize().y / fontSize / 1.5 - 1;
    int widthLines = window.getSize().x / fontSize;

    sf::Text textLine;
    textLine.setFillColor(fontColor);
    textLine.setFont(font);
    textLine.setCharacterSize(fontSize);
    
    std::string bufferString;
    for (int i = 1; i <= std::min(numberOfLines, (int)fileObject.getNumOfLines()); ++i) {
        bufferString += fileObject.getLine(i) + '\n';
    }
    textLine.setString(bufferString);
    window.clear(bgColor);
    window.draw(textLine);
}