#pragma once

#include <string>
#include <list>
#include <fstream>
#include <iostream>
#include <sstream>

class EditorViewer;

class FileObject
{
public:
    FileObject();
    ~FileObject();

    FileObject(const FileObject& other) = delete;
    FileObject(FileObject&& other) = delete;
    FileObject& operator= (const FileObject& other) = delete;
    FileObject& operator= (FileObject&& other) = delete;

    bool init(const std::string& fileName) noexcept;
    bool save() noexcept;
    std::string getLine(size_t n) const;
    size_t getNumOfLines() const;

    void insertCharToPos(int x, int y, const std::string& ch);
    void removeCharBeforePos(int x, int y);
    void removeCharAfterPos(int x, int y);
    void addLineToPos(int x, int y);

    friend class EditorViewer;

private:
    std::string fileName;
    std::string filePath;
    std::list<std::string> linesBuffer;
    size_t linesBufferSize;
};