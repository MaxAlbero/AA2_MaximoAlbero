#pragma once
#include "EnemyMovement.h"

class DownLinearMovement : public EnemyMovement {
private:
    float _speed;
    float _yThreshold;
    bool _hasThreshold;

public:
    // Constructor con umbral
    DownLinearMovement(Transform* transform, RigidBody* rigidBody, float yThreshold, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(yThreshold), _speed(speed), _hasThreshold(true) {
    }

    // Constructor sin umbral
    DownLinearMovement(Transform* transform, RigidBody* rigidBody, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(1000.f), _speed(speed), _hasThreshold(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        _rigidBody->SetVelocity(Vector2(0.f, _speed));

        if (_hasThreshold && _transform->position.y >= _yThreshold) {
            _transform->position.y = _yThreshold;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }

    }
};