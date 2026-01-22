#pragma once
#include "EnemyState.h"
#include "Vector2.h"
#include "RigidBody.h"
#include "Transform.h"

class LinearMovementState : public EnemyState {
private:
	RigidBody* _rigidBody;
	Transform* _transform;
	Vector2 _start;
	Vector2 _finish;
	float _pixelsPerSec;
	float _elapsed;

public:
	LinearMovementState(Transform* transform, RigidBody* rigidBody,
		const Vector2& start, const Vector2& finish,
		float pixelsPerSec)
		: _rigidBody(rigidBody), _transform(transform), _start(start), _finish(finish),
		_pixelsPerSec(pixelsPerSec), _elapsed(0.f) {
		_transform->position = _start;
	}

	void Update(float deltaTime) override {
		_elapsed += deltaTime;

		Vector2 direction = _finish - _start;
		float distance = direction.Length();

		if (distance > 0.f) {
			direction.Normalize();
			_rigidBody->SetVelocity(direction * _pixelsPerSec);
		}

		Vector2 toFinish = _transform->position - _finish;
		float distToFinish = toFinish.Length();

		if (distToFinish < _pixelsPerSec * deltaTime) {
			_rigidBody->SetVelocity(Vector2(0.f, 0.f));
			_transform->position = _finish;
		}
	}

	bool IsFinished() const override {
		Vector2 toFinish = _transform->position - _finish;
		float distToFinish = toFinish.Length();
		return distToFinish < 5.f;
	}

	EnemyState* NextState() override {
		return nullptr; // El manager decide la transición
	}
};