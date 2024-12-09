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
    while (std::getline(inputFile, lineBuffer)) 
        linesBuffer.push_back(lineBuffer);
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
    auto it = linesBuffer.begin();
    std::advance(it, n-1);
    std::string str = *it;
    return str;
}

size_t FileObject::getNumOfLines() const { return linesBufferSize; }
std::string FileObject::getFileName() const { return fileName; }

void FileObject::insertCharToPos(int x, int y, const std::string& ch) 
{
    auto line = linesBuffer.begin();
    std::advance(line, y-1);
    if (x-1 < line->size())
        line->insert(x-1, ch);
    else
        line->append(ch);
}

void FileObject::removeCharBeforePos(int x, int y)
{
    // auto line = linesBuffer.begin();
    // std::advance(line, y-1);
    // if (x - 2 >= 0) {
    //     line->erase(x-2, 1);
    //     return;
    // }
    // if (y <= 1) return;
    // (--line)->append(*(++line));
    // linesBuffer.erase(line);
    // linesBufferSize--;
}

void FileObject::removeCharAfterPos(int x, int y)
{
    // if (x <= linesBuffer[y-1].size())
    //     linesBuffer[y-1].erase(x-1, 1);
}