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
    linesBufferSize = linesBuffer.size();
    return true;
}

std::string FileObject::getLine(size_t n) 
{   
    if (1 > n || n > linesBufferSize) {
        std::cerr << n << " is not valid number line\n";
        return "";
    }
    return linesBuffer[n-1];
}
size_t FileObject::getNumOfLines() { return linesBufferSize; }