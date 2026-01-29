#include "GameplayStateFinishWave.h"
#include "Gameplay.h"
#include "InputManager.h"
#include <iostream>

GameplayStateFinishWave::GameplayStateFinishWave(Gameplay* gameplay)
    : _gameplay(gameplay), _finished(false), _nextState(-1),
      _displayTimer(0.f), _displayDuration(2.0f), _isLastWave(false) {
}

void GameplayStateFinishWave::Start() {
    _finished = false;
    _nextState = -1;
    _displayTimer = 0.f;
    // Aquí sí podemos consultar a Gameplay porque incluimos Gameplay.h
    _isLastWave = (_gameplay == nullptr) ? false : !_gameplay->HasMoreWaves();
    std::cout << "¡OLEADA COMPLETADA!" << std::endl;
}

void GameplayStateFinishWave::Update(float deltaTime) {
    _displayTimer += deltaTime;

    if (_isLastWave) {
        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
            IM->GetLeftClick() ||
            _displayTimer >= 5.0f) {
            TransitionToVictory();
        }
    }
    else {
        ContinueToNextWave();
        //if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
        //    IM->GetLeftClick() ||
        //    _displayTimer >= _displayDuration) {
        //    ContinueToNextWave();
        //}
    }
}

void GameplayStateFinishWave::Render() {
    //TODO: renderizar mensaje de "wave cleared" si se desea
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
    if (_gameplay) {
        _gameplay->ForceStartNextWave();
    }
    _finished = true;
    _nextState = 0; // volver a PLAYING
}

void GameplayStateFinishWave::TransitionToVictory() {
    _finished = true;
    _nextState = 0; // TODO: CAMBIAR ESTO PARA CUANDO SEA EL FINAL DEL SEGUNDO NIVEL PASAR A GUARDAR EL SCORE DE LA PARTIDA
}
