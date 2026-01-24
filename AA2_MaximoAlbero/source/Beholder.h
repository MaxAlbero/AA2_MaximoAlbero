#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "ChaseMovement.h"
#include "EscapeMovement.h" // Lo crearemos después

class Beholder : public Enemy {
public:
    Beholder(Vector2 spawnPos, Transform* playerTransform) : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/image.png",
            Vector2(0.f, 0.f), Vector2(306.f, 562.f));

        _transform->size = Vector2(100.f, 100.f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(100);
        SetPointsValue(300);

        float speed = 200.f;
        float xThreshold = RM->WINDOW_WIDTH * 2.f / 3.f; // Se detiene en 2/3 de la pantalla

        // Patrón: moverse a la izquierda hasta un punto - perseguir 3 veces - escapar
        movements.push_back(new LeftLinearMovement(_transform, _physics, xThreshold, speed));
        movements.push_back(new ChaseMovement(_transform, _physics, playerTransform, speed, 3, 1.5f, 10.f));
        movements.push_back(new EscapeMovement(_transform, _physics, speed)); // Escapar al borde más cercano
    }

    void Update() override {
        // Actualizar movimientos
        Enemy::Update();

        // Destruir si sale de pantalla
        if (_transform->position.x + _transform->size.x < 0.f ||
            _transform->position.x > RM->WINDOW_WIDTH ||
            _transform->position.y + _transform->size.y < 0.f ||
            _transform->position.y > RM->WINDOW_HEIGHT) {
            Destroy();
        }
    }
};