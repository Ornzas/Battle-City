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
    tile.setTexture(t);
    tile.setTextureRect(sf::IntRect(737, 0, tileSize, tileSize));;
    for (size_t x = 0; x < (MAP_WIDTH + UI_WIDTH); ++x) {
        for (size_t y = 0; y < MAP_HEIGHT; ++y) {
            tile.setPosition(x * tileSize, y * tileSize);
            window.draw(tile);
        }
    }
}

void Map::draw(sf::RenderWindow& window, const sf::Vector2f& offset, const sf::Texture& t) {
    tile.setTexture(t);
    //if (!tileset) return;
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
            else 
            tile.setTextureRect(sf::IntRect(620, 100, TILE_SIZE, TILE_SIZE)); // пусто — не рисуем
            // tile.setTextureRect(sf::IntRect(id * tileSize, TILESET_TOP, tileSize, tileSize));
            tile.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            window.draw(tile);
        }
    }
}

bool Map::isBlocked(const sf::FloatRect& bounds, const sf::Vector2f& offset) const {
    // Сдвигаем координаты, если карта не с нуля отрисована
    float left = bounds.left - offset.x;
    float top = bounds.top - offset.y;

    if (left < 0.f || top < 0.f)
        return true; // за границами сверху/слева

    int x1 = static_cast<int>(left / tileSize);
    int y1 = static_cast<int>(top / tileSize);
    int x2 = static_cast<int>((left + bounds.width) / tileSize);
    int y2 = static_cast<int>((top + bounds.height) / tileSize);

    for (int y = y1; y <= y2; ++y) {
        for (int x = x1; x <= x2; ++x) {
            // Проверка выхода за границы карты
            if (y < 0 || y >= static_cast<int>(grid.size()) ||
                x < 0 || x >= static_cast<int>(grid[y].size()))
                return true; // считаем, что за границей — стена

            int t = grid[y][x];
            // Препятствия: кирпичи, сталь и вода (если хочешь)
            if (t == 1 || t == 2 || t == 3)
                return true;
        }
    }

    return false;
}
