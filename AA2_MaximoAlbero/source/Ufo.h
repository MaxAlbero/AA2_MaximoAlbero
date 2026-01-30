#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "IdleMovement.h"

class Ufo : public Enemy {
public:
    Ufo(Vector2 spawnPos, float speed)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/bebe.jpg",
            Vector2(0.f, 0.f), Vector2(360.f, 360.f));

        _transform->rotation = 270.f;
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(20);
        SetPointsValue(100);

        float xThreshold = RM->WINDOW_WIDTH / 2.f;
        float duration = 2.f;

        // Movimiento simple: izquierda sin umbral (sale de pantalla)
        movements.push_back(new RightLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new IdleMovement(_transform, _physics, duration));
        movements.push_back(new LeftLinearMovement(_transform, _physics, speed));
    }

    void Update() override { //TODO: REVISAR SI ESTO HACE FALTA AQUI (QUE DIRIA QUE NO)
        // Actualizar movimientos
        Enemy::Update();

        // Destruir si sale de pantalla
        if (_transform->position.x + _transform->size.x < 0.f) {
            Destroy();
        }
    }
};