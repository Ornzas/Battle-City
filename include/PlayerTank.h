#pragma once
#include "TankBase.h"
class Map;

class PlayerTank : public TankBase {
public:
    PlayerTank(float speed = 120.f);
    void update(float dt, const Map& map) override;
    void handleInput(float dt, const Map& map);
};
