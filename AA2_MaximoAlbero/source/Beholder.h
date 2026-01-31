#pragma once
#include "Enemy.h"
#include "IdleMovement.h"
#include "ChaseMovement.h"
#include "EscapeMovement.h"

class Beholder : public Enemy {
public:
    Beholder(Vector2 spawnPos, Transform* playerTransform) : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/beholder.png",
            Vector2(0.f, 0.f), Vector2(306.f, 562.f));

        _transform->size = Vector2(100.f, 100.f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(30);
        SetPointsValue(300);

        float speed = 200.f;
        float xThreshold = RM->WINDOW_WIDTH * 2.f / 3.f;

        movements.push_back(new IdleMovement(_transform, _physics, 1.f));
        movements.push_back(new ChaseMovement(_transform, _physics, playerTransform, speed, 3, 1.5f, 10.f));
        movements.push_back(new EscapeMovement(_transform, _physics, speed));
    }

    void Update() override {
        Enemy::Update();

        if (_transform->position.x + _transform->size.x < 0.f ||
            _transform->position.x > RM->WINDOW_WIDTH ||
            _transform->position.y + _transform->size.y < 0.f ||
            _transform->position.y > RM->WINDOW_HEIGHT) {
            Destroy();
        }
    }
};