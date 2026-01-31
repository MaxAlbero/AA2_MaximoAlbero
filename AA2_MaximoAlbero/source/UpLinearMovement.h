#pragma once
#include "EnemyMovement.h"

class UpLinearMovement : public EnemyMovement {
private:
    float _speed;
    float _yThreshold;
    bool _hasThreshold;

public:
    // Constructor con umbral
    UpLinearMovement(Transform* transform, RigidBody* rigidBody, float yThreshold, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(yThreshold), _speed(speed), _hasThreshold(true) {
    }

    // Constructor sin umbral (para Hmedusa - sale de pantalla)
    UpLinearMovement(Transform* transform, RigidBody* rigidBody, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(-1000.f), _speed(speed), _hasThreshold(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        _rigidBody->SetVelocity(Vector2(0.f, -_speed));

        if (_hasThreshold && _transform->position.y <= _yThreshold) {
            _transform->position.y = _yThreshold;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }
    }
};