#pragma once
#include "EnemyMovement.h"

class RightLinearMovement : public EnemyMovement {
private:
    float _speed;
    float _xThreshold;
    bool _hasThreshold;

public:
    // Constructor con umbral
    RightLinearMovement(Transform* transform, RigidBody* rigidBody, float xThreshold, float speed)
        : EnemyMovement(transform, rigidBody),
        _xThreshold(xThreshold), _speed(speed), _hasThreshold(true) {
    }

    // Constructor sin umbral
    RightLinearMovement(Transform* transform, RigidBody* rigidBody, float speed)
        : EnemyMovement(transform, rigidBody),
        _xThreshold(1000.f), _speed(speed), _hasThreshold(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        _rigidBody->SetVelocity(Vector2(_speed, 0.f));

        if (_hasThreshold && _transform->position.x >= _xThreshold) {
            _transform->position.x = _xThreshold;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }

    }
};