#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Resources {
    static sf::Texture sprites;

    static bool load() {
        if (!sprites.loadFromFile("assets/textures/sprites.png")) {
            std::cerr << "Ошибка: не удалось загрузить game_atlas.png\n";
            return false;
        }
        return true;
    }
};