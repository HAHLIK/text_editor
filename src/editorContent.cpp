#include "editorContent.h"


EditorContent::EditorContent(EditorViewer& editorViewer) : editorViewer (&editorViewer) {}
EditorContent::~EditorContent() {}

void EditorContent::insertTextToCursorPos(const std::string& text) 
{
    int cursor_x = editorViewer->cursorPos.first;
    int cursor_y = editorViewer->cursorPos.second;
    for (auto ch : text) {
        switch (ch)
        {
        case 13:
            cursor_y++; break;
        case 8: {
            editorViewer->fileObject->removeCharBeforePos(cursor_x, cursor_y);
            editorViewer->moveCursorLeft();
            break;
        }
        case 127:
            editorViewer->fileObject->removeCharAfterPos(cursor_x, cursor_y);
            break;

        default: {
            editorViewer->fileObject->insertCharToPos(cursor_x, cursor_y, text);
            editorViewer->moveCursorRight();
            break;
        } }
    }
}