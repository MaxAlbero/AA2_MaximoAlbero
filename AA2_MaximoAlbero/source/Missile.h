#pragma once
#include "Enemy.h"
#include "RightLinearMovement.h"

class Missile : public Enemy {
public:
	Missile(Vector2 spawnPos, float speed)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));

		_transform->size = Vector2(100.f, 100.f);
		//_transform->position = spawnPosition;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(30);
		SetPointsValue(100);

		movements.push_back(new RightLinearMovement(_transform, _physics, speed));
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