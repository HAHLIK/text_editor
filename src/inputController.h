#pragma once

#include "editorViewer.h"

class InputController
{
public:
    InputController(EditorViewer& editorViewer);
    ~InputController();

    InputController(const InputController& other) = delete;
    InputController(InputController&& other) = delete;
    InputController& operator= (const InputController& other) = delete;
    InputController& operator= (InputController&& other) = delete;

    void handleEvents(const sf::Event& events);


private:
    EditorViewer* editorViewer = nullptr;

    void handleConstantEvent(const sf::Event& event);
    void handleMouseEvent(const sf::Event& event);
    void handleKeyEvent(const sf::Event& event);
    void handleEnteredEvent(const sf::Event& event);
};