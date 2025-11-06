#pragma once
#include "DrawableEntity.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

class Map; // forward, TankBase не зависит от Map напрямую

class TankBase : public DrawableEntity {
public:
    TankBase(float speed = 100.f) : speed(speed), hp(3) {}
    virtual ~TankBase() = default;
    virtual void update(float dt) = 0;
    void moveDir(const sf::Vector2f& dir, float dt, const Map& map);
    void setTextureRect(const sf::IntRect& rect) { sprite.setTextureRect(rect); }
    void setAtlasTexture(const sf::Texture& tex) { sprite.setTexture(tex); }
protected:
    float speed;
    int hp;
};
