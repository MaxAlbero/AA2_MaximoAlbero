#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "IAttacker.h"

class Bullet : public ImageObject, public IAttacker
{
public:

	Bullet() //Bullet(Vector2 initPosition)
		: ImageObject("resources/BulletBill.png", Vector2(0.f, 0.f), Vector2(634.f, 394.f)) 
	{
		//_transform->position = initPosition;
		_transform->scale = Vector2(0.5f, 0.15f);
		_physics->SetVelocity(Vector2(2000.f, 0.f));
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	void Update() override {
		SetLifeTime();
		Object::Update();
	}

	virtual void SetLifeTime() {}
	

	void OnCollision(Object* other) override {}

	virtual void Attack(IDamageable* other) const override {}
};

