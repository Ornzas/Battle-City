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

void Map::draw(sf::RenderWindow& window, const sf::Vector2f& offset) {
    if (!tileset) return;
    const int TILESET_TOP = 608; // пример — поправь в зависимости от твоего атласа
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            int id = grid[y][x];
            if (id == 0) continue;
            tile.setTextureRect(sf::IntRect(id * tileSize, TILESET_TOP, tileSize, tileSize));
            tile.setPosition(offset.x + x * tileSize, offset.y + y * tileSize);
            window.draw(tile);
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
