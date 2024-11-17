#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "fileObject.h"

#define LEFT_BOARD_WIDTH 10

class EditorViewer
{
    public:
        EditorViewer();
        ~EditorViewer();

        EditorViewer(const EditorViewer& other) = delete;
        EditorViewer(EditorViewer&& other) = delete;
        EditorViewer& operator= (const EditorViewer& other) = delete;
        EditorViewer& operator= (EditorViewer&& other) = delete;

        void init(sf::RenderWindow& window, const FileObject& fileObject);

        void setFontColor(const sf::Color& color);
        void setBgColor(const sf::Color& color);
        void setFont(const sf::Font& font);
        void setFontSize(int size);
        
        void moveRight();
        void moveLeft();
        void moveUp();
        void moveDown();

        void setCameraBounds(int width, int height);
        void draw() const;

    private:
        void setWindowSizeInChar();

        sf::RenderWindow* window = nullptr;
        const FileObject* fileObject;

        std::pair<int, int> currentPos = std::pair<int, int>(1, 1);
        std::pair<int, int> cursorPos = std::pair<int, int>(1, 1);
        std::pair<int, int> windowSizeInChar;

        sf::Color fontColor;
        sf::Color bgColor;
        sf::Font font;
        int fontSize;
        int lineHeight;
};