#pragma once
#include "Enemy.h"
#include "UpLinearMovement.h"
#include "RightLinearMovement.h"
#include "DownLinearMovement.h"
#include "IdleMovement.h"
#include "TargetMovement.h"

class Angrygons : public Enemy {
public:
    Angrygons(Vector2 spawnPos, float speed)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/bebe.jpg",
            Vector2(0.f, 0.f), Vector2(360.f, 360.f));

        //_transform->rotation = 270.f;
        _transform->scale = Vector2(0.5f, 0.5f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(20);
        SetPointsValue(100);

        float xThreshold = _transform->position.x + 300.f;
        float yThreshold = RM->WINDOW_HEIGHT - 100.f;
        float duration = 2.f;
        Vector2 targetPos = Vector2(RM->WINDOW_WIDTH / 1.2f, yThreshold);

        // Movimiento simple: izquierda sin umbral (sale de pantalla)
        movements.push_back(new RightLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new DownLinearMovement(_transform, _physics, yThreshold, speed));
        movements.push_back(new TargetMovement(_transform, _physics, targetPos, speed));
        movements.push_back(new UpLinearMovement(_transform, _physics, speed));
    }

    void Update() override { //TODO: REVISAR SI ESTO HACE FALTA AQUI (QUE DIRIA QUE NO)
        // Actualizar movimientos
        Enemy::Update();

        // Destruir si sale de pantalla
        //if (_transform->position.x + _transform->size.x < 0.f) {
        //    Destroy();
        //}
    }
};