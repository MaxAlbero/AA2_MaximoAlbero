#pragma once
#include "EnemyMovement.h"

class VerticalLinearMovement : public EnemyMovement {
private:
    float _speed;
    float _yThreshold; // Posición X donde termina el movimiento (opcional)
    bool _hasThreshold;

public:
    // Constructor con umbral (para Beholder - se detiene en cierto punto)
    VerticalLinearMovement(Transform* transform, RigidBody* rigidBody, float yThreshold, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(yThreshold), _speed(speed), _hasThreshold(true) {
    }

    // Constructor sin umbral (para Hmedusa - sale de pantalla)
    VerticalLinearMovement(Transform* transform, RigidBody* rigidBody, float speed)
        : EnemyMovement(transform, rigidBody),
        _yThreshold(-1000.f), _speed(speed), _hasThreshold(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        _rigidBody->SetVelocity(Vector2(0.f, -_speed));

        // Si tiene umbral, verificar si lo alcanzó
        if (_hasThreshold && _transform->position.y <= _yThreshold) {
            _transform->position.y = _yThreshold;
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _finished = true;
        }

        // Si no tiene umbral, nunca termina (sale de pantalla y se destruye por otro lado)
        // La clase Enemy o el Update general debe manejar la destrucción cuando sale de pantalla
    }
};