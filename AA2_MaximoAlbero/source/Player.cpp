#include "Player.h"
#include "TimeManager.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include "Enemy.h"
#include "EnemyBullet.h"

void Player::Move()
{
	float baseForce = 2000.f * maxSpeed;

	if (IM->GetEvent(SDLK_S, KeyState::HOLD)) {
		_physics->AddForce(Vector2(0.f, baseForce));
	}
	if (IM->GetEvent(SDLK_W, KeyState::HOLD)) {
		_physics->AddForce(Vector2(0.f, -baseForce));
	}
	if (IM->GetEvent(SDLK_A, KeyState::HOLD)) {
		_physics->AddForce(Vector2(-baseForce, 0.f));
	}
	if (IM->GetEvent(SDLK_D, KeyState::HOLD)) {
		_physics->AddForce(Vector2(baseForce, 0.f));
	}


	if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN)) {
		Shoot();
	}
	else if (IM->GetLeftClick()) {
		Shoot();
	}
}


void Player::CheckBorders() {
	if (_transform->position.x < _transform->size.x / 2)
		_transform->position.x = _transform->size.x / 2;

	if (_transform->position.x > RM->WINDOW_WIDTH - _transform->size.x / 2)
		_transform->position.x = RM->WINDOW_WIDTH - _transform->size.x / 2;

	if (_transform->position.y < _transform->size.y / 2)
		_transform->position.y = _transform->size.y / 2;

	if (_transform->position.y > RM->WINDOW_HEIGHT - _transform->size.y / 2)
		_transform->position.y = RM->WINDOW_HEIGHT - _transform->size.y / 2;
}

void Player::InmunityTime()
{
	do
	{
		ReceiveDamage(0);
		inmunityTime += TM.GetDeltaTime();
	} while (inmunityTime < maxInmunityTime);

	if (inmunityTime >= maxInmunityTime) {
		inmunityTime = 0.f;
	}
}

void Player::OnCollision(Object* other)
{
	if (EnemyBullet* bullet = dynamic_cast<EnemyBullet*>(other)) {
		bullet->Destroy();
		ReceiveDamage(10);
	}

	if (Enemy* enemy = dynamic_cast<Enemy*>(other)) {
		ReceiveDamage(20);
		InmunityTime();
	}

}
void Player::OnCollision(Object* other)
{
	// Solo recibir daño si no 
	if (isImmune) return;

	if (EnemyBullet* bullet = dynamic_cast<EnemyBullet*>(other)) {
		if (!bullet->IsPendingDestroy()) {
			bullet->Destroy();
			ReceiveDamage(15);
			ActivateImmunity();
		}
	}
	// Colision con enemigos
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
