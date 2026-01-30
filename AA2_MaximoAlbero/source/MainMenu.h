#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "TextObject.h"
#include "InputManager.h"
#include "RenderManager.h"

class MainMenu : public Scene
{
public:
	MainMenu() = default;

	void OnEnter() override
	{
		TextObject* text = new TextObject("MENU");
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.2f, (float)RM->WINDOW_HEIGHT / 3.2f };
		text->GetTransform()->scale = Vector2(5.f, 5.f);
		_ui.push_back(text);

		Button* button1 = new Button([]()
			{
				SM.SetNextScene("Gameplay");
			}
		);
		button1->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button1);

		TextObject* text3 = new TextObject("START GAME");
		text3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 2.0f };
		_ui.push_back(text3);

		//Level Selector
		Button* button2 = new Button([]()
			{
				SM.SetNextScene("LevelSelector");
			}
		);
		button2->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button2);

		TextObject* text4 = new TextObject("LEVEL SELECTOR");
		text4->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 2.0f };
		_ui.push_back(text4);
	}

	void Update() override {
		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}
};