#pragma once
#include "EnemyMovement.h"
#include <random>
#include <cmath>

class RoboKrabsMovement : public EnemyMovement {
private:
	Transform* _playerTransform;
	Vector2 _attachPos;
	bool _attachToCeiling;
	float _jumpSpeed;
	float _returnSpeed;
	float _minDelay;
	float _maxDelay;
	float _timer;
	float _currentDelay;
	float _tolerance;

	enum Phase { WAITING, JUMPING, RETURNING } _phase;

	// RNG para retraso aleatorio
	std::mt19937 _rng;
	std::uniform_real_distribution<float> _dist;

	// target dinámico para salto/retorno
	Vector2 _currentTarget;

	static float DistanceSq(const Vector2& a, const Vector2& b) {
		float dx = a.x - b.x; float dy = a.y - b.y; return dx * dx + dy * dy;
	}

public:
	RoboKrabsMovement(Transform* transform, RigidBody* rigidBody,
		Transform* playerTransform,
		const Vector2& attachPos,
		bool attachToCeiling,
		float jumpSpeed = 600.f,
		float returnSpeed = 400.f,
		float minDelay = 3.f,
		float maxDelay = 5.f,
		float tolerance = 12.f)
		: EnemyMovement(transform, rigidBody),
		_playerTransform(playerTransform),
		_attachPos(attachPos),
		_attachToCeiling(attachToCeiling),
		_jumpSpeed(jumpSpeed),
		_returnSpeed(returnSpeed),
		_minDelay(minDelay),
		_maxDelay(maxDelay),
		_timer(0.f),
		_phase(WAITING),
		_rng(std::random_device{}()),
		_dist(minDelay, maxDelay),
		_currentTarget(attachPos),
		_tolerance(tolerance)
	{
		_currentDelay = _dist(_rng);
		if (_transform) _transform->position = _attachPos;
	}

	void Update(float deltaTime) override {
		if (!_transform) return;

		// si no hay player, permanecer pegado
		if (!_playerTransform) {
			_phase = WAITING;
			if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
			return;
		}

		switch (_phase) {
		case WAITING: {
			_timer += deltaTime;
			// permanecer pegado
			if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
			if (_timer >= _currentDelay) {
				_timer = 0.f;
				_currentDelay = _dist(_rng);
				_phase = JUMPING;
				_currentTarget = _playerTransform->position;
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _jumpSpeed);
					else _transform->position = _transform->position + dir * (_jumpSpeed * deltaTime);
				}
			}
			break;
		}
		case JUMPING: {
			float d2 = DistanceSq(_transform->position, _currentTarget);
			if (d2 <= _tolerance * _tolerance) {
				// detener
				if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
				_phase = RETURNING;
				_currentTarget = _attachPos;
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _returnSpeed);
					else _transform->position = _transform->position + dir * (_returnSpeed * deltaTime);
				}
			}
			else {
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _jumpSpeed);
				}
			}
			break;
		}
		case RETURNING: {
			float d2 = DistanceSq(_transform->position, _currentTarget);
			if (d2 <= _tolerance * _tolerance) {
				_transform->position = _attachPos;
				if (_rigidBody) _rigidBody->SetVelocity(Vector2(0.f, 0.f));
				_phase = WAITING;
				_timer = 0.f;
				_currentDelay = _dist(_rng);
			}
			else {
				Vector2 dir = _currentTarget - _transform->position;
				float dist = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (dist > 0.001f) {
					dir.x /= dist; dir.y /= dist;
					if (_rigidBody) _rigidBody->SetVelocity(dir * _returnSpeed);
				}
			}
			break;
		}
		}
	}
};