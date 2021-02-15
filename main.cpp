#include "SFML/Graphics.hpp"

using namespace sf;

//Defines for window size
#define WIDTH 1920
#define HIGH 1080

int main() {
    RenderWindow window(VideoMode(800, 600), "Forest", Style::Titlebar | Style::Close);

    window.setFramerateLimit(60);

    //Loop program while it's window is open
    while(window.isOpen()){
        //Handling events
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(Color(255, 255, 255));

        window.display();
    }

    return 0;
}
