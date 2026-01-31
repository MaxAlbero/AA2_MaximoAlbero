#include "GameplayStatePaused.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "TextObject.h"
#include <iostream>

GameplayStatePaused::GameplayStatePaused()
    : _finished(false), _nextState(-1), _resumeButton(nullptr) {
}

void GameplayStatePaused::Start() {
    _finished = false;
    _nextState = -1;
    std::cout << "Estado: PAUSED" << std::endl;

    // Create the resume button with callback
    if (_resumeButton) {
        delete _resumeButton;
    }
    _resumeButton = new Button([this]() {
        _finished = true;
        _nextState = 0;
        });
    _resumeButton->GetTransform()->position = Vector2(
        RM->WINDOW_WIDTH / 2.f,
        RM->WINDOW_HEIGHT / 1.5f
    );
    _resumeButton->GetTransform()->scale = Vector2(1.5f, 1.5f);
}

void GameplayStatePaused::Update(float deltaTime) {
    // Update button for mouse interaction
    if (_resumeButton) {
        _resumeButton->Update();
    }

    // Listen for keyboard input to resume
    if (IM->GetEvent(SDLK_ESCAPE, KeyState::DOWN) ||
        IM->GetEvent(SDLK_P, KeyState::DOWN)) {
        _finished = true;
        _nextState = 0;
    }
}

void GameplayStatePaused::Render() {
    // Render dark overlay
    SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 200);
    SDL_FRect overlay = { 0.f, 0.f, (float)RM->WINDOW_WIDTH, (float)RM->WINDOW_HEIGHT };
    SDL_RenderFillRect(RM->GetRenderer(), &overlay);

    // Create and render pause text
    TextObject* pauseText = new TextObject("PAUSED - Press P, ESC or the button to Resume");
    pauseText->GetTransform()->position = Vector2(
        RM->WINDOW_WIDTH / 2.f,
        RM->WINDOW_HEIGHT / 2.f
    );
    pauseText->GetTransform()->scale = Vector2(2.f, 2.f);
    pauseText->SetTextColor(SDL_Color{ 255, 255, 255, 255 });
    pauseText->Render();

    // Render the button
    if (_resumeButton) {
        _resumeButton->Render();
    }
}

bool GameplayStatePaused::IsFinished() const {
    return _finished;
}

int GameplayStatePaused::GetNextState() const {
    return _nextState;
}

void GameplayStatePaused::Finish() {
    std::cout << "Saliendo de PAUSED" << std::endl;

    if (_resumeButton) {
        delete _resumeButton;
        _resumeButton = nullptr;
    }
}

bool GameplayStatePaused::ShouldUpdateScene() const {
    return false;
}