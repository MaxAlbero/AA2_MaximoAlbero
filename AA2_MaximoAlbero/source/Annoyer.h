#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "EscapeMovement.h"
#include "IdleMovement.h"
#include "ChaseMovement.h"

class Annoyer : public Enemy {
public:
    Annoyer(Vector2 spawnPos, Transform* playerTransform)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/annoyer.png",
            Vector2(0.f, 0.f), Vector2(500, 500.f));


        _transform->scale = Vector2(0.25f, 0.25f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(20);
        SetPointsValue(100);

        float speed = 200.f;
        float xThreshold = RM->WINDOW_WIDTH / 1.5f;
        float duration = 2.f;

        movements.push_back(new LeftLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new IdleMovement(_transform, _physics, duration));
        movements.push_back(new ChaseMovement(_transform, _physics, playerTransform, speed, 1, duration, 10.f));
        movements.push_back(new EscapeMovement(_transform, _physics, speed));
    }

    void Update() override {
        Enemy::Update();

        if (_transform->position.x + _transform->size.x < 0.f) {
            Destroy();
        }
    }
};