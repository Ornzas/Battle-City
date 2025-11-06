#pragma once
#include "TankBase.h"

class EnemyTank : public TankBase {
public:
    EnemyTank(float speed = 80.f);
    void update(float dt) override;
};
