//#pragma once
//#include "GameplayStateBase.h"
//#include "TimeManager.h"
//#include <iostream>
//
//class Gameplay;
//
//class GameplayStateDeath : public GameplayStateBase {
//private:
//    Gameplay* _gameplay;
//    bool _finished;
//    int _nextState;
//    float _deathAnimationTimer;
//    float _blackScreenTimer;
//    bool _showingBlackScreen;
//
//    const float DEATH_ANIMATION_DURATION = 1.0f;
//    const float BLACK_SCREEN_DURATION = 2.0f;
//
//public:
//    GameplayStateDeath(Gameplay* gameplay)
//        : _gameplay(gameplay), _finished(false), _nextState(-1),
//        _deathAnimationTimer(0.f), _blackScreenTimer(0.f),
//        _showingBlackScreen(false) {
//    }
//
//    void Start() override {
//        _finished = false;
//        _nextState = -1;
//        _deathAnimationTimer = 0.f;
//        _blackScreenTimer = 0.f;
//        _showingBlackScreen = false;
//
//        std::cout << "JUGADOR MUERTO" << std::endl;
//        // Reproducir animación de muerte
//        // Reproducir sonido de muerte
//    }
//
//    void Update(float deltaTime) override {
//        if (!_showingBlackScreen) {
//            // Fase 1: Mostrar animación de muerte (1 segundo)
//            _deathAnimationTimer += deltaTime;
//
//            if (_deathAnimationTimer >= DEATH_ANIMATION_DURATION) {
//                _showingBlackScreen = true;
//                DestroyAllGameplayElements();
//            }
//        }
//        else {
//            // Fase 2: Pantalla negra (2 segundos)
//            _blackScreenTimer += deltaTime;
//
//            if (_blackScreenTimer >= BLACK_SCREEN_DURATION) {
//                HandleRespawnOrGameOver();
//            }
//        }
//    }
//
//    void Render() override {
//        if (_showingBlackScreen) {
//            // Renderizar pantalla negra
//            // SDL_SetRenderDrawColor(..., 0, 0, 0, 255);
//            // SDL_RenderClear(...);
//        }
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
//        std::cout << "Saliendo del estado DEATH" << std::endl;
//    }
//
//private:
//    void DestroyAllGameplayElements();  // Limpiar enemigos, balas, etc.
//
//    void HandleRespawnOrGameOver() {
//        if (HasExtraLives()) {
//            RespawnPlayer();
//        }
//        else {
//            GameOver();
//        }
//    }
//
//    bool HasExtraLives();  // Verificar vidas extra
//    void RespawnPlayer();  // Resetear desde última oleada
//    void GameOver();       // Ir a pantalla de Game Over
//};