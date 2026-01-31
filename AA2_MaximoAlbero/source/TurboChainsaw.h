#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "CirclerMovement.h" 

enum ChainsawDirection {
    FROM_LEFT,
    FROM_RIGHT
};

class TurboChainsaw : public Enemy {
public:
    TurboChainsaw(ChainsawDirection direction) : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/chainsaw.png",
            Vector2(0.f, 0.f), Vector2(500.f, 500.f));

        _transform->scale = Vector2(0.25f, 0.25f);
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(50);
        SetPointsValue(250);

        float speed = 150.f;
        float radius = 100.f;
        float angularVelocity = 180.f; // grados por segundo

        Vector2 screenCenter(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);

        if (direction == FROM_LEFT) {
            // Viene desde la izquierda
            Vector2 startPos(-_transform->size.x, screenCenter.y);
            Vector2 orbitPos(screenCenter.x - radius, screenCenter.y);
            Vector2 exitPos(-_transform->size.x - 200.f, screenCenter.y);

            _transform->position = startPos;

            // Patrón: entrar - orbitar - salir
            movements.push_back(new TargetMovement(_transform, _physics, orbitPos, speed));
            movements.push_back(new CirclerMovement(_transform, _physics, radius, screenCenter, angularVelocity));
            movements.push_back(new TargetMovement(_transform, _physics, exitPos, speed));
        }
        else {
            // Viene desde la derecha
            Vector2 startPos(RM->WINDOW_WIDTH + _transform->size.x, screenCenter.y);
            Vector2 orbitPos(screenCenter.x + radius, screenCenter.y);
            Vector2 exitPos(RM->WINDOW_WIDTH + _transform->size.x + 200.f, screenCenter.y);

            _transform->position = startPos;

            // Patrón: entrar - orbitar - salir
            movements.push_back(new TargetMovement(_transform, _physics, orbitPos, speed));
            movements.push_back(new CirclerMovement(_transform, _physics, radius, screenCenter, angularVelocity));
            movements.push_back(new TargetMovement(_transform, _physics, exitPos, speed));
        }
    }
};