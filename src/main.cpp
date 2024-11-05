#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "settings.h"
#include "fileObject.h"

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

    sf::RenderWindow window(sf::VideoMode(800, 850), "Rim", 
        sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
    window.setVerticalSyncEnabled(true);

    sf::Text text;
    text.setFont(ProgramFont);
    text.setFillColor(fontColor);
    text.setCharacterSize(20);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {            
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close(); break;
            }
            std::string buffer;
            for (int i = 1; i <= std::min(28, (int)openedFile.getNumOfLines()); i++) {
                buffer += openedFile.getLine(i);
            }
            text.setString(buffer);
            window.clear(bgColor);
            window.draw(text);
        }
        window.display();
    }
    return 0;
}