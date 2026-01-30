#pragma once
#include "EnemyMovement.h"
#include <cmath>

class CirclePartialMovement : public EnemyMovement {
private:
    float _radius;
    Vector2 _center;
    float _angularVelocityDeg;
    float _degreesToRotate;
    float _accumulatedDeg;
    float _currentAngleDeg;
    bool _initialized;

public:
    CirclePartialMovement(Transform* transform, RigidBody* rigidBody,
        float radius, const Vector2& center,
        float angularVelocityDeg, float degreesToRotate)
        : EnemyMovement(transform, rigidBody),
        _radius(radius), _center(center),
        _angularVelocityDeg(angularVelocityDeg),
        _degreesToRotate(std::abs(degreesToRotate)),
        _accumulatedDeg(0.f),
        _currentAngleDeg(0.f),
        _initialized(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) return;
        if (!_transform) return;

        if (!_initialized) {
            Vector2 offset = _transform->position - _center;
            _currentAngleDeg = atan2f(offset.y, offset.x) * 180.0f / 3.14159265f;
            _accumulatedDeg = 0.f;
            _initialized = true;
        }

        float deltaDeg = _angularVelocityDeg * deltaTime;
        _currentAngleDeg += deltaDeg;
        _accumulatedDeg += std::abs(deltaDeg);

        const float PI = 3.14159265f;
        float rad = _currentAngleDeg * PI / 180.0f;
        _transform->position.x = _center.x + _radius * std::cos(rad);
        _transform->position.y = _center.y + _radius * std::sin(rad);

        if (_accumulatedDeg >= _degreesToRotate) {
            _finished = true;
        }
    }
};