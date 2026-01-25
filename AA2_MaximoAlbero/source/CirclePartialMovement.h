#pragma once
#include "EnemyMovement.h"
#include <cmath>

// Movimiento que realiza un arco de círculo (en grados) alrededor de un centro.
// - angularVelocity: grados por segundo (puede ser negativo para sentido contrario).
// - degreesToRotate: cantidad total de grados a rotar (positivo).
// La inicialización del ángulo se hace en el primer Update para leer la posición actual.
class CirclePartialMovement : public EnemyMovement {
private:
    float _radius;
    Vector2 _center;
    float _angularVelocityDeg; // grados por segundo
    float _degreesToRotate;    // grados totales a rotar (valor absoluto)
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

        // Inicializar ángulo en el primer frame (basado en la posición actual)
        if (!_initialized) {
            Vector2 offset = _transform->position - _center;
            _currentAngleDeg = atan2f(offset.y, offset.x) * 180.0f / 3.14159265f;
            _accumulatedDeg = 0.f;
            _initialized = true;
        }

        // Avanzar ángulo
        float deltaDeg = _angularVelocityDeg * deltaTime;
        _currentAngleDeg += deltaDeg;
        _accumulatedDeg += std::abs(deltaDeg);

        // Aplicar nueva posición según ángulo (convertir a radianes)
        const float PI = 3.14159265f;
        float rad = _currentAngleDeg * PI / 180.0f;
        _transform->position.x = _center.x + _radius * std::cos(rad);
        _transform->position.y = _center.y + _radius * std::sin(rad);

        // Comprobar finalización
        if (_accumulatedDeg >= _degreesToRotate) {
            _finished = true;
        }
    }
};