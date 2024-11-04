#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "settings.h"
#include "fileObject.h"

int main(int argc, char** argv)
{   
    std::string BinPath = argv[0];
    BinPath.erase(BinPath.find_last_of('/'), BinPath.size()-1);

    std::string fontName = GetFontNameFromSetingsFile(BinPath);

    sf::Font ProgramFont;
    ProgramFont.loadFromFile(BinPath + "/fonts/" + fontName + ".ttf");

    sf::RenderWindow window(sf::VideoMode(800, 850), "Rim", 
        sf::Style::Close | sf::Style::Resize);
    window.setVerticalSyncEnabled(true);

    sf::Text text;
    text.setFont(ProgramFont);
    text.setString("Hello world");
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
            window.clear();
            window.draw(text);
            window.display();
        }
    }
    return 0;
}