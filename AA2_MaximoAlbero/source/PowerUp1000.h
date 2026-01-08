#pragma once
#include "PowerUp.h"

class PowerUp1000 : public PowerUp {
public:
    PowerUp1000()
        : PowerUp()
    {
        _renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->scale = Vector2(2.0f, 2.0f);
    }

    // Sobrescribimos la colisión para cambiar el mensaje
    void OnCollision(Object* other) override;

    void ApplyEffect(Player* player) override;
};