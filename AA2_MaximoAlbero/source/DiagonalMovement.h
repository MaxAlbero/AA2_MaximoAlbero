#pragma once
#include "EnemyMovement.h"
#include <cmath>

class DiagonalMovement : public EnemyMovement {
private:
    float _targetY;
    float _speed;
    float _directionX; // 1.0 para derecha, -1.0 para izquierda

public:
    DiagonalMovement(Transform* transform, RigidBody* rigidBody,
        float targetY, float speed, float directionX = 1.0f)
        : EnemyMovement(transform, rigidBody),
        _targetY(targetY),
        _speed(speed),
        _directionX(directionX) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        // Calcular dirección Y
        float directionY = (_targetY > _transform->position.y) ? 1.0f : -1.0f;

        // Normalizar para mantener velocidad constante
        float magnitude = std::sqrt(_directionX * _directionX + directionY * directionY);
        float normalizedX = _directionX / magnitude;
        float normalizedY = directionY / magnitude;

        // Aplicar velocidad
        _rigidBody->SetVelocity(Vector2(normalizedX * _speed, normalizedY * _speed));

        // Verificar si alcanzó la altura objetivo
        float tolerance = _speed * deltaTime * 2.0f;
        if (std::abs(_transform->position.y - _targetY) <= tolerance) {
            _transform->position.y = _targetY;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }
    }
};