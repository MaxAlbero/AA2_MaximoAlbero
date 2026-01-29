#include "GameplayStatePaused.h"
#include "InputManager.h"
#include <iostream>

GameplayStatePaused::GameplayStatePaused()
    : _finished(false), _nextState(-1) {
}

void GameplayStatePaused::Start() {
    _finished = false;
    _nextState = -1;
    std::cout << "Estado: PAUSED" << std::endl;
}

void GameplayStatePaused::Update(float deltaTime) {
    // En pausa NO actualizamos delta time ni objetos
    // Solo escuchamos input para volver a PLAYING

    if (IM->GetEvent(SDLK_ESCAPE, KeyState::DOWN) ||
        IM->GetEvent(SDLK_P, KeyState::DOWN)) {
        _finished = true;
        _nextState = 0; // Volver a PLAYING (índice 0)
    }
}

void GameplayStatePaused::Render() {
    // Aquí podrías renderizar un overlay "PAUSED"
}

bool GameplayStatePaused::IsFinished() const {
    return _finished;
}

int GameplayStatePaused::GetNextState() const {
    return _nextState;
}

void GameplayStatePaused::Finish() {
    std::cout << "Saliendo de PAUSED" << std::endl;
}

bool GameplayStatePaused::ShouldUpdateScene() const {
    return false;
}