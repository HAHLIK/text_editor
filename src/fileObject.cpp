#include "fileObject.h"

FileObject::FileObject() {}
FileObject::~FileObject() {}

bool FileObject::init(const std::string& filePath) noexcept
{
    this->filePath = filePath;
    this->fileName = filePath;
    this->fileName.erase(0, this->fileName.find_last_of('/') + 1);

    std::ifstream inputFile(filePath);
    if (!inputFile.is_open())
        return false;
    std::string lineBuffer;
    while (std::getline(inputFile, lineBuffer)) {
        for (int i = 0; i < lineBuffer.size(); ++i) {
            if (lineBuffer[i] == '\t') {
                lineBuffer.replace(i, 1, "    ");
                i += 3;
            }
        }
        linesBuffer.push_back(lineBuffer);
    }
    linesBufferSize = linesBuffer.size();

    inputFile.close();
    return true;
}

bool FileObject::save() noexcept
{
    if (filePath == "") return false;
    std::ofstream outputFile(filePath);
    if (!outputFile.is_open())
        return false;
    for (auto line : linesBuffer)
        outputFile << line << '\n';

    outputFile.close();
    return true;
}


std::string FileObject::getLine(size_t n) const
{   
    if (1 > n || n > linesBufferSize) 
        return "";
    auto it = linesBuffer.begin();
    std::advance(it, n-1);
    std::string str = *it;
    return str;
}

size_t FileObject::getNumOfLines() const { return linesBufferSize; }

void FileObject::insertTextToPos(int x, int y, const std::string& text) 
{
    if (linesBufferSize == 0) {
        linesBuffer.push_back("");
        linesBufferSize++;
    }
    auto line = linesBuffer.begin();
    std::advance(line, y-1);
    if (x-1 < line->size())
        line->insert(x-1, text);
    else
        line->append(text);
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