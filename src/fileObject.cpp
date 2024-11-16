#include "fileObject.h"

FileObject::FileObject() {}
FileObject::~FileObject() {}

bool FileObject::init(const std::string& fileName) noexcept 
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: don't opening file" << std::endl;
        return false;
    }
    std::string lineBuffer;
    while (std::getline(inputFile, lineBuffer)) {
        linesBuffer.push_back(lineBuffer);
    }
    linesBufferSize = linesBuffer.size();
    inputFile.close();
    return true;
}

std::string FileObject::getLine(size_t n) const 
{   
    if (1 > n || n > linesBufferSize) {
        std::cerr << n << " is not valid number line" << std::endl;
        return "";
    }
    return linesBuffer[n-1];
}
size_t FileObject::getNumOfLines() const { return linesBufferSize; }