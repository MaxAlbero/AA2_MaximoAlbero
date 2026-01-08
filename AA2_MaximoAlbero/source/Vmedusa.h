#pragma once
#include "Enemy.h"
#include "TimeManager.h"

class Vmedusa : public Enemy {
private:
	float moveSpeed;
	float stopDistance;
	float stopDuration;
	float stopTimer;
	float nextStopY;

public:
	Vmedusa(Vector2 spawnPosition)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/bebe.jpg", Vector2(0.f, 0.f), Vector2(360.f, 360.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = spawnPosition;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		
		enemyHealth = 200;
		currentState = SIMPLE_MOVE;
		
		moveSpeed = 100.f;
		stopTimer = 0.f;
		stopDuration = 1.f;
		stopDistance = 150.f;
		nextStopY = spawnPosition.y - stopDistance;
	}

	void Update() override {

		switch (currentState) {
		case SIMPLE_MOVE:
			Move();
			break;
		case STAY:
			EnemyBehaviour();
			break;
		}


		if (_transform->position.y + _transform->size.y < 0.f) {
			std::cout << "AAAAAAAAAAHHHHHHHHH" << std::endl;
			Destroy();
		}

		Object::Update();
	}

	void Move() override {
		_physics->SetVelocity(Vector2(0.f, -moveSpeed));

		if (_transform->position.y <= nextStopY) {
			currentState = STAY;
			stopTimer = 0.f;
			_physics->SetVelocity(Vector2(0.f, 0.f));

			//std::cout << "Medusa detenida en Y: " << _transform->position.y
			//	<< ", Siguiente parada en: " << nextStopY << std::endl;
		}
	}

	//void OnCollision(Object* other) override;
	void EnemyBehaviour() override {


		stopTimer += TM.GetDeltaTime();

		//std::cout << TM.GetDeltaTime() << std::endl;

		if (stopTimer >= stopDuration) {

			//std::cout << "VerticalMedusa Behaviour" << std::endl;
			nextStopY -= stopDistance;

			currentState = SIMPLE_MOVE;
			stopTimer = 0.f;
		}
	}
};