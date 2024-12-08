#include "fileObject.h"

FileObject::FileObject() {}
FileObject::~FileObject() {}

bool FileObject::init(const std::string& fileName) noexcept
{
    this->fileName = fileName;
    this->fileName.erase(0, this->fileName.find_last_of('/') + 1);

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
std::string FileObject::getFileName() const { return fileName; }

void FileObject::insertCharToPos(int x, int y, const std::string& ch) 
{
    if (x-1 < linesBuffer[y-1].size())
        linesBuffer[y-1].insert(x-1, ch);
    else
        linesBuffer[y-1].append(ch);
}
void FileObject::removeCharBeforePos(int x, int y)
{
    if (x - 2 >= 0)
        linesBuffer[y-1].erase(x-2, 1);
}
void FileObject::removeCharAfterPos(int x, int y)
{
    if (x <= linesBuffer[y-1].size())
        linesBuffer[y-1].erase(x-1, 1);
    // else if (y < linesBufferSize)
    //     linesBuffer[y-1].append(linesBuffer[y]);
}