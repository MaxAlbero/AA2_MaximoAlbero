#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "IAttacker.h"
#include "AudioManager.h"

class Bullet : public ImageObject, public IAttacker
{
public:

	Bullet()
		: ImageObject("resources/BulletBill.png", Vector2(0.f, 0.f), Vector2(634.f, 394.f)) 
	{

		_transform->scale = Vector2(0.5f, 0.15f);
		_physics->SetVelocity(Vector2(2000.f, 0.f));
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	void Update() override {
		Object::Update();
	}

	void OnCollision(Object* other) override {
		AM->PlaySound("resources/audio/sfx/hit_wall.wav");
	}

	virtual void Attack(IDamageable* other) const override {}
};

