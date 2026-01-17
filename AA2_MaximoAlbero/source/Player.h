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
	int extraLives = 3;

	bool hasCannon = false;
	int cannonAmmo = 0;
	bool hasLaser = false;
	int laserAmmo = 0;
	int maxAmmo = 10;
	int numOfTurrets = 0;

	bool isImmune = false;
	float immunityTimer = 0.f;
	float immunityDuration = 1.0f;
	float maxInmunityTime = 0.5f;
	float inmunityTime = 0.f;

	ImageObject* _cannon = nullptr;
	ImageObject* _laser = nullptr;

	Vector2 cannonOffset = Vector2(20.f, -30.f);
	Vector2 laserOffset = Vector2(20.f, 30.f);

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

	~Player() {
		delete _cannon;
		delete _laser;
	}

	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }

	int GetExtraLives() const { return extraLives; }
	bool HasCannon() const { return hasCannon; }
	int GetCannonAmmo() const { return cannonAmmo; }
	bool HasLaser() const { return hasLaser; }
	int GetLaserAmmo() const { return laserAmmo; }


	void Update() override {
		Move();
		CheckBorders();
		UpdateImmunity();
		UpdateAttachments();
		Object::Update();
	}

	void Render() override {
		Object::Render();  // Renderizar nave primero

		// Renderizar attachments si existen
		if (hasCannon && _cannon) {
			_cannon->Render();
		}
		if (hasLaser && _laser) {
			_laser->Render();
		}
	}

	void UpdateAttachments() {
		if (hasCannon && _cannon) {
			_cannon->GetTransform()->position = _transform->position + cannonOffset;
			_cannon->Update();
		}

		if (hasLaser && _laser) {
			_laser->GetTransform()->position = _transform->position + laserOffset;
			_laser->Update();
		}
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
			// Crear ImageObject para el cañón
			_cannon = new ImageObject(
				"resources/BillBuster.png",
				Vector2(0.f, 0.f),
				Vector2(100.f, 50.f)  // Tamaño de la textura del cañón
			);

			// Configurar transform del cañón
			_cannon->GetTransform()->position = _transform->position + cannonOffset;
			_cannon->GetTransform()->scale = Vector2(0.4f, 0.4f);  // Escalar si es necesario

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

			_laser = new ImageObject(
				"resources/image.png",
				Vector2(0.f, 0.f),
				Vector2(120.f, 40.f)  // Tamaño de la textura del láser
			);

			// Configurar transform del láser
			_laser->GetTransform()->position = _transform->position + laserOffset;
			_laser->GetTransform()->scale = Vector2(0.35f, 0.35f);
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

	void ReceiveDamage(int damageToAdd) override {
		energy -= damageToAdd;
		std::cout << "Player received " << damageToAdd << " damage. Energy left: " << energy << std::endl;

		if (energy <= 0) {
			Destroy();
			std::cout << "Player Dead!" << std::endl;
		}
	}

	void Shoot() {
		Vector2 bulletOffset = Vector2(_transform->size.x * 0.5f, 0.f);
		SPAWNER.SpawnObject(new PlayerBullet(_transform->position + bulletOffset));

		if (hasCannon && cannonAmmo > 0 && _cannon) {
			Vector2 cannonPos = _cannon->GetTransform()->position;
			SPAWNER.SpawnObject(new PlayerBullet(cannonPos));
			cannonAmmo--;
		}

		if (hasLaser && laserAmmo > 0 && _laser) {
			Vector2 laserPos = _laser->GetTransform()->position;
			SPAWNER.SpawnObject(new PlayerBullet(laserPos));
			laserAmmo--;
		}
	}
};