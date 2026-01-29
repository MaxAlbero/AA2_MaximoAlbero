#pragma once
#include "Enemy.h"
#include "UpLinearMovement.h"
#include "IdleMovement.h"

class Vmedusa : public Enemy {
public:
	Vmedusa(Vector2 spawnPosition)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/VMedusa.png", Vector2(0.f, 0.f), Vector2(360.f, 360.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = spawnPosition;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		
		SetHealth(30);  
		SetPointsValue(100);
		
		float speed = 200.f;
		float yThreshold = RM->WINDOW_HEIGHT / 2.f;

		/*do
		{		*/	
			movements.push_back(new UpLinearMovement(_transform, _physics, yThreshold, speed));
			movements.push_back(new IdleMovement(_transform, _physics, 1.f));
			movements.push_back(new UpLinearMovement(_transform, _physics, speed));
			movements.push_back(new UpLinearMovement(_transform, _physics, yThreshold, speed));
			movements.push_back(new IdleMovement(_transform, _physics, 1.f));
			movements.push_back(new UpLinearMovement(_transform, _physics, speed));
			movements.push_back(new UpLinearMovement(_transform, _physics, yThreshold, speed));
			movements.push_back(new IdleMovement(_transform, _physics, 1.f));
			movements.push_back(new UpLinearMovement(_transform, _physics, speed));
		//} while (!IsPendingDestroy());
	}

	void Update() override { //TODO: REVISAR SI ESTO HACE FALTA AQUI (QUE DIRIA QUE NO)
		// Actualizar movimientos
		Enemy::Update();

		// Destruir si sale de pantalla
		if (_transform->position.y + _transform->size.y < 0.f) {
			std::cout << "Vertical Medusa DESTROYED" << std::endl;
			Destroy();
		}
	}
};