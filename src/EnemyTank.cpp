#include "EnemyTank.h"
#include <random>
#include <cmath>

EnemyTank::EnemyTank(float speed)
    : TankBase(speed)
{
    sprite.setPosition(200, 200);
}

    // создать глобальный или статический генератор
    std::random_device rd;
    std::mt19937 gen(rd()); // генератор Мерсенна
    std::uniform_int_distribution<int> directionRandom(0, 3); // диапазон от 0 до 10

void EnemyTank::update(float dt, const Map& map, const sf::Vector2f& mapOffset) {
    // примитивное поведение: двигаться вниз
    // sprite.move(0.f, speed * dt);
    sf::Vector2f dir(0.f, 0.f);
    int direction = directionRandom(gen); // получить случайное число
    switch (direction) {
        case 0: dir.y -= 1.f; break;
        case 1: dir.y += 1.f; break;
        case 2: dir.x -= 1.f; break;
        case 3: dir.x += 1.f; break;
    }
    if (dir.x != 0.f || dir.y != 0.f) {
        // нормализация (чтобы диагональ не ускоряла)
        float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        dir /= len;
        moveDir(dir, dt, map, mapOffset);
    }
}
