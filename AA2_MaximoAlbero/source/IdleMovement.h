#pragma once
#include "EnemyMovement.h"

class IdleMovement : public EnemyMovement {
private:
    float _duration;    // Duración total del idle
    float _elapsed;     // Tiempo transcurrido

public:
    IdleMovement(Transform* transform, RigidBody* rigidBody, float duration)
        : EnemyMovement(transform, rigidBody),
        _duration(duration),
        _elapsed(0.f) {
    }

    void Update(float deltaTime) override {
        if (_finished) return;

        // Detener completamente el movimiento
        _rigidBody->SetVelocity(Vector2(0.f, 0.f));

        // Incrementar tiempo transcurrido
        _elapsed += deltaTime;

        // Terminar cuando se alcanza la duración
        if (_elapsed >= _duration) {
            _finished = true;
        }
    }
};