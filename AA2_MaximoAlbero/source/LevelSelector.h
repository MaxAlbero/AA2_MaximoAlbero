#pragma once
#include "Scene.h"
#include "Button.h"

class LevelSelector : public Scene  {
public:
	LevelSelector() = default;

	void OnEnter() override {
		TextObject* text = new TextObject("SELECT THE LEVEL YOU WANT TO PLAY");
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 3.f };
		_ui.push_back(text);


		//Level 1
		Button* button1 = new Button([]()
			{
				SM.SetNextScene("Gameplay");
			}
		);
		button1->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button1);

		//Level 2
		//TODO: ADD LEVEL 2 FIRST


		//Return to MainMenu
		Button* button3 = new Button([]()
			{
				SM.SetNextScene("MainMenu");
			}
		);
		button3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 5.0f, (float)RM->WINDOW_HEIGHT / 5.0f };
		_ui.push_back(button3);
	}

	void OnExit() override {
		Scene::OnExit();
	}

	void Update() override {
		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}
};