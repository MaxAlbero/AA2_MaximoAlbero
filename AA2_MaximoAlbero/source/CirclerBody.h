#pragma once
#include "Enemy.h"

class CirclerBody : public Enemy {
private:
	Enemy* leader;
	float offsetDistance;
	Vector2 lastLeaderPos;

public:
	CirclerBody(Enemy* leaderEnemy, float distance = 120.f)
		: Enemy(), leader(leaderEnemy), offsetDistance(distance) {
		_renderer = new ImageRenderer(_transform, "resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f));
		_transform->size = Vector2(80.f, 80.f);

		if (leader) {
			_transform->position = leader->GetTransform()->position;
			lastLeaderPos = _transform->position;
		}

		_physics->AddCollider(new AABB(_transform->position, _transform->size));
		enemyHealth = 999999;
		currentState = STAY;
	}

	void Update() override {
		if (leader == nullptr || leader->IsDestroyed()) {
			Destroy();
			return;
		}

		FollowLeader();
		Object::Update();
	}

	void FollowLeader() {
		Vector2 leaderPos = leader->GetTransform()->position;
		Vector2 currentPos = _transform->position;

		// Calcular dirección desde el cuerpo hacia el líder
		Vector2 toLeader = leaderPos - currentPos;
		float distance = sqrt(toLeader.x * toLeader.x + toLeader.y * toLeader.y);

		// Solo moverse si está más lejos que la distancia deseada
		if (distance > offsetDistance) {
			// Normalizar y calcular posición objetivo
			toLeader.x /= distance;
			toLeader.y /= distance;

			// Moverse hacia el líder manteniendo la distancia
			float moveAmount = distance - offsetDistance;
			_transform->position.x += toLeader.x * moveAmount;
			_transform->position.y += toLeader.y * moveAmount;
		}
	}

	void ReceiveDamage(int damageToAdd) override {
		// No recibe daño
	}

	void EnemyBehaviour() override {}
	void Move() override {}
	void CircleMove() override {}
	void GoAway() override {}
};