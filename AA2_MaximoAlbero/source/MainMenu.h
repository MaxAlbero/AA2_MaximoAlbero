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
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.5f };
		text->GetTransform()->scale = Vector2(5.f, 5.f);
		_ui.push_back(text);
		TextObject* text2 = new TextObject("PRESS THE BUTTON TO CONTINUE");
		text2->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.2f };
		_ui.push_back(text2);



		Button* button1 = new Button([]() 
			{
				SM.SetNextScene("Gameplay");
			}
		);
		button1->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button1);

		//Level Selector
		Button* button2 = new Button([]()
			{
				SM.SetNextScene("LevelSelector");
			}
		);
		button2->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button2);

		//Check Ranking


		//Enable/Disable Audio


		//Exit
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

