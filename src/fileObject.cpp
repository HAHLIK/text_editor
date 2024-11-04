#include "fileObject.h"

FileObject::FileObject() {}
FileObject::~FileObject() {}

bool FileObject::init(const std::string& fileName) 
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: don't opening file";
        return false;
    }
    std::string lineBuffer;
    while (std::getline(inputFile, lineBuffer)) {
        linesBuffer.push_back(lineBuffer + '\n');
    }
    return true;
}