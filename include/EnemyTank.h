#pragma once
#include "TankBase.h"
class Map;

class EnemyTank : public TankBase {
public:
    EnemyTank(float speed = 80.f);
    void update(float dt, const Map& map, const sf::Vector2f& mapOffset) override;
    //void update(float dt, const Map& map);
};
