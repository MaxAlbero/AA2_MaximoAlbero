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

	bool hasCannon = false;
	int cannonAmmo = 0;
	bool hasLaser = false;
	int laserAmmo = 0;
	int maxAmmo = 100;
	int numOfTurrets = 0;

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

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		std::cout << "Current energy: " << energy << std::endl;
	}

	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }

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


	void Move();
	void Shoot() {
		//Bullet* bullet = new Bullet();

		SPAWNER.SpawnObject(new Bullet(Vector2(_transform->position.x + 1, _transform->position.y)));
	}
	void CheckBorders();
	
	//PowerUps (the only powerUp that shouldn't be here in theory is the 1000 extra score points because it's the ScoreManager the one that manages it
	
	//2
	void AddCannon() {
		//PSEUDOCODE: Primero comprobar si el jugador tiene el cañon equipado (sino lo tiene, se le añade pero esta vacio, si lo tiene se rellena la ammo)
		// al coger el powerup una vez, se añade el cañon a la parte superior (o puede que inferior) del player
		// después, cada vez que coges el powerUp, la ammo del cañon se rellena completamente
		if (!hasCannon) {
			//NEED TO ADD CANNON HERE
		}
		else {
			cannonAmmo = maxAmmo;
		}
	}
	//3
	void AddLaser() {  
		//PSEUDOCODE: Primero comprobar si el jugador tiene el laser equipado (sino lo tiene, se le añade pero esta vacio, si lo tiene se rellena la ammo)
		// al coger el powerup una vez, se añade el laser a la parte superior (o puede que inferior) del player
		// después, cada vez que coges el powerUp, la ammo del cañon se rellena completamente
		if (!hasLaser) {
			//NEED TO ADD CANNON HERE
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
		// al coger el powerup una vez, se añade 1, al hacerlo la segunda vez, se añade la segunda
		// después en principio no pasa nada al coger este powerUp

	}
	//6
	void RestoreFullEnergy() {
		energy = maxEnergy;
		std::cout << "Energy fully restored! Current energy: " << energy << std::endl;
	}

	//Interfaces para atacar y recibir daño
	virtual void Attack(IDamageable* other) const override {}
	virtual void ReceiveDamage(int damageToAdd) override {}

};