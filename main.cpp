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

    //Load main texture
    Texture main_texture;
    main_texture.loadFromFile("textures/textures.png");

    //Setup start/stop button
    Button s_button("btn_s", main_texture,
                    IntRect(0, 40, 160, 40),
                    IntRect(0, 0, 160, 40),
                    Vector2f(20.0f, 20.0f));
    //Loop program while it's window is open
    while(window.isOpen()){
        //Handling events
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == Event::MouseButtonPressed || event.type == Event::MouseButtonReleased)
                if (s_button.isClicked(Mouse::getPosition(window))){
                    s_button.setText(IntRect(0, 80, 160, 40));
                }
        }

        window.clear(Color(255, 255, 255));

        window.draw(s_button);

        window.display();
    }

    return 0;
}
