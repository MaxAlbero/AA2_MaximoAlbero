#pragma once
#include "ImageObject.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "TimeManager.h"

enum MovementState {
	STAY,
	SIMPLE_MOVE,
	CIRCLE_MOVE,
	CHASE,
	SHOOT,
	RETURN
};

class Enemy : public ImageObject, public IAttacker, public IDamageable
{
protected:
	int enemyHealth = 50;
	float radius = 100.f;
	float angle = 0.f;
	float angularSpeed = 0.01f;
	MovementState currentState;
	bool isDestroyed = false;

public:
	Enemy()
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f))
	{
		_transform->size = Vector2(150.f, 150.f);
		//_transform->position = Vector2(RM->WINDOW_WIDTH / 1.f, RM->WINDOW_HEIGHT / 2.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		currentState = STAY;
	}

	virtual void Update() override {
		EnemyBehaviour();
		Object::Update();
	}

	void OnCollision(Object* other) override;
	virtual void EnemyBehaviour() {}
	virtual void Move() {}
	virtual void CircleMove();
	virtual void GoAway() {}

	//Interfaces para atacar y recibir daño
	virtual void Attack(IDamageable* other) const override;
	virtual void ReceiveDamage(int damageToAdd) override;

	bool IsDestroyed() const { return isDestroyed; }

	void Destroy() {
		isDestroyed = true;
		Object::Destroy();
	}
};

