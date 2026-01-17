#pragma once
#include "Bullet.h"

class EnemyBullet : public Bullet {
public:
	EnemyBullet(Vector2 initPos)
		: Bullet() {
		_transform->position = initPos;
		_transform->scale = Vector2(0.5f, 0.15f);
		_physics->SetVelocity(Vector2(-1500.f, 0.f));
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	void Update() override {
		SetLifeTime();
		Object::Update();
	}

	void SetLifeTime() override {
		if (_transform->position.x < 0) {
			std::cout << "EnemyBullet Destroyed" << std::endl;
			Destroy();
		}
	}

	void OnCollision(Object* other) override {}

	void Attack(IDamageable* other) const override {
		other->ReceiveDamage(15);
	}
};