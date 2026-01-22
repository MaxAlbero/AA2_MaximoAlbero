#pragma once
#include "EnemyState.h"
#include "Vector2.h"
#include "Transform.h"
#include <cmath>

class CircleMovementState : public EnemyState {
private:
	Transform* _transform;
	Vector2 _circleCenter;
	float _radius;
	float _degreesPerSec;
	float _angle;

public:
	CircleMovementState(Transform* transform, const Vector2& center,
		float radius, float degreesPerSec)
		: _transform(transform), _circleCenter(center), _radius(radius),
		_degreesPerSec(degreesPerSec), _angle(0.f) {
	}

	void Update(float deltaTime) override {
		const float PI = 3.14159265f;
		_angle += _degreesPerSec * deltaTime;

		float rad = _angle * PI / 180.f;
		_transform->position.x = _circleCenter.x + _radius * std::cos(rad);
		_transform->position.y = _circleCenter.y + _radius * std::sin(rad);
	}

	bool IsFinished() const override {
		return _angle >= 360.f;
	}

	EnemyState* NextState() override {
		return nullptr; // El manager decide
	}
};