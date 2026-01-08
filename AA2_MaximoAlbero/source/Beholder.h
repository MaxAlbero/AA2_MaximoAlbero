#pragma once
#include "Enemy.h"
#include "Player.h"

class Beholder : public Enemy {
private:
	float moveSpeed;

	float stopDuration;
	float stopTimer;

	Vector2 targetPosition;
	Player* player;
	float tolerance;

	int numOfChase;
	int maxChases;
	Vector2 escapeDirection;
	bool escapeDirectionSet;

public:
	Beholder(Vector2 spawnPos, Player* playerRef)
		: Enemy(), player(playerRef) {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->position = spawnPos;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));


		enemyHealth = 100;
		currentState = STAY;
		moveSpeed = 200.f;

		stopDuration = 1.5f;
		stopTimer = 0.f;
		
		tolerance = 10.f;

		numOfChase = 0;
		maxChases = 3;
		escapeDirectionSet = false;

		if (player) {
			targetPosition = player->GetTransform()->position;
		}
	}
	
	void Update() override {

		if (player == nullptr) {
			Destroy();
			return;
		}

		if (_transform->position.x + _transform->size.x < 0.f ||
			_transform->position.x > RM->WINDOW_WIDTH ||
			_transform->position.y + _transform->size.y < 0.f ||
			_transform->position.y > RM->WINDOW_HEIGHT) {
			Destroy();
			return;
		}

		switch (currentState) {
		case STAY:
			EnemyBehaviour();
			break;
		case CHASE:
			Move();
			break;
		case RETURN:
			GoAway();
			break;
		}

		Object::Update();
	}

	   
	void EnemyBehaviour() override {

		_physics->SetVelocity(Vector2(0.f, 0.f));

		if (numOfChase >= maxChases) {
			currentState = RETURN;
			escapeDirectionSet = false;
			std::cout << "Beholder intentando escapar..." << std::endl;
			return;
		}

		stopTimer += TM.GetDeltaTime();

		if (stopTimer >= stopDuration) {
			targetPosition = player->GetTransform()->position;
			currentState = CHASE;
			stopTimer = 0.f;
			numOfChase++;
		}
	}

	void Move() override {
		Vector2 currentPos = _transform->position;

		Vector2 direction = targetPosition - currentPos;
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance <= tolerance) {
			currentState = STAY;
			_physics->SetVelocity(Vector2(0.f, 0.f));
			return;
		}

		direction.x /= distance;
		direction.y /= distance;

		_physics->SetVelocity(Vector2(direction.x * moveSpeed, direction.y * moveSpeed));
	}

	void GoAway() override {
		if (!escapeDirectionSet) {
			Vector2 currentPos = _transform->position;

			float distLeft = currentPos.x;
			float distRight = RM->WINDOW_WIDTH - currentPos.x;
			float distTop = currentPos.y;
			float distBottom = RM->WINDOW_HEIGHT - currentPos.y;

			float minDist = distLeft;
			escapeDirection = Vector2(-1.f, 0.f);  // Izquierda

			if (distRight < minDist) {
				minDist = distRight;
				escapeDirection = Vector2(1.f, 0.f);  // Derecha
			}
			if (distTop < minDist) {
				minDist = distTop;
				escapeDirection = Vector2(0.f, -1.f);  // Arriba
			}
			if (distBottom < minDist) {
				minDist = distBottom;
				escapeDirection = Vector2(0.f, 1.f);  // Abajo
			}

			escapeDirectionSet = true;
			std::cout << "Beholder escapa hacia el borde más cercano" << std::endl;
		}
		
		_physics->SetVelocity(Vector2(escapeDirection.x * moveSpeed, escapeDirection.y * moveSpeed));
	}



};