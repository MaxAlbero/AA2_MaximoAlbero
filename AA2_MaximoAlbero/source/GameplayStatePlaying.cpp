#include "GameplayStatePlaying.h"
#include "InputManager.h"
#include "TimeManager.h"
#include <iostream>

GameplayStatePlaying::GameplayStatePlaying()
    : _finished(false), _nextState(-1) {
}

void GameplayStatePlaying::Start() {
    _finished = false;
    _nextState = -1;
    std::cout << "Estado: PLAYING" << std::endl;
}

void GameplayStatePlaying::Update(float deltaTime) {
    // El gameplay normal se actualiza en Gameplay::Update()
    // Este estado solo escucha si se presiona pausa

    if (IM->GetEvent(SDLK_ESCAPE, KeyState::DOWN) ||
        IM->GetEvent(SDLK_P, KeyState::DOWN)) {
        _finished = true;
        _nextState = 1; // Ir a PAUSED (índice 1)
    }
}

void GameplayStatePlaying::Render() {
    // El render del gameplay se hace en Gameplay::Render()
}

bool GameplayStatePlaying::IsFinished() const {
    return _finished;
}

int GameplayStatePlaying::GetNextState() const {
    return _nextState;
}

void GameplayStatePlaying::Finish() {
    std::cout << "Saliendo de PLAYING" << std::endl;
}