#include "Player.h"
#include "TimeManager.h"
#include "EnemyBullet.h"
#include "Enemy.h"

void Player::Move()
{
	float baseForce = 200.f * maxSpeed;

	if (IM->GetEvent(SDLK_S, KeyState::HOLD)) {
		_physics->AddForce(Vector2(0.f, baseForce));
		std::cout << "BaseForce: " << baseForce << std::endl;
	}
	if (IM->GetEvent(SDLK_W, KeyState::HOLD)) {
		_physics->AddForce(Vector2(0.f, -baseForce));
		std::cout << "BaseForce: " << baseForce << std::endl;
	}
	if (IM->GetEvent(SDLK_A, KeyState::HOLD)) {
		_physics->AddForce(Vector2(-baseForce, 0.f));
		std::cout << "BaseForce: " << baseForce << std::endl;
	}
	if (IM->GetEvent(SDLK_D, KeyState::HOLD)) {
		_physics->AddForce(Vector2(baseForce, 0.f));
		std::cout << "BaseForce: " << baseForce << std::endl;
	}

	if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN)) {
		Shoot();
	}
	else if (IM->GetLeftClick()) {
		Shoot();
	}
}

void Player::CheckBorders() {
	// Tamaño efectivo considerando scale
	float effectiveWidth = _transform->size.x * _transform->scale.x;
	float effectiveHeight = _transform->size.y * _transform->scale.y;

	if (_transform->position.x < effectiveWidth / 2)
		_transform->position.x = effectiveWidth / 2;

	if (_transform->position.x > RM->WINDOW_WIDTH - effectiveWidth / 2)
		_transform->position.x = RM->WINDOW_WIDTH - effectiveWidth / 2;

	if (_transform->position.y < effectiveHeight / 2)
		_transform->position.y = effectiveHeight / 2;

	if (_transform->position.y > RM->WINDOW_HEIGHT - effectiveHeight / 2)
		_transform->position.y = RM->WINDOW_HEIGHT - effectiveHeight / 2;
}

void Player::OnCollision(Object* other)
{
	// Solo recibir daño si no estoy inmune
	if (isImmune) return;

	if (EnemyBullet* bullet = dynamic_cast<EnemyBullet*>(other)) {
		if (!bullet->IsPendingDestroy()) {
			bullet->Destroy();
			ReceiveDamage(15);
			ActivateImmunity();
		}
	}
	// Colisión con enemigos
	else if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
		if (!enemy->IsPendingDestroy()) {
			ReceiveDamage(20);
			ActivateImmunity();
		}
	}
}

void Player::UpdateImmunity() {
	if (isImmune) {
		immunityTimer += TM.GetDeltaTime();

		if (immunityTimer >= immunityDuration) {
			isImmune = false;
			immunityTimer = 0.f;
			std::cout << "Immunity ended" << std::endl;
		}
	}
}

void Player::ActivateImmunity() {
	isImmune = true;
	immunityTimer = 0.f;
	std::cout << "Immunity activated!" << std::endl;
}

void Player::InmunityTime()
{
	do
	{
		ReceiveDamage(0);
		immunityTime += TM.GetDeltaTime();
	} while (immunityTime < maxImmunityTime);

	if (immunityTime >= maxImmunityTime) {
		immunityTime = 0.f;
	}
}