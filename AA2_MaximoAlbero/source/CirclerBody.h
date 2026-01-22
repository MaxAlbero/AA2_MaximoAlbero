#pragma once
#include "Enemy.h"
#include "FollowLeaderState.h"

class CirclerBody : public Enemy {
public:
	CirclerBody(Enemy* leaderEnemy, float distance = 120.f)
		: Enemy() {
		_renderer = new ImageRenderer(_transform, "resources/pinky.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(80.f, 80.f);

		if (leaderEnemy) {
			_transform->position = leaderEnemy->GetTransform()->position;
		}

		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		SetHealth(999999);
		SetPointsValue(0);

		// Crear estado de seguimiento y registrarlo
		auto* follow = new FollowLeaderState(_transform, leaderEnemy, distance);
		_stateManager->AddState(follow);
	}

	// No override Update: deja que Enemy::Update geste el state manager
};