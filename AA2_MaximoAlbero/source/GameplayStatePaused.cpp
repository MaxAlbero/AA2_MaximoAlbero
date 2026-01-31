#include "GameplayStatePaused.h"
#include "InputManager.h"
#include <iostream>
#include "TextObject.h"

GameplayStatePaused::GameplayStatePaused()
    : _finished(false), _nextState(-1), _resumeButton(nullptr) {
}

void GameplayStatePaused::Start() {
    _finished = false;
    _nextState = -1;
    std::cout << "Estado: PAUSED" << std::endl;

    if (_resumeButton) {
        delete _resumeButton;
    }

    _resumeButton = new Button([]() {});
}

void GameplayStatePaused::Update(float deltaTime) {

    if (_resumeButton) {
        _resumeButton->Update();
    }

    if (IM->GetEvent(SDLK_ESCAPE, KeyState::DOWN) ||
        IM->GetEvent(SDLK_P, KeyState::DOWN)) {
        _finished = true;
        _nextState = 0;
    }

    if (_resumeButton && _resumeButton->GetTransform()->scale.x > 1.4f) {
        _finished = true;
        _nextState = 0;
    }
}

void GameplayStatePaused::Render() {
    SDL_SetRenderDrawColor(RM->GetRenderer(), 0, 0, 0, 200);
    SDL_FRect overlay = { 0.f, 0.f, (float)RM->WINDOW_WIDTH, (float)RM->WINDOW_HEIGHT };
    SDL_RenderFillRect(RM->GetRenderer(), &overlay);

    TextObject* pauseText = new TextObject("PAUSED - Press P, ESC or the button to Resume");
    pauseText->GetTransform()->position = Vector2(
        RM->WINDOW_WIDTH / 2.f,
        RM->WINDOW_HEIGHT / 2.f
    );
    pauseText->GetTransform()->scale = Vector2(2.f, 2.f);
    pauseText->SetTextColor(SDL_Color{ 255, 255, 255, 255 });
    _ui.push_back(pauseText);
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