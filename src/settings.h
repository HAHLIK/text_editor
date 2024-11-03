#pragma once

#include <fstream>
#include <iostream>

constexpr char DefaultfontName[] = "MesloLGLDZNerdFont-Bold";

std::string GetFontNameFromSetingsFile(std::string& filePath) {
    std::string fontName;
    std::fstream settingFile(filePath + "/RimSettings.txt");
    if (!settingFile.is_open()) {
        std::cerr << "Don't open RimSettings.txt"; 
        fontName = DefaultfontName;
    }
    else {
        std::getline(settingFile, fontName);
        fontName.erase(0, 7);
    }
    settingFile.close();
    return fontName;
}