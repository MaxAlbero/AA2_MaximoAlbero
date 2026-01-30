#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "CirclerMovement.h"

class CirclerBody : public Enemy {
public:
    CirclerBody(float distance = 120.f)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/pinky.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->size = Vector2(80.f, 80.f);

        _transform->position = Vector2(RM->WINDOW_WIDTH / 2.f, -_transform->size.y);

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        SetHealth(999999);
        SetPointsValue(0);

        float speed = 200.f;
        float baseRadius = 300.f;
        Vector2 screenCenter(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
        float angularVelocity = 90.f;

        Vector2 offset = Vector2(-distance, -distance * 0.4f);

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 4.f) + offset, speed));

        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - distance),
            screenCenter + offset,
            angularVelocity));

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 50.f, screenCenter.y + 10.f) + offset, speed));

        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - 100.f - distance),
            Vector2(screenCenter.x + 150.f, screenCenter.y + 100.f) + offset,
            angularVelocity));

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 200.f, screenCenter.y + 150.f) + offset, speed));

        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - 250.f - distance),
            Vector2(screenCenter.x + 250.f, screenCenter.y + 200.f) + offset,
            angularVelocity));

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, -200.f) + offset, speed));
    }

    void Update() override {
        Enemy::Update();

        if (_transform->position.y + _transform->size.y < 0.f) {
            std::cout << "CIRCLER Body DESTROYED" << std::endl;
            Destroy();
        }
    }
};