#pragma once

#include "editorViewer.h"
#include "editorContent.h"

class InputController
{
public:
    InputController(EditorViewer& editorViewer, EditorContent& EditorContent);
    ~InputController();

    InputController(const InputController& other) = delete;
    InputController(InputController&& other) = delete;
    InputController& operator= (const InputController& other) = delete;
    InputController& operator= (InputController&& other) = delete;

    void handleEvents(const sf::Event& events);

private:
    EditorViewer* editorViewer = nullptr;
    EditorContent* editorContent = nullptr;

    void handleConstantEvent(const sf::Event& event);
    void handleMouseEvent(const sf::Event& event);
    void handleKeyEvent(const sf::Event& event);
    void handleEnteredEvent(const sf::Event& event);
};