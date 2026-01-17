#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "TimeManager.h"

class Player : public ImageObject, public IAttacker, public IDamageable
{
private:
	int energy; //shields/shieldsPower... values from 0 to 100
	int maxEnergy;
	float maxSpeed;

	bool hasCannon = false;
	int cannonAmmo = 0;
	bool hasLaser = false;
	int laserAmmo = 0;
	int maxAmmo = 100;
	int numOfTurrets = 0;

	bool isImmune = false;
	float immunityTimer = 0.f;
	float immunityDuration = 1.0f;
	float maxInmunityTime = 0.5f;
	float inmunityTime = 0.f;

public:
	Player()
		: ImageObject("resources/caballo.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		// Posici� random en tota la finestra
		//Vector2 randomPosition = Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);

		_transform->position = Vector2(RM->WINDOW_WIDTH / 6.0f, RM->WINDOW_HEIGHT / 2.0f);
		_transform->scale = Vector2(0.5f, 0.5f);

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.1f);

		energy = 100;
		maxEnergy = 100;
		maxSpeed = 1.0f;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		std::cout << "Current energy: " << energy << std::endl;
	}

	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }

	void Update() override {
		Move();
		CheckBorders();
		UpdateImmunity();
		Object::Update();
	}

	void UpdateImmunity();

	void ActivateImmunity();

	void SetEnergy(int newEnergy) {
		energy = newEnergy;
		if (energy > maxEnergy) energy = maxEnergy;
		if (energy < 0) energy = 0;
	}

	void SetMaxSpeed(float newMaxSpeed) {
		maxSpeed = newMaxSpeed;
	}


	void Move();
	void Shoot() {
		//Bullet* bullet = new Bullet();

		SPAWNER.SpawnObject(new PlayerBullet(Vector2(_transform->position.x + 1, _transform->position.y)));
	}
	void CheckBorders();

	void InmunityTime();

	void OnCollision(Object* other) override;
	
	//PowerUps (the only powerUp that shouldn't be here in theory is the 1000 extra score points because it's the ScoreManager the one that manages it
	
	//2
	void AddCannon() {
		//PSEUDOCODE: Primero comprobar si el jugador tiene el ca�on equipado (sino lo tiene, se le a�ade pero esta vacio, si lo tiene se rellena la ammo)
		// al coger el powerup una vez, se a�ade el ca�on a la parte superior (o puede que inferior) del player
		// despu�s, cada vez que coges el powerUp, la ammo del ca�on se rellena completamente
		if (!hasCannon) {
			//NEED TO ADD CANNON HERE
			hasCannon = true;
			std::cout << "Cannon equipped!" << std::endl;
		}
		else {
			cannonAmmo = maxAmmo;
		}
	}
	//3
	void AddLaser() {  
		//PSEUDOCODE: Primero comprobar si el jugador tiene el laser equipado (sino lo tiene, se le a�ade pero esta vacio, si lo tiene se rellena la ammo)
		// al coger el powerup una vez, se a�ade el laser a la parte superior (o puede que inferior) del player
		// despues, cada vez que coges el powerUp, la ammo del ca�on se rellena completamente
		if (!hasLaser) {
			//NEED TO ADD LASER GUN HERE
			hasLaser = true;
		}
		else {
			laserAmmo = maxAmmo;
		}
	}

	//4
	void IncreaseSpeed() {
		float multiplier = 0.5f;

		maxSpeed += multiplier;
		std::cout << "Speed increased! New multiplier: " << maxSpeed << std::endl;
	}

	//5
	void AddTwinTurrets() {
		//PSEUDOCODE: Primero comprobar la cantidad de torretas que estan activas (empiezas con 0), 
		// al coger el powerup una vez, se a�ade 1, al hacerlo la segunda vez, se a�ade la segunda
		// despues en principio no pasa nada al coger este powerUp

	}
	//6
	void RestoreFullEnergy() {
		energy = maxEnergy;
		std::cout << "Energy fully restored! Current energy: " << energy << std::endl;
	}

	//Interfaces para atacar y recibir da�o
	void Attack(IDamageable* other) const override {}

	//Interfaces para atacar y recibir da�o
	void Attack(IDamageable* other) const override {}
	void ReceiveDamage(int damageToAdd) override {
		energy -= damageToAdd;
		std::cout << "Player received " << damageToAdd << " damage. Energy left: " << energy << std::endl;

		if (energy <= 0) {
			Destroy();
			std::cout << "Player Dead!" << std::endl;
		}
	}

	void OnCollision(Object* other) override;

};