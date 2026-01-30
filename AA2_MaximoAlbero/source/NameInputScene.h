#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include <string>

class NameInputScene : public Scene {
private:
    std::string playerName;
    TextObject* titleText;
    TextObject* inputText;
    TextObject* instructionText;
    bool inputActive;
    float blinkTimer;
    const float BLINK_INTERVAL = 0.5f;

public:
    NameInputScene()
        : playerName(""), titleText(nullptr), inputText(nullptr),
        instructionText(nullptr), inputActive(true), blinkTimer(0.f) {
    }

    ~NameInputScene() {
        // No hacer delete aquí - Scene::OnExit() se encarga
    }

    void OnEnter() override {
        playerName = "";
        inputActive = true;
        blinkTimer = 0.f;

        // Create title
        titleText = new TextObject("ENTER YOUR NAME");
        titleText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.5f, (float)RM->WINDOW_HEIGHT / 3.5f };
        titleText->GetTransform()->scale = Vector2(3.f, 3.f);
        titleText->SetTextColor(SDL_Color{ 255, 215, 0, 255 });
        _ui.push_back(titleText);

        // Create instruction
        instructionText = new TextObject("Type and press ENTER");
        instructionText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.8f, (float)RM->WINDOW_HEIGHT / 2.5f };
        instructionText->GetTransform()->scale = Vector2(2.f, 2.f);
        instructionText->SetTextColor(SDL_Color{ 200, 200, 200, 255 });
        _ui.push_back(instructionText);

        // Create input display
        inputText = new TextObject("_");
        inputText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, (float)RM->WINDOW_HEIGHT / 1.8f };
        inputText->GetTransform()->scale = Vector2(2.5f, 2.5f);
        inputText->SetTextColor(SDL_Color{ 100, 255, 100, 255 });
        _ui.push_back(inputText);
    }

    void OnExit() override {
        // Solo nullificar referencias
        titleText = nullptr;
        instructionText = nullptr;
        inputText = nullptr;
        playerName = "";

        //Scene::OnExit() elimina todo de _ui
        Scene::OnExit();
    }

    void Update() override {
        if (!inputActive) {
            Scene::Update();
            return;
        }

        // Handle character input (A-Z)
        if (IM->GetEvent(SDLK_A, KeyState::DOWN) && playerName.length() < 10) playerName += 'A';
        else if (IM->GetEvent(SDLK_B, KeyState::DOWN) && playerName.length() < 10) playerName += 'B';
        else if (IM->GetEvent(SDLK_C, KeyState::DOWN) && playerName.length() < 10) playerName += 'C';
        else if (IM->GetEvent(SDLK_D, KeyState::DOWN) && playerName.length() < 10) playerName += 'D';
        else if (IM->GetEvent(SDLK_E, KeyState::DOWN) && playerName.length() < 10) playerName += 'E';
        else if (IM->GetEvent(SDLK_F, KeyState::DOWN) && playerName.length() < 10) playerName += 'F';
        else if (IM->GetEvent(SDLK_G, KeyState::DOWN) && playerName.length() < 10) playerName += 'G';
        else if (IM->GetEvent(SDLK_H, KeyState::DOWN) && playerName.length() < 10) playerName += 'H';
        else if (IM->GetEvent(SDLK_I, KeyState::DOWN) && playerName.length() < 10) playerName += 'I';
        else if (IM->GetEvent(SDLK_J, KeyState::DOWN) && playerName.length() < 10) playerName += 'J';
        else if (IM->GetEvent(SDLK_K, KeyState::DOWN) && playerName.length() < 10) playerName += 'K';
        else if (IM->GetEvent(SDLK_L, KeyState::DOWN) && playerName.length() < 10) playerName += 'L';
        else if (IM->GetEvent(SDLK_M, KeyState::DOWN) && playerName.length() < 10) playerName += 'M';
        else if (IM->GetEvent(SDLK_N, KeyState::DOWN) && playerName.length() < 10) playerName += 'N';
        else if (IM->GetEvent(SDLK_O, KeyState::DOWN) && playerName.length() < 10) playerName += 'O';
        else if (IM->GetEvent(SDLK_P, KeyState::DOWN) && playerName.length() < 10) playerName += 'P';
        else if (IM->GetEvent(SDLK_Q, KeyState::DOWN) && playerName.length() < 10) playerName += 'Q';
        else if (IM->GetEvent(SDLK_R, KeyState::DOWN) && playerName.length() < 10) playerName += 'R';
        else if (IM->GetEvent(SDLK_S, KeyState::DOWN) && playerName.length() < 10) playerName += 'S';
        else if (IM->GetEvent(SDLK_T, KeyState::DOWN) && playerName.length() < 10) playerName += 'T';
        else if (IM->GetEvent(SDLK_U, KeyState::DOWN) && playerName.length() < 10) playerName += 'U';
        else if (IM->GetEvent(SDLK_V, KeyState::DOWN) && playerName.length() < 10) playerName += 'V';
        else if (IM->GetEvent(SDLK_W, KeyState::DOWN) && playerName.length() < 10) playerName += 'W';
        else if (IM->GetEvent(SDLK_X, KeyState::DOWN) && playerName.length() < 10) playerName += 'X';
        else if (IM->GetEvent(SDLK_Y, KeyState::DOWN) && playerName.length() < 10) playerName += 'Y';
        else if (IM->GetEvent(SDLK_Z, KeyState::DOWN) && playerName.length() < 10) playerName += 'Z';
        else if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) && playerName.length() < 10) playerName += ' ';

        // Handle backspace
        if (IM->GetEvent(SDLK_BACKSPACE, KeyState::DOWN) && !playerName.empty()) {
            playerName.pop_back();
        }

        // Handle enter - save score and transition to ranking
        if (IM->GetEvent(SDLK_RETURN, KeyState::DOWN)) {
            if (!playerName.empty()) {
                // Save the score with the player name
                HSM->SaveScore(playerName);
                std::cout << "Score saved for: " << playerName << std::endl;
                SM.SetNextScene("MainMenu");
                inputActive = false;
            }
        }

        // Update display with blinking cursor
        if (inputText) {
            blinkTimer += TM.GetDeltaTime();
            if (blinkTimer > BLINK_INTERVAL) {
                blinkTimer = 0.f;
            }

            std::string displayText = playerName;
            if (blinkTimer < BLINK_INTERVAL / 2.f) {
                displayText += "_";
            }

            inputText->SetText(displayText.empty() ? "_" : displayText);
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }
};