#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Resources {
    static sf::Texture sprites;

    static bool load(const std::string& path = "assets/images/sprites.png") {
        if (!sprites.loadFromFile(path)) {
            std::cerr << "Resources::load: failed to load " << path << std::endl;
            return false;
        }
        return true;
    }
};