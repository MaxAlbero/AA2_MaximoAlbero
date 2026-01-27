#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "CirclerMovement.h"

class CirclerBody : public Enemy {
public:
    // distance: separación deseada respecto a la cabeza (en píxeles)
    CirclerBody(float distance = 120.f)
        : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/pinky.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->size = Vector2(80.f, 80.f);

        // Posición inicial razonable (aparece en el centro superior como la cabeza)
        _transform->position = Vector2(RM->WINDOW_WIDTH / 2.f, -_transform->size.y);

        _physics->AddCollider(new AABB(_transform->position, _transform->size));
        SetHealth(999999);
        SetPointsValue(0);

        // Parámetros compartidos con Circler (manténlos sincronizados si cambias Circler)
        float speed = 200.f;
        float baseRadius = 300.f;
        Vector2 screenCenter(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
        float angularVelocity = 90.f; // grados por segundo

        // Offset aplicado a TODOS los targets/centros para crear separación
        // Puedes ajustar la dirección/valor del offset para obtener el efecto deseado
        Vector2 offset = Vector2(-distance, -distance * 0.4f);

        // Patrón: bajar - círculo - moverse - círculo - moverse - círculo - salir
        // 1) bajar al primer punto (igual que la cabeza, con offset)
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 4.f) + offset, speed));

        // 2) primer círculo (mismo centro, radio reducido y centro desplazado)
        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - distance),            // radius reducido
            screenCenter + offset,                             // centro desplazado
            angularVelocity));

        // 3) moverse al siguiente target (con offset)
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 50.f, screenCenter.y + 10.f) + offset, speed));

        // 4) segundo círculo (centro y radio ajustados)
        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - 100.f - distance),
            Vector2(screenCenter.x + 150.f, screenCenter.y + 100.f) + offset,
            angularVelocity));

        // 5) moverse a otro punto (con offset)
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 200.f, screenCenter.y + 150.f) + offset, speed));

        // 6) tercer círculo (centro y radio ajustados)
        movements.push_back(new CirclerMovement(_transform, _physics,
            std::max(10.f, baseRadius - 250.f - distance),
            Vector2(screenCenter.x + 250.f, screenCenter.y + 200.f) + offset,
            angularVelocity));

        // 7) salir por arriba (con offset)
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, -200.f) + offset, speed));
    }

    // No override Update: Enemy::Update ejecutará la secuencia de movements
};