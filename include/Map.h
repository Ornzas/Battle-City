#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Constants.h"  // вот это нужно
// если используешь ресурсы:
#include "Resources.h"

class Map {
public:
    Map();
    bool loadFromFile(const std::string& filename);
    void setAtlasTexture(const sf::Texture& t) { tileset = &t; tile.setTexture(*tileset); }
    void draw(sf::RenderWindow& window, const sf::Vector2f& offset);
    bool isBlocked(const sf::FloatRect& bounds) const;

private:
    const sf::Texture* tileset = nullptr;
    sf::Sprite tile;
    std::vector<std::vector<int>> grid;
    int tileSize = TILE_SIZE;
};
