#pragma once
#include "EnemyState.h"
#include "Vector2.h"
#include <cmath>

class Enemy;

class FollowLeaderState : public EnemyState {
private:
	Transform* _transform;
	Enemy* _leader;
	float _offsetDistance;
	bool _finished;

public:
	FollowLeaderState(Transform* transform, Enemy* leader, float offsetDistance = 120.f)
		: _transform(transform), _leader(leader), _offsetDistance(offsetDistance),
		_finished(false) {
	}

	void Update(float deltaTime) override {
		if (!_leader || _leader->IsPendingDestroy()) {
			_finished = true;
			return;
		}

		Vector2 leaderPos = _leader->GetTransform()->position;
		Vector2 currentPos = _transform->position;

		Vector2 toLeader = leaderPos - currentPos;
		float distance = toLeader.Length();

		if (distance > _offsetDistance) {
			toLeader.Normalize();
			float moveAmount = distance - _offsetDistance;
			_transform->position += toLeader * moveAmount;
		}
	}

	bool IsFinished() const override {
		return _finished;
	}

	EnemyState* NextState() override {
		return nullptr; // El manager decide
	}
};