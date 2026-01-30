#pragma once
#include "Scene.h"
#include "Button.h"

class LevelSelector : public Scene {
public:
	LevelSelector() = default;

	void OnEnter() override {
		TextObject* text = new TextObject("SELECT THE LEVEL YOU WANT TO PLAY");
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.5f, (float)RM->WINDOW_HEIGHT / 3.2f };
		_ui.push_back(text);

		//Level 1
		Button* button1 = new Button([]()
			{
				SM.SetNextScene("Gameplay");
			}
		);
		button1->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 2.7f };
		_ui.push_back(button1);

		TextObject* text1 = new TextObject("LEVEL 1 - SEA OF KARNAUGH");
		text1->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.2f, (float)RM->WINDOW_HEIGHT / 2.5f };
		_ui.push_back(text1);

		//Return to MainMenu
		Button* button3 = new Button([]()
			{
				SM.SetNextScene("MainMenu");
			}
		);
		button3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 5.0f, (float)RM->WINDOW_HEIGHT / 5.0f };
		_ui.push_back(button3);

		TextObject* text3 = new TextObject("RETURN TO MAIN MENU");
		text3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.2f, (float)RM->WINDOW_HEIGHT / 4.8f };
		_ui.push_back(text3);
	}

	void Update() override {
		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}
};