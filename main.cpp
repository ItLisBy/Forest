#include "SFML/Graphics.hpp"
#include "Button.h"

using namespace sf;

//Defines for window size
#define WIDTH 800
#define HEIGHT 600

int main() {
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Forest", Style::Titlebar | Style::Close);

    window.setFramerateLimit(60);

    //Load main text font
    Font main_font;
    main_font.loadFromFile("fonts/LiberationSans-Regular.ttf");

    //Setup start/stop button
    Button s_button("Start", Vector2f(160.0f, 40.0f), Vector2f(20.0f, 20.0f), 30, Color(225, 225, 225));
    s_button.setFont(main_font);

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

        window.draw(s_button.getShape());
        window.draw(s_button.getText());

        window.display();
    }

    return 0;
}
