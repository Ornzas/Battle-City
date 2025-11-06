#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Tank.h"
#include "UI.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();

    sf::RenderWindow window;
    Tank player;
    UI ui;
    Map map; // ← добавили карту
};