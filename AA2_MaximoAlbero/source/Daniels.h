#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "UpLinearMovement.h"
#include "IdleMovement.h"

class Daniels : public Enemy {
public:
    Daniels(Vector2 spawnPos)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/daniels.png",
            Vector2(0.f, 0.f), Vector2(509, 490.f));

        _transform->scale = Vector2(0.5f, 0.5f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(20);
        SetPointsValue(100);

        float speed = 200.f;
        float xThreshold = RM->WINDOW_WIDTH / 2.f;
        float yThreshold = RM->WINDOW_HEIGHT / 2.f;
        float duration = 0.5f;

        movements.push_back(new RightLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new IdleMovement(_transform, _physics, duration));
        movements.push_back(new UpLinearMovement(_transform, _physics, yThreshold, speed));
        movements.push_back(new IdleMovement(_transform, _physics, duration));
        movements.push_back(new LeftLinearMovement(_transform, _physics, speed));
    }

    void Update() override {
        Enemy::Update();
    }
};