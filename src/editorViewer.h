#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "fileObject.h"

#define LEFT_BOARD_WIDTH 10

class InputController;
class EditorContent;

class EditorViewer
{
    public:
        EditorViewer();
        ~EditorViewer();

        EditorViewer(const EditorViewer& other) = delete;
        EditorViewer(EditorViewer&& other) = delete;
        EditorViewer& operator= (const EditorViewer& other) = delete;
        EditorViewer& operator= (EditorViewer&& other) = delete;

        void init(sf::RenderWindow& window, FileObject& fileObject);
        void save();
        void close();

        void setFontColor(const sf::Color& color);
        void setBgColor(const sf::Color& color);
        void setFont(const sf::Font& font);
        
        void moveCursorRight();
        void moveCursorLeft();
        void moveCursorUp();
        void moveCursorDown();
        void scrolleUp();
        void scrolleDown();
        void home(bool mode = false);
        void end(bool mode = false);

        void setCameraBounds(int width, int height);
        void draw() const;

        friend class InputController;
        friend class EditorContent;

    private:
        void setWindowSizeInChar();
        void normalizeCamera();
        void normalizeCursor();
        std::pair<int, int> windowCoordToDocCoord(std::pair<int, int> windowCoord) const;

        sf::RenderWindow* window = nullptr;
        FileObject* fileObject = nullptr;
        bool fileSaved = true;

        std::pair<int, int> currentPos = std::pair<int, int>(1, 1);
        std::pair<int, int> cursorPos = std::pair<int, int>(1, 1);
        std::pair<int, int> windowSizeInChar;

        sf::Color fontColor;
        sf::Color bgColor;
        sf::Font font;
        int fontSize = 20;
        int lineHeight = 20 * 1.5f;
        int charWidth = 20 / 2;
};