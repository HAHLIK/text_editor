#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "fileObject.h"

#define LEFT_BOARD_WIDTH 10

class InputController;

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
        void close();

        void setFontColor(const sf::Color& color);
        void setBgColor(const sf::Color& color);
        void setFont(const sf::Font& font);
        void setFontSize(int size);
        
        void moveCursorRight();
        void moveCursorLeft();
        void moveCursorUp();
        void moveCursorDown();
        void scrolleUp();
        void scrolleDown();

        void setCameraBounds(int width, int height);
        void draw() const;

        friend class InputController;

    private:
        void setWindowSizeInChar();
        void normalizeCamera();
        void normalizeCursor();
        std::pair<int, int> windowCoordToDocCoord(std::pair<int, int> windowCoord);

        sf::RenderWindow* window = nullptr;
        const FileObject* fileObject = nullptr;

        std::pair<int, int> currentPos = std::pair<int, int>(1, 1);
        std::pair<int, int> cursorPos = std::pair<int, int>(1, 1);
        std::pair<int, int> windowSizeInChar;

        sf::Color fontColor;
        sf::Color bgColor;
        sf::Font font;
        int fontSize;
        int lineHeight;
};