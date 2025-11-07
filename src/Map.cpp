#include "Map.h"
#include "Constants.h"
#include <fstream>
#include <iostream>

Map::Map() {}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Map::loadFromFile fail: " << filename << '\n';
        return false;
    }
    grid.clear();
    std::string line;
    while (std::getline(f, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c >= '0' && c <= '9') row.push_back(c - '0');
        }
        if (!row.empty()) grid.push_back(row);
    }
    f.close();
    return true;
}

void Map::setAtlasTexture(sf::RenderWindow& window, const sf::Texture& t) {
    // tile.setTextureRect(sf::IntRect(737, 0, tileSize, tileSize));;
    for (size_t y = 0; y < MAP_WIDTH; ++y) {
        for (size_t x = 0; x < MAP_HEIGHT; ++x) {
            tile.setPosition(x * tileSize, y * tileSize);
            window.draw(tile);
        }
    }
}

void Map::draw(sf::RenderWindow& window, const sf::Vector2f& offset) {
    if (!tileset) return;
    const int TILESET_TOP = 608; // пример — поправь в зависимости от твоего атласа
    enum TileType { EMPTY, BRICK, GRASS, WATER, STEEL };
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == BRICK)
                tile.setTextureRect(sf::IntRect(512, 0, TILE_SIZE, TILE_SIZE));      // кирпич
            else if (grid[y][x] == GRASS)
                tile.setTextureRect(sf::IntRect(544, 64, TILE_SIZE, TILE_SIZE));     // трава
            else if (grid[y][x] == WATER)
                tile.setTextureRect(sf::IntRect(512, 64, TILE_SIZE, TILE_SIZE));     // вода
            else if (grid[y][x] == STEEL)
                tile.setTextureRect(sf::IntRect(512, 32, TILE_SIZE, TILE_SIZE));     // сталь
            else continue; // пусто — не рисуем
            // tile.setTextureRect(sf::IntRect(id * tileSize, TILESET_TOP, tileSize, tileSize));
            tile.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            window.draw(tile);
    //             enum TileType { EMPTY, BRICK, GRASS, WATER, STEEL };
    // for (int y = 0; y < grid.size(); y++) {
    //     for (int x = 0; x < grid[y].size(); x++) {
    //         if (grid[y][x] == BRICK)
    //             tileSprite.setTextureRect(sf::IntRect(512, 0, TILE_SIZE, TILE_SIZE));      // кирпич
    //         else if (grid[y][x] == GRASS)
    //             tileSprite.setTextureRect(sf::IntRect(544, 64, TILE_SIZE, TILE_SIZE));     // трава
    //         else if (grid[y][x] == WATER)
    //             tileSprite.setTextureRect(sf::IntRect(512, 64, TILE_SIZE, TILE_SIZE));     // вода
    //         else if (grid[y][x] == STEEL)
    //             tileSprite.setTextureRect(sf::IntRect(512, 32, TILE_SIZE, TILE_SIZE));     // сталь
    //         else continue; // пусто — не рисуем

    //         tileSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
    //         window.draw(tileSprite);
        }
    }
}

bool Map::isBlocked(const sf::FloatRect& bounds) const {
    int x1 = bounds.left / tileSize;
    int y1 = bounds.top / tileSize;
    int x2 = (bounds.left + bounds.width) / tileSize;
    int y2 = (bounds.top + bounds.height) / tileSize;

    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            if (y < 0 || y >= (int)grid.size() || x < 0 || x >= (int)grid[y].size()) return true;
            int t = grid[y][x];
            if (t == 1 || t == 2) return true; // 1,2 - блокирующие
        }
    }
    return false;
}
