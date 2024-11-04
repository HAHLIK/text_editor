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

private:
    std::vector<std::string> linesBuffer;
};