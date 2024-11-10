#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "settings.h"
#include "fileObject.h"
#include "editorViewer.h"

constexpr char SettingsFileName[] = "RimSettings.txt";

int main(int argc, char** argv)
{   
    std::string BinPath = argv[0];
    BinPath.erase(BinPath.find_last_of('/'), BinPath.size()-1);

    FileObject openedFile;
    if (argc >= 2) {
        openedFile.init(argv[1]);
    }
    std::string fontName = GetFontNameFromSetingsFile(BinPath + "/" + SettingsFileName);
    sf::Color bgColor(GetBgColorFromSettingsFile(BinPath + "/"+ SettingsFileName));
    sf::Color fontColor(GetFColorFromSettingsFile(BinPath + "/"+ SettingsFileName));

    sf::Font ProgramFont;
    ProgramFont.loadFromFile(BinPath + "/fonts/" + fontName + ".ttf");

    sf::RenderWindow window(sf::VideoMode(800, 1000), "Rim", 
        sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);

    EditorViewer editorViewer;
    editorViewer.setFont(ProgramFont);
    editorViewer.setBgColor(bgColor);
    editorViewer.setFontColor(fontColor);
    editorViewer.setFontSize(20);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {            
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close(); break;
            }
            editorViewer.draw(window, openedFile);
        }
        window.display();
    }
    return 0;
}