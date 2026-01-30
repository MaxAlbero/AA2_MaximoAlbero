#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "IdleMovement.h"
#include "ShootMovement.h"

class BioTitan : public Enemy {
public:
    BioTitan() : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/image.png",
            Vector2(0.f, 0.f), Vector2(306.f, 562.f));

        _transform->size = Vector2(300.f, 300.f);
        _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT / 2.f);
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(300);
        SetPointsValue(500);

        float speed = 100.f;
        Vector2 stopPos(RM->WINDOW_WIDTH - _transform->size.x, RM->WINDOW_HEIGHT / 2.f);

        // Patrón: entrar - disparar - pausa - disparar - pausa - disparar - salir
        movements.push_back(new TargetMovement(_transform, _physics, stopPos, speed));

        movements.push_back(new IdleMovement(_transform, _physics, 2.0f));

        // Primera ráfaga: dispara entre 3-7 veces, con 0.5s entre cada disparo
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));

        // Pausa
        movements.push_back(new IdleMovement(_transform, _physics, 1.0f));

        // Segunda ráfaga
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));

        // Pausa
        movements.push_back(new IdleMovement(_transform, _physics, 1.0f));

        // Tercera ráfaga
        movements.push_back(new ShootMovement(_transform, 0.5f, 3, 7, 50.f));
    }

    void Update() override {
        Enemy::Update();

        // Destruir si sale completamente de pantalla
        if (_transform->position.x > RM->WINDOW_WIDTH + 300.f) {
            Destroy();
        }
    }
};