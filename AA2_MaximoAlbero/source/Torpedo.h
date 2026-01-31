#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"

class Torpedo : public Enemy {
public:
	Torpedo(Vector2 spawnPos, float speed)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/torpedo.png", Vector2(0.f, 0.f), Vector2(216.f, 233.f));

		_transform->position = spawnPos;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(30);
		SetPointsValue(100);

		movements.push_back(new LeftLinearMovement(_transform, _physics, speed));
	}
};