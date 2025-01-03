#include <algorithm>
#include "settings.h"
#include "fileObject.h"
#include "editorViewer.h"
#include "inputController.h"


int main(int argc, char** argv)
{   
    std::string BinPath = argv[0];
    BinPath.erase(BinPath.find_last_of('/'), BinPath.size()-1);

    FileObject openedFile;
    if (argc >= 2) openedFile.init(argv[1]);

    sf::Font ProgramFont;
    ProgramFont.loadFromFile(BinPath + "/resours/font/" + FontName + ".ttf");

    sf::RenderWindow window(sf::VideoMode(800, 1000), "Rim");
    window.setVerticalSyncEnabled(true);

    EditorViewer editorViewer;
    editorViewer.setFont(ProgramFont);
    editorViewer.setBgColor(BgColor);
    editorViewer.setFontColor(FontColor);
    editorViewer.init(window, openedFile);

    EditorContent editorContent(editorViewer);
    InputController inputController(editorViewer, editorContent);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {            
            inputController.handleEvents(event);
        }
        editorViewer.draw();
        window.display();
    }
    return 0;
}