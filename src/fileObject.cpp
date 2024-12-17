#include "fileObject.h"

FileObject::FileObject() {}
FileObject::~FileObject() {}

bool FileObject::init(const std::string& filePath) noexcept
{
    this->filePath = filePath;
    this->fileName = filePath;
    this->fileName.erase(0, this->fileName.find_last_of('/') + 1);

    std::ifstream inputFile(filePath);
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

bool FileObject::save() noexcept
{
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error: don't opening file" << std::endl;
        return false;
    }
    for (auto line : linesBuffer)
        outputFile << line << '\n';

    outputFile.close();
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

void FileObject::insertCharToPos(int x, int y, const std::string& ch) 
{
    if (linesBufferSize == 0) {
        linesBuffer.push_back("");
        linesBufferSize++;
    }
    auto line = linesBuffer.begin();
    std::advance(line, y-1);
    if (x-1 < line->size())
        line->insert(x-1, ch);
    else
        line->append(ch);
}

void FileObject::removeCharBeforePos(int x, int y)
{
    auto itLine = linesBuffer.begin();
    std::advance(itLine, y-1);
    if (x - 2 >= 0) {
        itLine->erase(x-2, 1);
        return;
    }
    if (y <= 1) return;
    (--itLine)->append(*(++itLine));
    linesBuffer.erase(itLine);
    linesBufferSize--;
}

void FileObject::removeCharAfterPos(int x, int y)
{
    auto itLine = linesBuffer.begin();
    std::advance(itLine, y-1);
    if (x <= itLine->size()) {
        itLine->erase(x-1, 1);
        return;
    }
    if (y >= linesBufferSize) return;
    itLine->append(*(++itLine));
    linesBuffer.erase(itLine);
    linesBufferSize--;
}

void FileObject::addLineToPos(int x, int y)
{
    auto itLine = linesBuffer.begin();
    std::advance(itLine, y-1);
    std::string newLineString = itLine->substr(x-1, itLine->size() - x + 1);
    itLine->erase(x-1, itLine->size() - x + 1);
    linesBuffer.insert(++itLine, newLineString);
    linesBufferSize++;
}