#include "Map.h"
#include <fstream>
#include <iostream>

Map::Map() {
    // if (!texture.loadFromFile("assets/images/sprites.png")) {
    //     std::cerr << "Ошибка: не удалось загрузить спрайт sprites.png\n";
    // }
    // tile.setTexture(texture);

    // Простая карта: 0 — пусто, 1 — кирпич
    // grid = {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    // };
}

void Map::setAtlas(sf::Texture& texture) {
    tileSprite.setTexture(texture);
}

bool Map::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть " << filename << "\n";
        return false;
    }
    grid.resize(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 0));
    //grid.clear();
    // std::string line;
    // while (std::getline(file, line)) {
    //     std::vector<int> row;
    //     for (char c : line) {
    //         if (c >= '0' && c <= '9')
    //             row.push_back(c - '0');
    //     }
    //     grid.push_back(row);
    // }
        for (int y = 0; y < MAP_HEIGHT; ++y) {
        std::string line;
        if (!std::getline(file, line)) break;

        for (int x = 0; x < MAP_WIDTH && x < line.size(); ++x) {
            if (isdigit(line[x])) grid[y][x] = line[x] - '0';
        }
    }

    file.close();
    return true;
}

void Map::draw(sf::RenderWindow& window) {
    // допустим, тайлы идут в первом ряду: кирпич, трава, вода, сталь
    enum TileType { EMPTY, BRICK, GRASS, WATER, STEEL };
    for (int y = 0; y < grid.size(); y++) {
        for (int x = 0; x < grid[y].size(); x++) {
            if (grid[y][x] == BRICK)
                tile.setTextureRect(sf::IntRect(512, 0, TILE_SIZE, TILE_SIZE));      // кирпич
            else if (grid[y][x] == GRASS)
                tile.setTextureRect(sf::IntRect(544, 64, TILE_SIZE, TILE_SIZE));     // трава
            else if (grid[y][x] == WATER)
                tile.setTextureRect(sf::IntRect(512, 64, TILE_SIZE, TILE_SIZE));     // вода
            else if (grid[y][x] == STEEL)
                tile.setTextureRect(sf::IntRect(512, 32, TILE_SIZE, TILE_SIZE));     // сталь
            else continue; // пусто — не рисуем

            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(tile);
        }
    }
}

bool Map::isBlocked(const sf::FloatRect& bounds) const {
    int x1 = bounds.left / TILE_SIZE;
    int y1 = bounds.top / TILE_SIZE;
    int x2 = (bounds.left + bounds.width) / TILE_SIZE;
    int y2 = (bounds.top + bounds.height) / TILE_SIZE;

    for (int y = y1; y <= y2; y++) {
        for (int x = x1; x <= x2; x++) {
            if (y < 0 || y >= grid.size() || x < 0 || x >= grid[y].size())
                return true; // выход за карту = блок
            if (grid[y][x] == 1)
                return true; // кирпич = нельзя пройти
        }
    }
    return false;
}
