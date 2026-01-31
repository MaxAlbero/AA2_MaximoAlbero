#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"

class Missile : public Enemy {
public:
	Missile(Vector2 spawnPos, float speed)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/missile.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f));

		
		_transform->size = Vector2(100.f, 100.f);
		_transform->rotation = 270.f;
		_transform->position = spawnPos;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(30);
		SetPointsValue(100);

		movements.push_back(new LeftLinearMovement(_transform, _physics, speed));
	}
};