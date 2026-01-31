#pragma once
#include "AnimatedImageObject.h"

class TestAnimation : public AnimatedImageObject{
public:
	TestAnimation()
		: AnimatedImageObject("resources/frog.png", Vector2(0.f,0.f), Vector2(96.f, 128.f),
			12, 3, 32.f, 32.f, true) {
		Vector2 randomPosition = Vector2(rand() % RM->WINDOW_WIDTH, rand() & RM->WINDOW_HEIGHT);
		_transform->position = randomPosition;
		_transform->scale = Vector2(2.f, 2.f);
	}

	void Update() override {

		Object::Update();
	}
};