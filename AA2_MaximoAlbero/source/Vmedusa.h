#pragma once
#include "Enemy.h"
#include "UpLinearMovement.h"
#include "IdleMovement.h"

class Vmedusa : public Enemy {
public:
	Vmedusa(Vector2 spawnPosition, float speed)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/VMedusa.png", Vector2(0.f, 0.f), Vector2(360.f, 360.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = spawnPosition;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		
		SetHealth(30);  
		SetPointsValue(100);
		
		float yThreshold = RM->WINDOW_HEIGHT / 2.f;

		movements.push_back(new UpLinearMovement(_transform, _physics, yThreshold, speed));
		movements.push_back(new IdleMovement(_transform, _physics, 1.f));
		movements.push_back(new UpLinearMovement(_transform, _physics, speed));
	}
};