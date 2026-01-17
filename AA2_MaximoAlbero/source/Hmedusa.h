#pragma once
#include "Enemy.h"

class Hmedusa : public Enemy {
private:
	float moveSpeed;
	int health;
public:
	Hmedusa(Vector2 spawnPos, int speed)
		: Enemy ()
	{
		_renderer = new ImageRenderer(_transform, "resources/bebe.jpg", Vector2(0.f, 0.f), Vector2(360.f, 360.f));

		//_transform->size = Vector2(360.f, 360.f);
		_transform->rotation = 270.f;
		_transform->position = spawnPos; //<-- Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT / 2.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		health = 20;
		moveSpeed = speed;
	}

	void Update() override {
		EnemyBehaviour();


		if (_transform->position.x + _transform->size.x < 0.f) {
			Destroy();
		}

		Object::Update();
	}

	//void OnCollision(Object* other) override;
	void EnemyBehaviour() override {
		_physics->SetVelocity(Vector2(-moveSpeed, 0.f));

	}
};