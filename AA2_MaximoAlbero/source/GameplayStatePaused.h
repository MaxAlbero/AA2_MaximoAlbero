//#pragma once
//#include "GameplayStateBase.h"
//#include "InputManager.h"
//#include <iostream>
//
//class Gameplay;
//
//class GameplayStatePaused : public GameplayStateBase {
//private:
//    Gameplay* _gameplay;
//    bool _finished;
//    int _nextState;
//
//public:
//    GameplayStatePaused(Gameplay* gameplay)
//        : _gameplay(gameplay), _finished(false), _nextState(-1) {
//    }
//
//    void Start() override {
//        _finished = false;
//        _nextState = -1;
//        std::cout << "JUEGO PAUSADO" << std::endl;
//        // Aquí podrías mostrar un menú de pausa
//    }
//
//    void Update(float deltaTime) override {
//        // NO actualizar la física ni los objetos, solo escuchar input
//
//        // Si presiona pausa de nuevo, volver a PLAYING
//        if (IM->GetEvent(SDLK_ESCAPE, KeyState::DOWN) ||
//            IM->GetEvent(SDLK_P, KeyState::DOWN)) {
//            Resume();
//        }
//    }
//
//    void Render() override {
//        // Renderizar overlay de pausa sobre el juego
//        // Puedes mostrar un texto "PAUSED" o un menú
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
//        std::cout << "Saliendo de PAUSA" << std::endl;
//    }
//
//    void Resume() {
//        _finished = true;
//        _nextState = 0; // Volver a PLAYING
//    }
//};