#pragma once
#include "ImageObject.h"
#include "TimeManager.h"

class Explosion : public ImageObject {
private:
	float maxDurationTime = 2.f;
	float durationTime = 0.f;

public:
	// Constructor por defecto (mantener compatibilidad)
	Explosion()
		: ImageObject("resources/explosion.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f)) {
		_transform->scale = Vector2(0.5f, 0.5f);
	}

	// Nuevo constructor que coloca la explosion en una posición dada
	Explosion(const Vector2& position)
		: ImageObject("resources/explosion.png", Vector2(0.f, 0.f), Vector2(500.f, 500.f)) {
		_transform->scale = Vector2(0.5f, 0.5f);
		_transform->position = position;
	}

	void Update() override {
		if (durationTime >= maxDurationTime) {
			Destroy();
		}
		else {
			durationTime += TM.GetDeltaTime();
		}
		Object::Update();
	}

	void Render() override {
		Object::Render();
	}
};