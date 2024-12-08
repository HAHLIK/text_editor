#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>


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
    std::string getLine(size_t n) const;
    size_t getNumOfLines() const;
    std::string getFileName() const;

    void insertCharToPos(int x, int y, const std::string& ch);
    void removeCharBeforePos(int x, int y);
    void removeCharAfterPos(int x, int y);

private:
    std::string fileName;
    std::vector<std::string> linesBuffer;
    size_t linesBufferSize;
};