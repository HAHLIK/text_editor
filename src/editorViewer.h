#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "fileObject.h"

class EditorViewer
{
    public:
        EditorViewer();
        ~EditorViewer();

        EditorViewer(const EditorViewer& other) = delete;
        EditorViewer(EditorViewer&& other) = delete;
        EditorViewer& operator= (const EditorViewer& other) = delete;
        EditorViewer& operator= (EditorViewer&& other) = delete;

        void setFontColor(const sf::Color& color);
        void setBgColor(const sf::Color& color);
        void setFont(const sf::Font& font);
        void setFontSize(int size);

        void draw(sf::RenderWindow& window, FileObject& fileObject);

    private:
        sf::Color fontColor;
        sf::Color bgColor;
        sf::Font font;
        int fontSize;
};