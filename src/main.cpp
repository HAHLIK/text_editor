#include <algorithm>
#include "settings.h"
#include "fileObject.h"
#include "editorViewer.h"


int main(int argc, char** argv)
{   
    std::string BinPath = argv[0];
    BinPath.erase(BinPath.find_last_of('/'), BinPath.size()-1);

    FileObject openedFile;
    if (argc >= 2) {
        openedFile.init(argv[1]);
    }

    sf::Font ProgramFont;
    ProgramFont.loadFromFile(BinPath + "/font/" + FontName + ".ttf");

    sf::RenderWindow window(sf::VideoMode(800, 1000), "Rim");
    window.setVerticalSyncEnabled(true);

    EditorViewer editorViewer;
    editorViewer.setFont(ProgramFont);
    editorViewer.setBgColor(BgColor);
    editorViewer.setFontColor(FontColor);
    editorViewer.setFontSize(20);
    editorViewer.init(window, openedFile);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {            
            switch (event.type) 
            {
            case sf::Event::Closed:
                window.close(); break;
            case sf::Event::Resized:
                editorViewer.setCameraBounds(event.size.width, event.size.height);
                break;
            }
            if (event.type != sf::Event::KeyPressed) continue;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                editorViewer.moveDown();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                editorViewer.moveUp();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                editorViewer.moveRight();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                editorViewer.moveLeft();
        }
        editorViewer.draw();
        window.display();
    }
    return 0;
}