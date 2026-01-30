#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "TimeManager.h"
#include <cmath>
#include "WeaponManager.h"

class Player : public ImageObject, public IAttacker, public IDamageable
{
private:
	int energy;
	int maxEnergy;
	float maxSpeed;
	int extraLives;

	bool isImmune;
	float immunityTimer;
	float immunityDuration;

	float immunityTime = 0.f;
	float maxImmunityTime = 0.5f;

	WeaponManager* _weaponManager;

	Vector2 _initialPosition;

public:
	Player() : ImageObject("resources/caballo.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {
		_initialPosition = Vector2(RM->WINDOW_WIDTH / 6.0f, RM->WINDOW_HEIGHT / 2.0f);
		_transform->position = _initialPosition;
		_transform->scale = Vector2(0.5f, 0.5f);

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.1f);

		energy = 100;
		maxEnergy = 100;
		maxSpeed = 1.0f;
		extraLives = 3;
		isImmune = false;
		immunityTimer = 0.f;
		immunityDuration = 1.0f;

		_weaponManager = new WeaponManager();

		_physics->AddCollider(new AABB(_transform->position, _transform->size));
	}

	~Player() {
		delete _weaponManager;
	}

	void Update() override {
		Move();
		CheckBorders();
		UpdateImmunity();
		_weaponManager->Update(_transform->position); // Delegar responsabilidad
		Object::Update();
	}

	void Render() override {
		Object::Render();
		_weaponManager->Render(); // Delegar responsabilidad
	}

	void Shoot() {
		// Disparo principal
		Vector2 bulletOffset = Vector2(_transform->size.x * 0.5f, 0.f);
		SPAWNER.SpawnObject(new PlayerBullet(_transform->position + bulletOffset));

		// Delegar a WeaponManager
		_weaponManager->ShootAll(_transform->position);
	}

	//Getters delegados a WeaponManager
	bool HasCannon() const { return _weaponManager->HasCannon(); }
	int GetCannonAmmo() const { return _weaponManager->GetCannonAmmo(); }
	bool HasLaser() const { return _weaponManager->HasLaser(); }
	int GetLaserAmmo() const { return _weaponManager->GetLaserAmmo(); }
	int GetNumOfTurrets() const { return _weaponManager->GetNumOfTurrets(); }

	// Getters
	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }
	int GetExtraLives() const { return extraLives; }

	void SetEnergy(int newEnergy) {
		energy = newEnergy;
		if (energy > maxEnergy) energy = maxEnergy;
		if (energy < 0) energy = 0;
	}

	void SetExtraLives(int newLives) {  // NUEVO
		extraLives = newLives;
		if (extraLives < 0) extraLives = 0;
	}

	void UpdateImmunity();
	void ActivateImmunity();

	void SetMaxSpeed(float newMaxSpeed) {
		maxSpeed = newMaxSpeed;
	}

	void Move();
	void CheckBorders();
	void InmunityTime();
	void OnCollision(Object* other) override;

	//PowerUps delegados a WeaponManager
	void AddCannon() { _weaponManager->AddCannon(); }
	void AddLaser() { _weaponManager->AddLaser(); }
	void AddTwinTurrets() { _weaponManager->AddTurret(); }


	//PowerUps
	void IncreaseSpeed() {
		maxSpeed += 0.5f;
		std::cout << "Speed increased! New speed: " << maxSpeed << std::endl;
	}

	void RestoreFullEnergy() {
		energy = maxEnergy;
		std::cout << "Energy fully restored! Current energy: " << energy << std::endl;
	}

	// Interfaces
	void Attack(IDamageable* other) const override {}

	void ReceiveDamage(int damageToAdd) override {
		energy -= damageToAdd;
		std::cout << "Player received " << damageToAdd << " damage. Energy left: " << energy << std::endl;

		if (energy <= 0) {
			Destroy();
			std::cout << "Player Dead!" << std::endl;
		}
	}

	void ResetPosition() {
		if (!_transform) {
			std::cout << "Error: Transform is null! Cannot reset position." << std::endl;
			return;
		}

		if (!_physics) {
			std::cout << "Error: Physics is null! Cannot reset position." << std::endl;
			return;
		}

		_transform->position = _initialPosition;
		_physics->SetVelocity(Vector2(0.f, 0.f));
		isImmune = false;
		immunityTimer = 0.f;
		std::cout << "Player position reset to initial position ("
			<< _initialPosition.x << ", " << _initialPosition.y << ")" << std::endl;
	}
};