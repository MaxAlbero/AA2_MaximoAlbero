#pragma once
#include "PowerUp.h"

class SpeedPowerUp : public PowerUp
{
private:
    float speedBoost;

public:
    SpeedPowerUp(float boost = 0.5f)
        : PowerUp(), speedBoost(boost) {

        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->scale = Vector2(2.0f, 2.0f);
    }

    //void ApplyEffect(Player* player) override {
    //    player->IncreaseSpeed(speedBoost);
    //    std::cout << "Speed PowerUp collected! Speed increased by " << speedBoost << std::endl;
    //}
};