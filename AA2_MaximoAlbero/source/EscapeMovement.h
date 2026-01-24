#pragma once
#include "EnemyMovement.h"
#include "RenderManager.h"
#include <cmath>

class EscapeMovement : public EnemyMovement {
private:
    float _speed;
    Vector2 _escapeDirection;
    bool _directionSet;

public:
    EscapeMovement(Transform* transform, RigidBody* rigidBody, float speed)
        : EnemyMovement(transform, rigidBody),
        _speed(speed),
        _directionSet(false) {
    }

    void Update(float deltaTime) override {
        if (_finished) return;

        if (!_directionSet) {
            // Calcular borde más cercano
            Vector2 currentPos = _transform->position;

            float distLeft = currentPos.x;
            float distRight = RM->WINDOW_WIDTH - currentPos.x;
            float distTop = currentPos.y;
            float distBottom = RM->WINDOW_HEIGHT - currentPos.y;

            float minDist = distLeft;
            _escapeDirection = Vector2(-1.f, 0.f);  // Izquierda

            if (distRight < minDist) {
                minDist = distRight;
                _escapeDirection = Vector2(1.f, 0.f);  // Derecha
            }
            if (distTop < minDist) {
                minDist = distTop;
                _escapeDirection = Vector2(0.f, -1.f);  // Arriba
            }
            if (distBottom < minDist) {
                _escapeDirection = Vector2(0.f, 1.f);  // Abajo
            }

            _directionSet = true;
        }

        _rigidBody->SetVelocity(_escapeDirection * _speed);

        // Este movimiento nunca termina, el enemigo se destruye al salir de pantalla
    }
};