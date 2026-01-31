#pragma once
#include "SDL3/SDL.h"
#include <math.h>

#define TM TimeManager::Instance()

class TimeManager {
private:
	TimeManager() {
		_deltaTime = 0.0f;
		_elapsedTime = 0.0f;
		_previousElapsedTime = (double)SDL_GetTicks() / 1000.0f;

		_frameTime = 1.0f / (float)_FPS;
	}
	~TimeManager() = default;

	TimeManager(const TimeManager& t) = delete;
	TimeManager& operator=(const TimeManager& t) = delete;

	//Time Control
	float _deltaTime;
	float _elapsedTime;
	float _previousElapsedTime;

	//FPS Control
	const int _FPS = 60;
	float _frameTime;

public:
	static TimeManager& Instance() {
		static TimeManager instance;

		return instance;
	}

	float GetDeltaTime() const { return _deltaTime; }
	float GetElapsedTime() const { return _elapsedTime; }
	float GetFrameTime() const { return _frameTime; }
	bool ShouldUpdateGame() const { return _deltaTime >= _frameTime; }

	void ResetDeltaTime() {
		_deltaTime = _deltaTime - (float)(floor(_deltaTime / _frameTime) * _frameTime);
	}

	void Update() {
		_elapsedTime = (double)SDL_GetTicks() / 1000.0;
		_deltaTime += _elapsedTime - _previousElapsedTime;
		_previousElapsedTime = _elapsedTime;
	}
};