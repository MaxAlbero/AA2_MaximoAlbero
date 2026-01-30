#pragma once
#include "Enemy.h"
#include "RightLinearMovement.h"
#include "SpreadMovement.h"
#include "CirclerMovement.h"
#include "ReuniteMovement.h"
#include "LeftLinearMovement.h"
#include <cmath>

class Amoeba : public Enemy {
private:
    int _index;
    Vector2 _center;
    Vector2 _gridOffset;
    Vector2 _targetSpreadPos;
    float _circleRadius;

public:
    // index: 0..7 para decidir la posición del spread
    Amoeba(const Vector2& spawnPos, int index)
        : Enemy(), _index(index)
    {
        // Configurar renderer
        _renderer = new ImageRenderer(_transform, "resources/slime.png", Vector2(0.f, 0.f), Vector2(1200.f, 1200.f));
        _transform->size = Vector2(48.f, 48.f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        // Configurar stats
        SetHealth(10);
        SetPointsValue(50);

        // Calcular posiciones
        _center = Vector2(RM->WINDOW_WIDTH * 0.5f, RM->WINDOW_HEIGHT * 0.5f);

        // Layout de las 8 posiciones alrededor del centro
        static const Vector2 grid[8] = {
            Vector2(-1.f,-1.f), Vector2(0.f,-1.f), Vector2(1.f,-1.f),
            Vector2(-1.f, 0.f),                    Vector2(1.f, 0.f),
            Vector2(-1.f, 1.f), Vector2(0.f, 1.f), Vector2(1.f, 1.f)
        };
        _gridOffset = grid[_index % 8] * 60.f; // escala del spread
        _targetSpreadPos = _center + _gridOffset;

        // Calcular radio del círculo
        _circleRadius = 24.f + (std::abs(_gridOffset.x) + std::abs(_gridOffset.y)) * 0.25f;


        movements.push_back(new RightLinearMovement(_transform, _physics, _center.x, 800.f));
        movements.push_back(new SpreadMovement(_transform, _physics, _center, _targetSpreadPos, 0.6f));
        movements.push_back(new CirclerMovement(_transform, _physics, _circleRadius, _targetSpreadPos, 360.f)); // 360°/s = 1 vuelta/segundo
        movements.push_back(new CirclerMovement(_transform, _physics, _circleRadius, _targetSpreadPos, 360.f));
        movements.push_back(new ReuniteMovement(_transform, _physics, _targetSpreadPos, _center, 0.6f));
        movements.push_back(new RightLinearMovement(_transform, _physics, 600.f));
    }

    virtual ~Amoeba() {}

    void Update() override {
        // Destruir si sale de pantalla (por la izquierda)
        if (_transform->position.x + _transform->size.x > RM->WINDOW_WIDTH) {
            Destroy();
            return; // IMPORTANTE: salir inmediatamente después de destruir
        }

        // Actualizar movimientos (llamar al Update de Enemy)
        Enemy::Update();
    }
};