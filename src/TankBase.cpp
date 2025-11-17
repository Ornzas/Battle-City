#include "TankBase.h"
#include "Map.h"

void TankBase::moveDir(const sf::Vector2f& dir, float dt, const Map& map, const sf::Vector2f& offset) {
    sf::Vector2f delta = dir * speed * dt;
    sf::FloatRect next = sprite.getGlobalBounds();
    next.left += delta.x;
    next.top  += delta.y;

    if (!map.isBlocked(next, offset)) {
        sprite.move(delta);
    }
}