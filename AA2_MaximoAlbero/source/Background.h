#pragma once
#include "ImageObject.h"

class Background : public ImageObject {
public:
	Background()
		: ImageObject("resources/background.jpg", Vector2(0.f, 0.f), Vector2(680.f, 383.f)) {

		_transform->size = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT);
		_transform->position = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);
		_physics->SetVelocity(Vector2(-70.f, 0.f));
	}

	void Update() override {
		ScrollBG();

		Object::Update();
	}

	void ScrollBG() {
		if (_transform->position.x < -_transform->size.x / 2) {
			_transform->position.x = RM->WINDOW_WIDTH * 1.5f;
		}
	}
};