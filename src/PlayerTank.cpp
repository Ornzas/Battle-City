#include "PlayerTank.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include "Map.h"


PlayerTank::PlayerTank(float speed)
    : TankBase(speed)
{
    // начальные координаты
    sprite.setPosition(100, 100);
}

void PlayerTank::handleInput(float dt, const Map& map) {
    sf::Vector2f dir(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dir.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dir.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dir.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dir.x += 1.f;

    if (dir.x != 0.f || dir.y != 0.f) {
        // нормализация (чтобы диагональ не ускоряла)
        float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        dir /= len;
        moveDir(dir, dt, map);
    }
}

void PlayerTank::update(float dt) {
    // пусто — вызывай handleInput из Game::update с map
}
