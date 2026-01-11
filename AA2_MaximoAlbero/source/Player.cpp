#include "Player.h"

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