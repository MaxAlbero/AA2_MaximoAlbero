#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "CirclePartialMovement.h"
#include "DiagonalMovement.h"

enum BubbleDirection {
	TOP_TO_BOTTOM,
	BOTTOM_TO_TOP
};

class Bubbles : public Enemy {
private:
	float moveSpeed;
	float stopPointX;

	float circleRadius;
	float circleAngularVelDeg;
	float circleDegrees;

	BubbleDirection direction;

public:
	Bubbles(BubbleDirection dir, float offsetX = 0.f)
		: Enemy(), direction(dir) {

		_renderer = new ImageRenderer(_transform, "resources/pompa.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(100.f, 100.f);

		if (dir == TOP_TO_BOTTOM) {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT / 5.f);
		}
		else {
			_transform->position = Vector2(RM->WINDOW_WIDTH + offsetX, RM->WINDOW_HEIGHT * 4.f / 5.f);
		}

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		moveSpeed = 300.f;
		stopPointX = RM->WINDOW_WIDTH / 3.f;

		circleRadius = 60.f;
		circleAngularVelDeg = 120.f;
		circleDegrees = 300.f;

		float centerY;
		if (dir == TOP_TO_BOTTOM)
			centerY = RM->WINDOW_HEIGHT / 3.f;
		else
			centerY = RM->WINDOW_HEIGHT / 1.5f;

		movements.push_back(new LeftLinearMovement(_transform, _physics, stopPointX, moveSpeed));

		Vector2 circleCenter = Vector2(stopPointX, centerY);
		movements.push_back(new CirclePartialMovement(_transform, _physics, circleRadius, circleCenter, circleAngularVelDeg, circleDegrees));

		float directionY;
		if (dir == TOP_TO_BOTTOM)
			directionY = RM->WINDOW_HEIGHT / 1.5f;
		else
			directionY = RM->WINDOW_HEIGHT / 3.f;

		movements.push_back(new DiagonalMovement(_transform, _physics, directionY, moveSpeed, 1.f));
		movements.push_back(new RightLinearMovement(_transform, _physics, moveSpeed));

		SetHealth(20);
		SetPointsValue(100);
	}

	void Update() override {
		Enemy::Update();
	}
};