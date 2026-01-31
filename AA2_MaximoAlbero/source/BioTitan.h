#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "IdleMovement.h"
#include "ShootMovement.h"

class BioTitan : public Enemy {
public:
    BioTitan() : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/father.png",
            Vector2(0.f, 0.f), Vector2(415.f, 403.f));

        _transform->size = Vector2(300.f, 300.f);
        _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT / 2.f);
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(300);
        SetPointsValue(1000);
        SetIsBoss(true);

        float speed = 100.f;
        Vector2 stopPos(RM->WINDOW_WIDTH - _transform->size.x, RM->WINDOW_HEIGHT / 2.f);

        movements.push_back(new TargetMovement(_transform, _physics, stopPos, speed));
        movements.push_back(new IdleMovement(_transform, _physics, 2.0f));
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));
        movements.push_back(new IdleMovement(_transform, _physics, 1.0f));
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));
        movements.push_back(new IdleMovement(_transform, _physics, 1.0f));
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));
    }
};