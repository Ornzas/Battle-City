#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Constants.h"
#include "Map.h"
#include "PlayerTank.h"
#include "EnemyTank.h"

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    sf::Sprite backgroundSprite;

    Map map;
    std::unique_ptr<PlayerTank> player;
    std::vector<std::unique_ptr<EnemyTank>> enemies;

    sf::Vector2f mapOffset = {32.f, 32.f}; // смещение поля сверху/слева
};
