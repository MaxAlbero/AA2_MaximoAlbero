#pragma once
#include "Enemy.h"
#include "EnemyBullet.h"
#include "LinearMovementState.h"
#include "ShootState.h"

class BioTitan : public Enemy {
private:
	float moveSpeed;
public:
	BioTitan()
		: Enemy(), moveSpeed(100.f) {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));

		_transform->size = Vector2(300.f, 300.f);
		_transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, RM->WINDOW_HEIGHT / 2.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		SetHealth(300);
		SetPointsValue(500);

		// Crear estados
		Vector2 startPos = _transform->position;
		Vector2 stopPos = Vector2(RM->WINDOW_WIDTH - _transform->size.x, _transform->position.y);

		auto* moveState = new LinearMovementState(_transform, _physics, startPos, stopPos, moveSpeed);
		auto* shootState = new ShootState(_transform, 0.5f, 5, -_transform->size.x / 2.f);

		// Añadir estados en orden - el manager gestiona la transición secuencial
		_stateManager->AddState(moveState);
		_stateManager->AddState(shootState);
	}
};