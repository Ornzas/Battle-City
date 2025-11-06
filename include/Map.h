#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Constants.h"

class Map {
public:
    Map();
    void setAtlas(sf::Texture& texture);
    bool loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    bool isBlocked(const sf::FloatRect& bounds) const;

private:
    sf::Texture texture;
    sf::Sprite tileSprite;
    std::vector<std::vector<int>> grid;
};
