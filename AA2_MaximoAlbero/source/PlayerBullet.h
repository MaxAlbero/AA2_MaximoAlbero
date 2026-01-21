#pragma once
#include "Bullet.h"
#include <cmath>

class PlayerBullet : public Bullet {
public:
	PlayerBullet(Vector2 initPos)
		: Bullet() {
		_transform->position = initPos;
		_transform->scale = Vector2(0.5f, 0.15f);
		_physics->SetVelocity(Vector2(2000.f, 0.f));
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	// Nueva sobrecarga: dispara con un ángulo en grados (0 = hacia la derecha)
	PlayerBullet(Vector2 initPos, float angleDegrees, float speed = 2000.f)
		: Bullet() {
		_transform->position = initPos;
		_transform->scale = Vector2(0.5f, 0.15f);

		const float PI = 3.14159265f;
		float rad = angleDegrees * PI / 180.0f;
		Vector2 dir = Vector2(std::cos(rad), std::sin(rad));
		dir.Normalize();
		_physics->SetVelocity(dir * speed);

		_transform->rotation = angleDegrees; // opcional: rotar la sprite de la bala
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	void Update() override {
		SetLifeTime();
		Object::Update();
	}

	void SetLifeTime() override {
		if (_transform->position.x > RM->WINDOW_WIDTH) {
			//std::cout << "Bullet Destroyed" << std::endl;
			Destroy();
		}
	}

	void OnCollision(Object* other) override {}

	void Attack(IDamageable* other) const override {
		other->ReceiveDamage(10);
	}
};