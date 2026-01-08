#pragma once
#include "Enemy.h"
class KillerWhale : public Enemy {
private:
	float attachedSpeed;
	float moveSpeed;
	Vector2 startPoint;
	Vector2 endPoint;
	bool hasDetached;
	int health;

public:
	KillerWhale(bool startAtTop = false)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/Wailord.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(150.f, 80.f);

		// Set start and end positions
		if (startAtTop) {
			startPoint = Vector2(RM->WINDOW_WIDTH + _transform->size.x, 0.f);
			endPoint = Vector2(-_transform->size.x, RM->WINDOW_HEIGHT - _transform->size.y);
		}
		else {
			startPoint = Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT - _transform->size.y);
			endPoint = Vector2(-_transform->size.x, 0.f);
		}

		_transform->position = startPoint;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		health = 100;
		currentState = STAY;
		hasDetached = false;

		attachedSpeed = 200.f;
		moveSpeed = 20.f;
	}

	void Update() override {
		switch (currentState) {
		case STAY:
			EnemyBehaviour();
			break;
		case SIMPLE_MOVE:
			Move();
			break;
		}

		Object::Update();
	}

	void EnemyBehaviour() override {
		// Move horizontally along the edge
		_physics->SetVelocity(Vector2(-attachedSpeed, 0.f));

		// Detach at screen center
		if (!hasDetached && _transform->position.x <= RM->WINDOW_WIDTH / 2.f) {
			currentState = SIMPLE_MOVE;
			hasDetached = true;
			std::cout << "Killer Whale se despego" << std::endl;
		}
	}

	void Move() override {
		// Move diagonally towards end point
		Vector2 direction = endPoint - _transform->position;
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		if (distance > 5.f) {
			// Normalize and apply speed
			direction.x /= distance;
			direction.y /= distance;

			_physics->SetVelocity(Vector2(direction.x * moveSpeed, direction.y * attachedSpeed));
		}
		else {
			// Reached end point
			Destroy();
			std::cout << "Killer Whale salio de la pantalla" << std::endl;
		}
	}
};