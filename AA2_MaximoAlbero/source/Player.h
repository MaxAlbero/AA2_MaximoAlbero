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

class Player : public ImageObject, public IAttacker, public IDamageable
{
private:
	int energy;
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
	ImageObject* _topTurret = nullptr;
	ImageObject* _bottomTurret = nullptr;

	Vector2 cannonOffset = Vector2(20.f, -30.f);
	Vector2 laserOffset = Vector2(20.f, 30.f);
	Vector2 topTurretOffset = Vector2(0.f, -50.f);
	Vector2 bottomTurretOffset = Vector2(0.f, 50.f);

	// Variables para rotación de torretas
	float topTurretRotation = 0.f;       // Rotación "internа" (se usa -topTurretRotation para el transform)
	float bottomTurretRotation = 0.f;    // Rotación interna (aplicada directamente al transform)
	float maxTurretRotation = 180.f;     // Máximo ángulo de rotación
	float turretRotationSpeed = 150.f;   // (no usado con el nuevo método, se conserva si quieres seguimiento por tiempo)
	Vector2 previousPosition;

	// Nuevo: acumulador de distancia en X para la regla "45º cada 100 unidades"
	float turretXAccumulator = 0.f;
	const float rotationPerStep = 45.f;      // grados por paso
	const float distancePerStep = 100.f;     // unidades X por paso

public:
	Player()
		: ImageObject("resources/caballo.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)) {

		_transform->position = Vector2(RM->WINDOW_WIDTH / 6.0f, RM->WINDOW_HEIGHT / 2.0f);
		_transform->scale = Vector2(0.5f, 0.5f);

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.1f);

		energy = 100;
		maxEnergy = 100;
		maxSpeed = 1.0f;

		_physics->AddCollider(new AABB(_transform->position, _transform->size));

		previousPosition = _transform->position;
	}

	~Player() {
		delete _cannon;
		delete _laser;
		delete _topTurret;
		delete _bottomTurret;
	}

	// Getters
	int GetEnergy() const { return energy; }
	int GetMaxEnergy() const { return maxEnergy; }
	float GetMaxSpeed() const { return maxSpeed; }
	int GetExtraLives() const { return extraLives; }
	bool HasCannon() const { return hasCannon; }
	int GetCannonAmmo() const { return cannonAmmo; }
	bool HasLaser() const { return hasLaser; }
	int GetLaserAmmo() const { return laserAmmo; }
	int GetNumOfTurrets() const { return numOfTurrets; }

	void Update() override {
		Move();
		CheckBorders();
		UpdateImmunity();
		UpdateTurretRotation();
		UpdateAttachments();

		previousPosition = _transform->position;
		Object::Update();
	}

	void Render() override {
		Object::Render();

		if (hasCannon && _cannon) {
			_cannon->Render();
		}
		if (hasLaser && _laser) {
			_laser->Render();
		}
		if (numOfTurrets >= 1 && _topTurret) {
			_topTurret->Render();
		}
		if (numOfTurrets >= 2 && _bottomTurret) {
			_bottomTurret->Render();
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

		if (numOfTurrets >= 1 && _topTurret) {
			_topTurret->GetTransform()->position = _transform->position + topTurretOffset;
			_topTurret->GetTransform()->rotation = -topTurretRotation;  // Negativo = rota hacia arriba
			_topTurret->Update();
		}

		if (numOfTurrets >= 2 && _bottomTurret) {
			_bottomTurret->GetTransform()->position = _transform->position + bottomTurretOffset;
			_bottomTurret->GetTransform()->rotation = bottomTurretRotation;  // Positivo = rota hacia abajo
			_bottomTurret->Update();
		}
	}

	// Nueva lógica: 45º por cada 100 unidades recorridas en X.
	void UpdateTurretRotation() {
		if (numOfTurrets == 0) return;

		// Delta X recorrido desde el frame anterior
		float deltaX = _transform->position.x - previousPosition.x;
		if (deltaX == 0.f) return;

		// Acumula el desplazamiento en X
		turretXAccumulator += deltaX;

		// Si alcanzamos uno o más "pasos" de distancePerStep, aplicamos rotación por pasos
		while (std::abs(turretXAccumulator) >= distancePerStep) {
			int stepSign = (turretXAccumulator > 0.f) ? 1 : -1;
			// Aplicar cambio de ángulo: +45º por paso si se mueve a la derecha (signo positivo),
			// -45º por paso si se mueve a la izquierda (signo negativo).
			float deltaAngle = rotationPerStep * static_cast<float>(stepSign); 

			// Incrementar rotaciones internas (se usan signos al renderizar)
			topTurretRotation += deltaAngle;
			bottomTurretRotation += deltaAngle;

			// Limitar entre 0 y maxTurretRotation (como en tu diseño original)
			if (topTurretRotation > maxTurretRotation) topTurretRotation = maxTurretRotation;
			if (topTurretRotation < 0.f) topTurretRotation = 0.f;
			if (bottomTurretRotation > maxTurretRotation) bottomTurretRotation = maxTurretRotation;
			if (bottomTurretRotation < 0.f) bottomTurretRotation = 0.f;

			// Quitar el paso aplicado del acumulador (mantener resto)
			turretXAccumulator -= static_cast<float>(stepSign) * distancePerStep;
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

	// PowerUps
	void AddCannon() {
		if (!hasCannon) {
			hasCannon = true;
			_cannon = new ImageObject(
				"resources/BillBuster.png",
				Vector2(0.f, 0.f),
				Vector2(100.f, 50.f)
			);
			_cannon->GetTransform()->scale = Vector2(0.4f, 0.4f);
			std::cout << "Cannon equipped!" << std::endl;
		}
		else {
			cannonAmmo = maxAmmo;
			std::cout << "Cannon ammo refilled!" << std::endl;
		}
	}

	void AddLaser() {
		if (!hasLaser) {
			hasLaser = true;
			_laser = new ImageObject(
				"resources/image.png",
				Vector2(0.f, 0.f),
				Vector2(120.f, 40.f)
			);
			_laser->GetTransform()->scale = Vector2(0.35f, 0.35f);
			std::cout << "Laser equipped!" << std::endl;
		}
		else {
			laserAmmo = maxAmmo;
			std::cout << "Laser ammo refilled!" << std::endl;
		}
	}

	void IncreaseSpeed() {
		maxSpeed += 0.5f;
		std::cout << "Speed increased! New speed: " << maxSpeed << std::endl;
	}

	void AddTwinTurrets() {
		if (numOfTurrets == 0) {
			_topTurret = new ImageObject(
				"resources/turret.png",
				Vector2(0.f, 0.f),
				Vector2(482.f, 180.f)
			);
			_topTurret->GetTransform()->scale = Vector2(0.5f, 0.5f);
			numOfTurrets = 1;
			std::cout << "Top turret equipped!" << std::endl;
		}
		else if (numOfTurrets == 1) {
			_bottomTurret = new ImageObject(
				"resources/turret.png",
				Vector2(0.f, 0.f),
				Vector2(482.f, 180.f) 
			);
			_bottomTurret->GetTransform()->scale = Vector2(0.5f, 0.5f);
			numOfTurrets = 2;
			std::cout << "Bottom turret equipped!" << std::endl;
		}
		else {
			std::cout << "Already have both turrets!" << std::endl;
		}
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

	void Shoot() {
		// Disparo principal
		Vector2 bulletOffset = Vector2(_transform->size.x * 0.5f, 0.f);
		SPAWNER.SpawnObject(new PlayerBullet(_transform->position + bulletOffset));

		// Disparo del cañón
		if (hasCannon && cannonAmmo > 0 && _cannon) {
			Vector2 cannonPos = _cannon->GetTransform()->position;
			Vector2 cannonBulletOffset = Vector2(_cannon->GetTransform()->size.x * 0.5f, 0.f);
			SPAWNER.SpawnObject(new PlayerBullet(cannonPos + cannonBulletOffset));
			cannonAmmo--;
		}

		// Disparo del láser
		if (hasLaser && laserAmmo > 0 && _laser) {
			Vector2 laserPos = _laser->GetTransform()->position;
			Vector2 laserBulletOffset = Vector2(_laser->GetTransform()->size.x * 0.5f, 0.f);
			SPAWNER.SpawnObject(new PlayerBullet(laserPos + laserBulletOffset));
			laserAmmo--;
		}

		const float PI = 3.14159265f;

		// Disparo de torreta superior
		if (numOfTurrets >= 1 && _topTurret) {
			Vector2 topTurretPos = _topTurret->GetTransform()->position;
			float angleDeg = _topTurret->GetTransform()->rotation; // en grados
			float rad = angleDeg * PI / 180.0f;

			// Calcula la distancia hasta la punta de la torreta considerando la escala
			float tipDistance = _topTurret->GetTransform()->size.x * 0.5f * _topTurret->GetTransform()->scale.x;

			// Offset rotado: (cos(rad)*dx, sin(rad)*dx) porque el offset original era (dx,0)
			Vector2 topBulletOffset = Vector2(std::cos(rad) * tipDistance, std::sin(rad) * tipDistance);

			SPAWNER.SpawnObject(new PlayerBullet(topTurretPos + topBulletOffset, angleDeg));
		}

		// Disparo de torreta inferior
		if (numOfTurrets >= 2 && _bottomTurret) {
			Vector2 bottomTurretPos = _bottomTurret->GetTransform()->position;
			float angleDeg = _bottomTurret->GetTransform()->rotation; // en grados
			float rad = angleDeg * PI / 180.0f;

			float tipDistance = _bottomTurret->GetTransform()->size.x * 0.5f * _bottomTurret->GetTransform()->scale.x;
			Vector2 bottomBulletOffset = Vector2(std::cos(rad) * tipDistance, std::sin(rad) * tipDistance);

			SPAWNER.SpawnObject(new PlayerBullet(bottomTurretPos + bottomBulletOffset, angleDeg));
		}
	}
};