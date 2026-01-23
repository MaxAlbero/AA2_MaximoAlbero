#pragma once
#include "EnemyMovement.h"
#include <cmath>

class CirclerMovement : public EnemyMovement {
private:
    float _radius;
    Vector2 _center;
    float _angularVelocity; // grados por segundo
    float _currentAngle;
    float _initialAngle;

public:
    CirclerMovement(Transform* transform, RigidBody* rigidBody,
        float radius, Vector2 center, float angularVelocity)
        : EnemyMovement(transform, rigidBody),
        _radius(radius), _center(center), _angularVelocity(angularVelocity),
        _currentAngle(0.f) {

        // Calcular ángulo inicial basado en la posición actual
        Vector2 offset = _transform->position - _center;
        _initialAngle = atan2(offset.y, offset.x) * 180.f / 3.14159265f;
        _currentAngle = _initialAngle;
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        const float PI = 3.14159265f;
        _currentAngle += _angularVelocity * deltaTime;

        float rad = _currentAngle * PI / 180.f;
        _transform->position.x = _center.x + _radius * std::cos(rad);
        _transform->position.y = _center.y + _radius * std::sin(rad);

        // Una vuelta completa
        if (_currentAngle >= _initialAngle + 360.f) {
            _finished = true;
        }
    }
};