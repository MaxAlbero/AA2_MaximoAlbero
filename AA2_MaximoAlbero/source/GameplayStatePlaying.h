//#pragma once
//#include "GameplayStateBase.h"
//#include "Player.h"
//#include "SpawnWaves.h"
//#include <vector>
//
//class Gameplay; // Forward declaration
//
//class GameplayStatePlaying : public GameplayStateBase {
//private:
//    Gameplay* _gameplay;
//    bool _finished;
//    int _nextState;
//
//public:
//    GameplayStatePlaying(Gameplay* gameplay)
//        : _gameplay(gameplay), _finished(false), _nextState(-1) {
//    }
//
//    void Start() override {
//        _finished = false;
//        _nextState = -1;
//        std::cout << "Estado PLAYING iniciado" << std::endl;
//    }
//
//    void Update(float deltaTime) override;
//
//    void Render() override {
//        // El gameplay normal ya renderiza todo
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
//        std::cout << "Estado PLAYING finalizado" << std::endl;
//    }
//
//    // Métodos para transicionar
//    void TransitionToPause() {
//        _finished = true;
//        _nextState = 1; // Índice del estado PAUSED
//    }
//
//    void TransitionToFinishWave() {
//        _finished = true;
//        _nextState = 2; // Índice del estado FINISH_WAVE
//    }
//
//    void TransitionToDeath() {
//        _finished = true;
//        _nextState = 3; // Índice del estado DEATH
//    }
//};