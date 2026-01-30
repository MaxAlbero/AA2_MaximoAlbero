#pragma once
#include "EnemyMovement.h"
#include <cmath>

class TargetMovement : public EnemyMovement {
private:
    Vector2 _targetPosition;
    float _speed;

public:
    TargetMovement(Transform* transform, RigidBody* rigidBody, Vector2 targetPos, float speed)
        : EnemyMovement(transform, rigidBody), _targetPosition(targetPos), _speed(speed) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        Vector2 direction = _targetPosition - _transform->position;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (distance < 5.f) {
            _transform->position = _targetPosition;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }
        else {
            direction.Normalize();
            _rigidBody->SetVelocity(direction * _speed);
        }
    }
};