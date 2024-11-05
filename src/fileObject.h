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

    bool init(const std::string& fileName);
    std::string getLine(size_t n);
    size_t getNumOfLines();

private:
    std::vector<std::string> linesBuffer;
    size_t linesBufferSize;
};