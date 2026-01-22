#pragma once
#include "Enemy.h"
#include "CircleMovementState.h"
#include "LinearMovementState.h"

enum BubbleDirection {
	TOP_TO_BOTTOM,
	BOTTOM_TO_TOP
};

class Bubbles : public Enemy {
private:
	BubbleDirection _direction;
	float _moveSpeed;
	float _stopPointX;

public:
	Bubbles(BubbleDirection dir, float offsetX = 0.f) : Enemy(), _direction(dir), _moveSpeed(100.f) {
		_renderer = new ImageRenderer(_transform, "resources/pompa.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(100.f, 100.f);

		if (dir == TOP_TO_BOTTOM) {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT / 5.f);
		}
		else {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT * 4.f / 5.f);
		}

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		_stopPointX = RM->WINDOW_WIDTH / 3.f;
		enemyHealth = 20;
		pointsValue = 200;

		InitializeStates(dir);
	}

private:
	void InitializeStates(BubbleDirection dir) {
		Vector2 stopPos(_stopPointX, _transform->position.y);
		Vector2 circleCenter = (dir == TOP_TO_BOTTOM)
			? Vector2(_stopPointX, RM->WINDOW_HEIGHT / 1.5f)
			: Vector2(_stopPointX, RM->WINDOW_HEIGHT / 3.f);

		// Crear estados
		auto* linearState = new LinearMovementState(_transform, _physics, _transform->position, stopPos, _moveSpeed);
		auto* circleState = new CircleMovementState(_transform, circleCenter, 100.f, 90.f);
		auto* exitState = new LinearMovementState(_transform, _physics, circleCenter, Vector2(RM->WINDOW_WIDTH + 200.f, circleCenter.y), _moveSpeed);

		// Añadir en orden - transición secuencial automática
		_stateManager->AddState(linearState);
		_stateManager->AddState(circleState);
		_stateManager->AddState(exitState);
	}
};