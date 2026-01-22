#pragma once
#include "EnemyState.h"
#include "TimeManager.h"

class IdleState : public EnemyState {
private:
	float _duration;
	float _elapsed;
	EnemyState* _nextState;

public:
	IdleState(float duration = 1.0f, EnemyState* nextState = nullptr)
		: _duration(duration), _elapsed(0.f), _nextState(nextState) {
	}

	void Update(float deltaTime) override {
		_elapsed += deltaTime;
	}

	bool IsFinished() const override {
		return _elapsed >= _duration;
	}

	EnemyState* NextState() override {
		return _nextState;
	}
};