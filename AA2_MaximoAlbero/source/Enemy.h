#pragma once
#include "ImageObject.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "EnemyStateManager.h"
#include "ScoreManager.h"
//#include "Explosion.h"

class Enemy : public ImageObject, public IAttacker, public IDamageable
{
protected:
	int enemyHealth;
	int pointsValue;
	EnemyStateManager* _stateManager;

public:
	Enemy()
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)),
		  enemyHealth(50), pointsValue(200) {
		_transform->size = Vector2(150.f, 150.f);
		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		_stateManager = new EnemyStateManager(_transform);
	}

	~Enemy() {
		delete _stateManager;
	}

	virtual void Update() override {
		if (_stateManager) {
			_stateManager->Update(0.02f); // 50 FPS
		}
		Object::Update();
	}

	void OnCollision(Object* other) override;

	virtual void Attack(IDamageable* other) const override;
	virtual void ReceiveDamage(int damageToAdd) override {
		enemyHealth -= damageToAdd;
		if (enemyHealth <= 0) {
			Destroy();
		}
	}

	void Destroy() override {
		//SPAWNER.SpawnObject(new Explosion(_transform->position));
		HSM->AddPoints(pointsValue);
		Object::Destroy();
	}

	EnemyStateManager* GetStateManager() { return _stateManager; }
	int GetHealth() const { return enemyHealth; }
	void SetHealth(int hp) { enemyHealth = hp; }
	void SetPointsValue(int points) { pointsValue = points; }
};

