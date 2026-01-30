#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include "TextObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "TimeManager.h"

class SplashScreen : public Scene {
private:
	float maxDisplayTime = 3.0f;
	float currentTime = 0.0f;

public:
	SplashScreen() = default;

	void OnEnter() override
	{
		TextObject* text = new TextObject("MENACE -1988- SDL");
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 5.0f, (float)RM->WINDOW_HEIGHT / 2.0f };
		text->GetTransform()->scale = Vector2(5.f, 5.f);
		_ui.push_back(text);
	}

	void Update() override {
		if (currentTime >= maxDisplayTime) {
			SM.SetNextScene("MainMenu");
		}
		else {
			currentTime += TM.GetDeltaTime();
		}
		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}
};