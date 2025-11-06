#pragma once
#include "TankBase.h"
#include "Map.h"

class PlayerTank : public TankBase {
public:
    PlayerTank(float speed = 120.f);
    void update(float dt) override;
    void handleInput(float dt, const Map& map);
};
