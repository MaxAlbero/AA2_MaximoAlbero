#include "GameplayStateFinishWave.h"
#include "Gameplay.h"
#include "InputManager.h"
#include "LevelManager.h"
#include <iostream>

GameplayStateFinishWave::GameplayStateFinishWave(Gameplay* gameplay)
    : _gameplay(gameplay), _finished(false), _nextState(-1),
    _displayTimer(0.f), _displayDuration(2.0f), _isLastWave(false) {
}

void GameplayStateFinishWave::Start() {
    _finished = false;
    _nextState = -1;
    _displayTimer = 0.f;
    _isLastWave = (_gameplay == nullptr) ? false : !_gameplay->HasMoreWaves();
    std::cout << "¡OLEADA COMPLETADA!" << std::endl;
    std::cout << "¿Último wave? " << (_isLastWave ? "SÍ" : "NO") << std::endl;
}

void GameplayStateFinishWave::Update(float deltaTime) {
    _displayTimer += deltaTime;

    if (_isLastWave) {
        std::cout << "Esperando input para victoria... " << _displayTimer << "s" << std::endl;
        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
            IM->GetLeftClick() ||
            _displayTimer >= 5.0f) {
            TransitionToVictory();
        }
    }
    else {
        // IMPORTANTE: Solo ejecutar UNA VEZ
        if (!_finished) {
            std::cout << "Transitioning to next wave..." << std::endl;
            ContinueToNextWave();
        }
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
    // Verificar si hay más waves EN ESTE NIVEL
    if (_gameplay && _gameplay->HasMoreWaves()) {
        std::cout << "Hay más waves en este nivel. Iniciando siguiente wave..." << std::endl;
        _gameplay->ForceStartNextWave();
        _finished = true;
        _nextState = 0; // Volver a PLAYING
    }
    // Si NO hay más waves, comprobar si hay más NIVELES
    else if (LM.HasNextLevel()) {
        std::cout << "Nivel " << LM.GetCurrentLevel() << " completado. Transitioning to Level "
            << (LM.GetCurrentLevel() + 1) << std::endl;

        if (LM.NextLevel()) {
            std::cout << "Nivel " << LM.GetCurrentLevel() << " cargado correctamente" << std::endl;

            // IMPORTANTE: Recargar Gameplay para el nuevo nivel
            if (_gameplay) {
                _gameplay->ReloadLevel();
            }

            _finished = true;
            _nextState = 0; // Volver a PLAYING con el nuevo nivel
        }
    }
    else {
        // No hay más waves ni niveles = Victoria final
        std::cout << "¡JUEGO COMPLETADO!" << std::endl;
        TransitionToVictory();
    }
}

void GameplayStateFinishWave::TransitionToVictory() {
    std::cout << "GAME COMPLETED! All levels finished!" << std::endl;
    _finished = true;
    _nextState = 0; // En el futuro: SM.SetNextScene("VictoryScreen");
}