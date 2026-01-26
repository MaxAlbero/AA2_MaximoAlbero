//#pragma once
//#include "GameplayStateBase.h"
//#include "InputManager.h"
//#include <iostream>
//
//class Gameplay;
//
//class GameplayStateFinishWave : public GameplayStateBase {
//private:
//    Gameplay* _gameplay;
//    bool _finished;
//    int _nextState;
//    float _displayTimer;
//    float _displayDuration;
//
//public:
//    GameplayStateFinishWave(Gameplay* gameplay)
//        : _gameplay(gameplay), _finished(false), _nextState(-1),
//        _displayTimer(0.f), _displayDuration(2.0f) {
//    }
//
//    void Start() override {
//        _finished = false;
//        _nextState = -1;
//        _displayTimer = 0.f;
//        std::cout << "¡OLEADA COMPLETADA!" << std::endl;
//    }
//
//    void Update(float deltaTime) override {
//        _displayTimer += deltaTime;
//
//        // Esperar input del jugador o timeout
//        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
//            IM->GetLeftClick() ||
//            _displayTimer >= _displayDuration) {
//
//            // Verificar si hay más oleadas
//            if (HasMoreWaves()) {
//                ContinueToNextWave();
//            }
//            else {
//                // No hay más oleadas, mostrar pantalla de victoria
//                TransitionToVictory();
//            }
//        }
//    }
//
//    void Render() override {
//        // Mostrar mensaje "WAVE CLEARED" o estadísticas
//    }
//
//    bool IsFinished() const override {
//        return _finished;
//    }
//
//    int GetNextState() const override {
//        return _nextState;
//    }
//
//    void Finish() override {
//        std::cout << "Continuando al siguiente estado..." << std::endl;
//    }
//
//private:
//    bool HasMoreWaves() {
//        bool _true = true;
//        return _true;
//    }// Implementar según tu SpawnWaves
//
//    void ContinueToNextWave() {
//        _finished = true;
//        _nextState = 0; // Volver a PLAYING
//    }
//
//    void TransitionToVictory() {
//        _finished = true;
//        _nextState = 4; // Estado VICTORY (crear después)
//    }
//};