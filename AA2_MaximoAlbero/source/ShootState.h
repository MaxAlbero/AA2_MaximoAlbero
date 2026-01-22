#pragma once
#include "EnemyState.h"
#include "EnemyBullet.h"
#include "Spawner.h"
#include "Vector2.h"
#include <iostream>

class ShootState : public EnemyState {
private:
	Transform* _transform;
	float _cooldown;
	int _maxShots;
	int _shotsFired;
	float _timer;
	bool _finished;
	float _bulletOffsetX;

public:
	ShootState(Transform* transform, float cooldown = 0.5f, int maxShots = 5, float bulletOffsetX = -50.f)
		: _transform(transform), _cooldown(cooldown), _maxShots(maxShots),
		_shotsFired(0), _timer(0.f), _finished(false), _bulletOffsetX(bulletOffsetX) {
	}

	void Update(float deltaTime) override {
		if (_finished) return;

		_timer += deltaTime;
		if (_timer >= _cooldown) {
			_timer = 0.f;
			_shotsFired++;

			Vector2 bulletPos = Vector2(_transform->position.x + _bulletOffsetX, _transform->position.y);
			EnemyBullet* b = new EnemyBullet(bulletPos);
			SPAWNER.SpawnObject(b);

			if (_shotsFired >= _maxShots) {
				_finished = true;
			}
		}
	}

	bool IsFinished() const override {
		return _finished;
	}

	EnemyState* NextState() override {
		return nullptr; // El manager decide
	}
};