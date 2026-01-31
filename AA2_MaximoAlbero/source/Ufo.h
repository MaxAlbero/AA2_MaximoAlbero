#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "IdleMovement.h"

class Ufo : public Enemy {
public:
    Ufo(Vector2 spawnPos, float speed)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/ufo.png",
            Vector2(0.f, 0.f), Vector2(499.f, 499.f));

        _transform->scale = Vector2(0.5f, 0.5f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(20);
        SetPointsValue(100);

        float xThreshold = RM->WINDOW_WIDTH / 2.f;
        float duration = 2.f;

        movements.push_back(new RightLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new IdleMovement(_transform, _physics, duration));
        movements.push_back(new LeftLinearMovement(_transform, _physics, speed));
    }

    void Update() override {
        Enemy::Update();

        if (_transform->position.x + _transform->size.x < 0.f) {
            Destroy();
        }
    }
};