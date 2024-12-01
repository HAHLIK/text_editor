#include "inputController.h"


InputController::InputController(EditorViewer& editorViewer) : 
    editorViewer (&editorViewer) {};
InputController::~InputController() {};


void InputController::handleEvents(const sf::Event& event) 
{
    this->handleKeyEvent(event);
    this->handleConstantEvent(event);
    this->handleMouseEvent(event);
    this->handleEnteredEvent(event);
}

void InputController::handleConstantEvent(const sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        editorViewer->close();
    else if (event.type == sf::Event::Resized)
        editorViewer->setCameraBounds(event.size.width, event.size.height);
}

void InputController::handleMouseEvent(const sf::Event& event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            if (event.mouseWheelScroll.delta > 0)
                editorViewer->scrolleUp();
            else editorViewer->scrolleDown();
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        auto mousePos = sf::Mouse::getPosition(*(editorViewer->window));
        std::pair<int, int> mousePosI(mousePos.x, mousePos.y);
        editorViewer->cursorPos = editorViewer->windowCoordToDocCoord(mousePosI);
        editorViewer->normalizeCursor();
    }
}

void InputController::handleKeyEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed) return;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        editorViewer->moveCursorDown();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        editorViewer->moveCursorUp();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        editorViewer->moveCursorRight();
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        editorViewer->moveCursorLeft();
}

void InputController::handleEnteredEvent(const sf::Event& event)
{
    
}