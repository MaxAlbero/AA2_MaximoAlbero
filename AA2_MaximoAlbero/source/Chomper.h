#pragma once
#include "Enemy.h"

class Chomper : public Enemy {
private:
	Vector2 circleCenter;
	float circleRadius;
	float circleAngle;
	float circleSpeed;
	bool circleComplete;
	float horizontalMove;
	int health;

	float stopDuration;
	float stopTimer;

public:
	Chomper(Vector2 spawnPos)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f,0.f), Vector2(306.f, 562.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = spawnPos;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		health = 20;
		currentState = STAY;

		stopTimer = 0.f;
		stopDuration = 1.f;

		circleRadius = 20.f;
		circleAngle = 0.f;
		circleSpeed = 10.0f;
		circleComplete = false;
		horizontalMove = 50.f;

		circleCenter = spawnPos;
	}

	void Update() override {

		switch (currentState) {
		case STAY:
			EnemyBehaviour();
			break;
		case CIRCLE_MOVE:
			CircleMove();
			break;
		}


		if (_transform->position.x < -_transform->size.x) {
			std::cout << "Ah bueno adios master" << std::endl;
			Destroy();
		}

		Object::Update();
	}

	void EnemyBehaviour() override {

		stopTimer += TM.GetDeltaTime();

		if (stopTimer >= stopDuration) {
			currentState = CIRCLE_MOVE;
		}
	}

	void CircleMove() override {
		float pi = 3.14159f;

		circleCenter.x -= horizontalMove * TM.GetDeltaTime();
		circleAngle += circleSpeed * TM.GetDeltaTime();

		float newX = circleCenter.x + circleRadius * cos(circleAngle);
		float newY = circleCenter.y + circleRadius * sin(circleAngle);

		// Mover a la nueva posici�n
		_transform->position = Vector2(newX, newY);

		// Verificar si el chomper ha completado una vuelta completa
		if (circleAngle >= 2.0f * pi) {
			circleAngle = 0.f;
		}
	}
};