#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "IdleMovement.h"
#include "ShootMovement.h"

class SpaceBoss : public Enemy {
public:
    SpaceBoss() : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/Richard.png",
            Vector2(0.f, 0.f), Vector2(231.f, 149.f));

        _transform->scale = Vector2(2.f, 2.f);
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