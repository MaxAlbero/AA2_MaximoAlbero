#pragma once
#include "PowerUp.h"

class EnergyRecharge : public PowerUp {
public:
    EnergyRecharge()
        : PowerUp()
    {
        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->scale = Vector2(2.0f, 2.0f);
    }

    //void ApplyEffect(Player* player) override {
    //    player->RestoreFullEnergy();
    //    std::cout << "Heal PowerUp collected! Energy fully restored!" << std::endl;
    //}
};