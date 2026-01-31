#pragma once
#include "Scene.h"
#include "Button.h"
#include "SceneManager.h"
#include "TextObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "AudioManager.h"

class MainMenu : public Scene
{
private:
	bool _audioEnabled;

public:
	MainMenu() : _audioEnabled(true) {}

	void OnEnter() override
	{
		AM->PlaySoundLooping("resources/audio/music/MenuBackground.wav");

		TextObject* text = new TextObject("MENU");
		text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.2f, (float)RM->WINDOW_HEIGHT / 3.2f };
		text->GetTransform()->scale = Vector2(5.f, 5.f);
		_ui.push_back(text);

		// START GAME
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

		// LEVEL SELECTOR
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

		// RANKING
		Button* button3 = new Button([]()
			{
				SM.SetNextScene("Ranking");
			}
		);
		button3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 1.5f, (float)RM->WINDOW_HEIGHT / 1.7f };
		_ui.push_back(button3);

		TextObject* text5 = new TextObject("RANKING");
		text5->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 1.4f, (float)RM->WINDOW_HEIGHT / 2.0f };
		_ui.push_back(text5);

		// AUDIO TOGGLE
		Button* audioButton = new Button([this]()
			{
				_audioEnabled = !_audioEnabled;
				if (_audioEnabled) {
					AM->Unmute();
				}
				else {
					AM->Mute();
				}
			}
		);
		audioButton->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 1.3f };
		_ui.push_back(audioButton);

		TextObject* audioText = new TextObject("MUTE/UNMUTE AUDIO");
		audioText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 1.15f };
		audioText->GetTransform()->scale = Vector2(1.2f, 1.2f);
		_ui.push_back(audioText);

		// EXIT GAME
		Button* exitButton = new Button([]()
			{
				SDL_Quit();
			}
		);
		exitButton->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.3f };
		_ui.push_back(exitButton);

		TextObject* exitText = new TextObject("EXIT");
		exitText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 1.15f };
		exitText->GetTransform()->scale = Vector2(1.2f, 1.2f);
		_ui.push_back(exitText);
	}

	void OnExit() override {
		AM->HaltAudio();
		Scene::OnExit();
	}


	void Update() override {
		Scene::Update();
	}

	void Render() override {
		Scene::Render();
	}
};