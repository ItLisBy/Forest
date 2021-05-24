#include "SFML/Graphics.hpp"
#include "Map.h"
#include "Animals.h"
#include "TileMap.h"
#include "imgui.h"
#include "imgui-SFML.h"

using namespace sf;

//Defines for window size
#define WIDTH 768
#define HEIGHT 768

enum Proc{
    start,
    m_proc,
    ref
};

int main() {
    bool stopped = true;
    bool tropical = false;
    float anim [NUM_ANIMALS] = {0};
    float i_anim[NUM_ANIMALS] = {0};
    Proc prev_process = start;
    Proc process = start;

    Map::init();

    TileMap map, anim_map, ent_map;
    map.setScale(0.75, 0.75);
    anim_map.setScale(0.75, 0.75);
    ent_map.setScale(0.75, 0.75);
    if (!map.load("textures/usual.png", sf::Vector2u(16, 16), Map::terrain_map, 64, 64))
        return -1;
    if (!anim_map.load("textures/animals.png", sf::Vector2u(16, 16), Map::animals_map, 64, 64))
        return -1;
    if (!ent_map.load("textures/ent.png", sf::Vector2u(16, 16), Map::entities_map, 64, 64))
        return -1;

    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Forest", Style::Titlebar | Style::Close);

    window.setFramerateLimit(200);
    ImGui::SFML::Init(window);

    //Loop program while it's window is open
    Clock delta_clock;

    while(window.isOpen()){
        Event event;

        //Handling events
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            // "close requested" event: we close the window
            switch (event.type) {
                case Event::Closed:
                    window.close();
                    break;

                case Event::KeyPressed:
                    if (Keyboard::isKeyPressed(Keyboard::F1)) {
                        prev_process = process;
                        process = ref;
                    }
                    break;

                default:

                    break;
            }

        }

        ImGui::SFML::Update(window, delta_clock.restart());

        ImGui::Begin("Tools");
        if (ImGui::Button(stopped ? "Start" : "Stop", ImVec2(160, 40))) {
            stopped = !stopped;
            if (process != m_proc)
                process = m_proc;
        }
        if (stopped) {
            if (process == start)
                if (ImGui::RadioButton("Use alt. tileset", tropical)) {
                    tropical = !tropical;
                    if (!map.load(tropical ? "textures/tropical.png" : "textures/usual.png", sf::Vector2u(16, 16), Map::terrain_map, 64, 64))
                        return -1;
                }
            if (ImGui::SliderFloat("Sheep", &i_anim[AnimalType::Sheep], 0.f, 20.f, "%.0f")) {
                anim[AnimalType::Sheep] = i_anim[AnimalType::Sheep];
            }
            if (ImGui::SliderFloat("Hares", &i_anim[AnimalType::Hare], 0.f, 20.f, "%.0f")) {
                anim[AnimalType::Hare] = i_anim[AnimalType::Hare];
            }
            if (ImGui::SliderFloat("Wolfs", &i_anim[AnimalType::Wolf], 0.f, 20.f, "%.0f")) {
                anim[AnimalType::Wolf] = i_anim[AnimalType::Wolf];
            }
        }
        else {
            ImGui::Text("Sheep: %.0f", anim[AnimalType::Sheep]);
            ImGui::Text("Hares: %.0f", anim[AnimalType::Hare]);
            ImGui::Text("Wolfs: %.0f", anim[AnimalType::Wolf]);
        }

        ImGui::End();

        switch (process) {
            case start:

                break;

            case m_proc:

                break;

            case ref:
                ImGui::Begin("Reference");
                ImGui::Text("Simulation paused!");
                ImGui::Text("Buttons:");
                ImGui::Text("\"Start\" - start simulation. Available only when stopped");
                ImGui::Text("\"Stop\" - start simulation. Available only when running");
                ImGui::Text("RadioButtons:");
                ImGui::Text("\"Use alt. tileset\" - change tileset to tropical. Available only before first start");
                ImGui::Text("");
                ImGui::Text("2021, Minsk");
                if (ImGui::Button("Close", ImVec2(160, 40))) {
                    process = prev_process;
                    prev_process = ref;
                }
                ImGui::End();
                break;
        }

        window.clear(Color(255, 255, 255));
        window.draw(map);
        window.draw(anim_map);
        window.draw(ent_map);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();
    return 0;
}
