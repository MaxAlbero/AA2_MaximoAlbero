#pragma once
#include "Enemy.h"
#include "TargetMovement.h"
#include "CirclerMovement.h"

class Circler : public Enemy {
public:
	Circler() 
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/pacman.png",
			Vector2(0.f, 0.f), Vector2(500.f, 500.f));

		_transform->scale = Vector2(0.5f, 0.5f);
		_transform->position = Vector2(RM->WINDOW_WIDTH / 2.f, -_transform->size.y);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(1000);
		SetPointsValue(500);

		float speed = 200.f;
		float radius = 300.f;
		Vector2 screenCenter(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
		float angularVelocity = 90.f; // grados por segundo

        // Patrón: bajar - círculo - moverse - círculo - moverse - círculo - salir
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 4.f), speed));

        movements.push_back(new CirclerMovement(_transform, _physics,
            radius, screenCenter, angularVelocity));

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 50.f, screenCenter.y + 10.f), speed));

        movements.push_back(new CirclerMovement(_transform, _physics,
            radius - 100.f, Vector2(screenCenter.x + 150.f, screenCenter.y + 100.f), angularVelocity));

        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(screenCenter.x + 200.f, screenCenter.y + 150.f), speed)); 

        movements.push_back(new CirclerMovement(_transform, _physics,
            radius - 250.f, Vector2(screenCenter.x + 250.f, screenCenter.y + 200.f), angularVelocity));

        // Salir por arriba
        movements.push_back(new TargetMovement(_transform, _physics,
            Vector2(RM->WINDOW_WIDTH / 2.f, -200.f), speed));
    }

    void Update() override { //TODO: REVISAR SI ESTO HACE FALTA AQUI (QUE DIRIA QUE NO)
        // Actualizar movimientos
        Enemy::Update();

        // Destruir si sale de pantalla
        if (_transform->position.y + _transform->size.y < 0.f) {
            std::cout << "CIRCLER DESTROYED" << std::endl;
            Destroy();
        }
    }
};

// Vector2(_transform->position.x - 50.f, _transform->position.y - 100.f)