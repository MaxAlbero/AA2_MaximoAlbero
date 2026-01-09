#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "Bullet.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"

class Player : public ImageObject, public IAttacker, public IDamageable
{
private:
	int energy; //shields/shieldsPower... values from 0 to 100
	int maxEnergy;
	float maxSpeed;
	float currentSpeedMultiplier;

public:
	Player()
		: ImageObject("resources/caballo.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		// Posició random en tota la finestra
		//Vector2 randomPosition = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);

		_transform->position = Vector2(RM->WINDOW_WIDTH / 6.0f, RM->WINDOW_HEIGHT / 2.0f);
		_transform->scale = Vector2(0.5f, 0.5f);
		//_transform->rotation = 30.f;

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.1f);

		energy = 30;
		maxEnergy = 100;
		maxSpeed = 1.0f;
		currentSpeedMultiplier = 1.0f;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		std::cout << "Current energy: " << energy << std::endl;
	}

	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }
	float GetSpeedMultiplier() const { return currentSpeedMultiplier; }

	void Update() override {

		Move();

		CheckBorders();

		Object::Update();
	}

	void SetEnergy(int newEnergy) {
		energy = newEnergy;
		if (energy > maxEnergy) energy = maxEnergy;
		if (energy < 0) energy = 0;
	}

	void SetMaxSpeed(float newMaxSpeed) {
		maxSpeed = newMaxSpeed;
	}

	void IncreaseSpeed() {
		float multiplier = 0.5f;

		currentSpeedMultiplier += multiplier;
		std::cout << "Speed increased! New multiplier: " << currentSpeedMultiplier << std::endl;
	}

	void RestoreFullEnergy() {
		energy = maxEnergy;
		std::cout << "Energy fully restored! Current energy: " << energy << std::endl;
	}

	void Move();

	void Shoot() {
		//Bullet* bullet = new Bullet();

		SPAWNER.SpawnObject(new Bullet(Vector2(_transform->position.x + 1, _transform->position.y)));
	}

	void CheckBorders();

	//Interfaces para atacar y recibir daño
	virtual void Attack(IDamageable* other) const override {}
	virtual void ReceiveDamage(int damageToAdd) override {}

};