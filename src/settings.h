#pragma once

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "fileObject.h"

constexpr char DefaultfontName[] = "MesloLGLDZNerdFont-Bold";
const sf::Color DefaultBgColor(0x00000000);
const sf::Color DefaultFontColor(0xFFFFFF00);

std::string GetFontNameFromSetingsFile(const std::string& filePath) {
    std::string fontName;
    FileObject settingFile;
    if (!settingFile.init(filePath))
        fontName = DefaultfontName;
    else {
        fontName = settingFile.getLine(1);
        fontName.erase(0, 7);
    }
    return fontName;
}

sf::Color GetBgColorFromSettingsFile(const std::string& filePath) {
    sf::Color bgColor;
    FileObject settingFile;
    if (!settingFile.init(filePath))
        bgColor = DefaultBgColor;
    else {
        std::string bufferString = settingFile.getLine(2);
        bufferString.erase(0, 13);
        bgColor = sf::Color(std::stoi(bufferString, 0, 16) * 0x100 + 0xFF);
    }
    return bgColor;
}

sf::Color GetFColorFromSettingsFile(const std::string& filePath) {
    sf::Color fontColor;
    FileObject settingFile;
    if (!settingFile.init(filePath))
        fontColor = DefaultFontColor;
    else {
        std::string bufferString = settingFile.getLine(3);
        bufferString.erase(0, 13);
        fontColor = sf::Color(std::stoi(bufferString, 0, 16) * 0x100 + 0xFF);
    }
    return fontColor;
}