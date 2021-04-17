#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

//Defines for window size
#define WIDTH 800
#define HEIGHT 600

int main() {
    bool stopped = true;

    Map main_map(Map::TerritoryType::middle_forest);

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Forest", Style::Titlebar | Style::Close);

    window.setFramerateLimit(200);
    ImGui::SFML::Init(window);

    //Loop program while it's window is open
    Clock delta_clock;

    while(window.isOpen()){
        Event event;
        int process;
        //Handling events
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();

        }

        ImGui::SFML::Update(window, delta_clock.restart());

        if (stopped){
            ImGui::Begin("Tools");
            if(ImGui::Button("Start", ImVec2(160, 40))) {
                stopped = false;
            }
            ImGui::End();

        }



        window.clear(Color(255, 255, 255));
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
