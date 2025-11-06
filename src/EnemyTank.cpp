#include "EnemyTank.h"

EnemyTank::EnemyTank(float speed)
    : TankBase(speed)
{
    sprite.setPosition(200, 200);
}

void EnemyTank::update(float dt) {
    // примитивное поведение: двигаться вниз
    sprite.move(0.f, speed * dt);
}
