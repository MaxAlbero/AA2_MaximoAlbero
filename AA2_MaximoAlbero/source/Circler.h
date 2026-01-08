#pragma once
#include "Enemy.h"

class Circler : public Enemy {
private:
	float moveSpeed;

	Vector2 circleCenter;
	float circleRadius;
	float circleAngle;
	float circleSpeed;
	bool circleComplete;
	float horizontalMove;

	int circleCount;
	int maxCircles;
	float startAngle;

public:
	Circler()
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = Vector2(RM->WINDOW_WIDTH / 2.f, -_transform->size.y);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		enemyHealth = 1000;
		currentState = SIMPLE_MOVE;

		circleRadius = 300.f;
		circleAngle = 0.f;
		circleSpeed = 3.0f;
		circleComplete = false;

		moveSpeed = 200.f;

		circleCount = 0;
		maxCircles = 5;

		horizontalMove = 20.f;
		startAngle = -1.5707963f;
	}

	void Update() override {

		switch (currentState) {
		case SIMPLE_MOVE:
			Move();
			break;
		case CIRCLE_MOVE:
			CircleMove();
			break;
		case RETURN:
			GoAway();
			break;
		}


		if (_transform->position.y < -_transform->size.y) {
			std::cout << "Ah bueno adios master" << std::endl;
			Destroy();
		}

		Object::Update();
	}

	void Move() override {
		_physics->SetVelocity(Vector2(0.f, moveSpeed));
		  
		if (_transform->position.y >= RM->WINDOW_HEIGHT / 4.f) {
			currentState = CIRCLE_MOVE;
			circleCenter = Vector2(RM->WINDOW_WIDTH / 2.f,RM->WINDOW_HEIGHT / 2.f);
			circleAngle = startAngle;
			_physics->SetVelocity(Vector2(0.f, 0.f));
			std::cout << "Iniciando movimiento circular" << std::endl;
		}
	}

	void CircleMove() override {
		float pi = 3.14159f;

		circleAngle += circleSpeed * TM.GetDeltaTime();

		float newX = circleCenter.x + circleRadius * cos(circleAngle);
		float newY = circleCenter.y + circleRadius * sin(circleAngle);
		_transform->position = Vector2(newX, newY);

		if (circleAngle >= startAngle + 2.0f * pi) {
			circleCount++;
			std::cout << "Vueltas completadas: " << circleCount << std::endl;

			// Resetear al ángulo inicial (punto alto)
			circleAngle = startAngle;
			circleRadius -= 50.f;

			if (circleCount >= maxCircles) {
				currentState = RETURN;
				//Posicionar en el punto más alto antes de salir
				_transform->position = Vector2(
					circleCenter.x + circleRadius * cos(startAngle),
					circleCenter.y + circleRadius * sin(startAngle)
				);
				std::cout << "5 vueltas completadas. Regresando desde punto alto..." << std::endl;
			}
			else {
				circleCenter.x -= horizontalMove;
			}
		}
	}
	void GoAway() override {
		_physics->SetVelocity(Vector2(0.f, -moveSpeed));
	}
};