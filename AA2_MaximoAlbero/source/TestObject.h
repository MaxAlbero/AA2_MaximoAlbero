#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "Bullet.h"


class TestObject : public ImageObject
{
public:
	TestObject()
		: ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f))
	{
		// Posició random en tota la finestra
		Vector2 randomPosition = Vector2(0.f, 0.f);    // Vector2(rand() % RM->WINDOW_WIDTH, rand() % RM->WINDOW_HEIGHT);
		_transform->position = randomPosition;
		_transform->scale = Vector2(0.5f, 0.5f);
		_transform->rotation = 30.f;

		_physics->SetLinearDrag(10.f);
		_physics->SetAngularDrag(0.1f);
	}

	void Update() override {
		if (IM->GetEvent(SDLK_S, KeyState::DOWN)) {
			_physics->AddForce(Vector2(0.f, 20.f));
		}
		if (IM->GetEvent(SDLK_W, KeyState::DOWN)) {
			_physics->AddForce(Vector2(0.f, -20.f));
		}
		if (IM->GetEvent(SDLK_A, KeyState::DOWN)) {
			_physics->AddForce(Vector2(-20.f, 0.f));
		}
		if (IM->GetEvent(SDLK_D, KeyState::DOWN)) {
			_physics->AddForce(Vector2(20.f, 0.f));
		}
		if (IM->GetEvent(SDLK_R, KeyState::DOWN)) {
			_physics->AddTorque(200.f);
		}
		if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN)) {
			Shoot();
		}

		Object::Update();
	}


	void Shoot() {
		Bullet* bullet = new Bullet(Vector2(_transform->position.x + 1, _transform->position.y));
		SPAWNER.SpawnObject(bullet);
	}
};