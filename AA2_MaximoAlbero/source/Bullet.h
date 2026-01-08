#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class Bullet : public ImageObject
{
public:

	Bullet(Vector2 initPosition)
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(100.f, 100.f)) 
	{
		_transform->position = initPosition;
		_transform->scale = Vector2(0.5f, 0.15f);
		_physics->SetVelocity(Vector2(2000.f, 0.f));
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	void Update() override {
		SetLifeTime();
		Object::Update();
	}

	void SetLifeTime() {
		if (_transform->position.x > RM->WINDOW_WIDTH) {
			std::cout << "PEW PEW" << std::endl;
			Destroy();
		}
	}
	

	void OnCollision(Object* other) override;
};

