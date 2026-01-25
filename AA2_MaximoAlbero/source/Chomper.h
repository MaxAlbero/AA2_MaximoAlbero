#pragma once
#include "Enemy.h"
#include "IdleMovement.h"
#include "ChomperMovement.h"

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
		_renderer = new ImageRenderer(_transform, "resources/bat.png", Vector2(0.f,0.f), Vector2(54.f, 36.f));

		_transform->size = Vector2(100.f, 100.f);
		_transform->scale = Vector2(2.f, 2.f);
		_transform->position = spawnPos;
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(20);
		SetPointsValue(100);

		movements.push_back(new IdleMovement(_transform, _physics, 1.5f)); // espera 1.5s
		movements.push_back(new ChomperMovement(_transform, _physics,
			_transform->position,   // centro inicial = posición de spawn
			20.f,                   // radius
			10.0f,                  // angularSpeed (rad/s)
			50.f,                   // horizontalShiftPerLoop
			0,                      // maxLoops = 0 => infinito
			0.f                     // startAngle si se desea
		));
	}
};