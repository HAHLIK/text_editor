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
        case 8:
            editorViewer->moveCursorLeft();
            editorViewer->fileObject->removeCharBeforePos(cursor_x, cursor_y);
            break;
        case 9:
            editorViewer->fileObject->insertTextToPos(cursor_x, cursor_y, "    ");
            for (int i = 0; i < 4; ++i) editorViewer->moveCursorRight();
            break;
        case 13:
            editorViewer->fileObject->addLineToPos(cursor_x, cursor_y);
            editorViewer->moveCursorDown();
            editorViewer->home();
            break;
        case 127:
            editorViewer->fileObject->removeCharAfterPos(cursor_x, cursor_y);
            break;

        default: {
            editorViewer->fileObject->insertTextToPos(cursor_x, cursor_y, text);
            editorViewer->moveCursorRight();
            break;
        } }
    }
}