#pragma once
#include "Enemy.h"
#include "UpLinearMovement.h"

class Nuke : public Enemy {
public:
	Nuke(Vector2 spawnPos, float speed)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/missile.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f));

		_transform->position = spawnPos;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(30);
		SetPointsValue(100);

		movements.push_back(new UpLinearMovement(_transform, _physics, speed));
	}

	void Update() override {
		Enemy::Update();

		if (_transform->position.y + _transform->size.y < 0.f) {
			Destroy();
		}
	}
};