#pragma once
#include "EnemyMovement.h"
#include <cmath>
#include <algorithm>

class ReuniteMovement : public EnemyMovement {
private:
    Vector2 _startPosition;
    Vector2 _targetPosition;
    float _duration;
    float _elapsedTime;
    bool _initialized;

    static Vector2 Lerp(const Vector2& a, const Vector2& b, float t) {
        return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
    }

    static float SmoothStep(float t) {
        t = std::max(0.f, std::min(1.f, t));
        return t * t * (3.f - 2.f * t);
    }

public:
    ReuniteMovement(Transform* transform, RigidBody* rigidBody, Vector2 startPosition, Vector2 targetPosition, float duration = 0.6f)
        : EnemyMovement(transform, rigidBody),
        _startPosition(startPosition), _targetPosition(targetPosition),
        _duration(duration), _elapsedTime(0.f), _initialized(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        // Inicializar la posición de inicio en el primer frame
        if (!_initialized) {
            _startPosition = _transform->position;
            _initialized = true;
        }

        // Asegurar que la velocidad sea 0
        _rigidBody->SetVelocity(Vector2(0.f, 0.f));

        _elapsedTime += deltaTime;
        float t = std::min(1.f, _elapsedTime / _duration);

        // Establecer posición directamente
        _transform->position = Lerp(_startPosition, _targetPosition, SmoothStep(t));

        if (t >= 1.f) {
            _transform->position = _targetPosition;
            _finished = true;
        }
    }
};