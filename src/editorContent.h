#pragma once
#include <string>
#include "editorViewer.h"


class EditorContent
{
public:
    EditorContent(EditorViewer& editorViewer);
    ~EditorContent();
    EditorContent(const EditorContent& other) = delete;
    EditorContent(EditorContent&& other) = delete;
    EditorContent& operator= (const EditorContent& other) = delete;
    EditorContent& operator= (EditorContent&& other) = delete;

    void insertTextToCursorPos(const std::string& text);

private:
    EditorViewer* editorViewer = nullptr; 
};