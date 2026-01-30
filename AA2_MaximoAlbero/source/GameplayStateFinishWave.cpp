#include "GameplayStateFinishWave.h"
#include "InputManager.h"
#include <iostream>

GameplayStateFinishWave::GameplayStateFinishWave()
    : _context(nullptr), _finished(false), _nextState(-1),
    _displayTimer(0.f), _displayDuration(2.0f), _isLastWave(false) {
}

void GameplayStateFinishWave::Start() {
    _finished = false;
    _nextState = -1;
    _displayTimer = 0.f;

    // Verificar si es la última wave
    _isLastWave = (_context == nullptr) ? false : !_context->HasMoreWaves();
    std::cout << "¡OLEADA COMPLETADA!" << std::endl;
}

void GameplayStateFinishWave::Update(float deltaTime) {
    _displayTimer += deltaTime;

    if (_isLastWave) {
        // Es la última wave, esperar input o tiempo para transicionar
        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
            IM->GetLeftClick() ||
            _displayTimer >= 5.0f) {
            TransitionToVictory();
        }
    }
    else {
        // Hay más waves, continuar automáticamente
        ContinueToNextWave();
    }
}

void GameplayStateFinishWave::Render() {
    // TODO: renderizar mensaje de "wave cleared" o "Level complete!"
}

bool GameplayStateFinishWave::IsFinished() const {
    return _finished;
}

int GameplayStateFinishWave::GetNextState() const {
    return _nextState;
}

void GameplayStateFinishWave::Finish() {
    std::cout << "Continuando al siguiente estado..." << std::endl;
}

bool GameplayStateFinishWave::ShouldUpdateScene() const {
    return false;
}

void GameplayStateFinishWave::ContinueToNextWave() {
    if (_context) {
        _context->StartNextWave();
    }
    _finished = true;
    _nextState = 0; // volver a PLAYING
}

void GameplayStateFinishWave::TransitionToVictory() {
    // Llamar a TransitionToNextLevel que maneja todo (cambio de nivel o GameOver)
    if (_context) {
        _context->TransitionToNextLevel();
    }
    
    _finished = true;
    _nextState = 0; // volver a PLAYING (con el nuevo nivel cargado)
}