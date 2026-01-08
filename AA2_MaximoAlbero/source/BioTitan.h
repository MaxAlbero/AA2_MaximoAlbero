#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"

class BioTitan : public Enemy {
private:
	int moveSpeed;

	float shootTimer;
	float shootCooldown;
	int shotsFired;
	int maxShots;
public:
	BioTitan()
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));


		_transform->size = Vector2(300.f,300.f);
		_transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT / 2.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		enemyHealth = 300;
		currentState = SIMPLE_MOVE;

		moveSpeed = 100.f;
		shootTimer = 0.f;
		shootCooldown = 0.5f; // Dispara cada 0.5 segundos
		shotsFired = 0;
		maxShots = 5;
	}


	void Update() override {

		switch (currentState) {
		case SIMPLE_MOVE:
			Move();
			break;
		case SHOOT:
			Shoot();
			break;
		case STAY:
			EnemyBehaviour();
			break;
		}


		Object::Update();
	}

	void Move() override {
		_physics->SetVelocity(Vector2(-moveSpeed, 0.f));

		if (_transform->position.x <= RM->WINDOW_WIDTH - _transform->size.x) {
			_physics->SetVelocity(Vector2(0.f, 0.f));
			currentState = SHOOT;
		}
	}

	//void Attack(IAttacker* other) const override;

	void Shoot() {
		shootTimer += TM.GetDeltaTime();

		if (shootTimer >= shootCooldown) {
			// Crear bala desde la posición del BioTitan
			Vector2 bulletPos = Vector2(
				_transform->position.x - _transform->size.x / 2.f,
				_transform->position.y
			);

			EnemyBullet* bullet = new EnemyBullet(bulletPos);
			SPAWNER.SpawnObject(bullet);

			shootTimer = 0.f;
			shotsFired++;

			std::cout << "BioTitan shoots! (" << shotsFired << "/" << maxShots << ")" << std::endl;

			if (shotsFired >= maxShots) {
				currentState = STAY;
			}
		}
	}


	void EnemyBehaviour() override {
		shootTimer = 0.f;
		shootCooldown = 0.5f;
		shotsFired = 0;
		maxShots = 5;

		currentState = SHOOT;
	}
};