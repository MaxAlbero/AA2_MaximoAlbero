#pragma once
#include "GameplayStateBase.h"
#include "IGameplayContext.h"
#include <iostream>

class GameplayStateFinishWave : public GameplayStateBase {
private:
    IGameplayContext* _context;
    bool _finished;
    int _nextState;
    float _displayTimer;
    float _displayDuration;
    bool _isLastWave;

public:
    GameplayStateFinishWave();

    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool IsFinished() const override;
    int GetNextState() const override;
    void Finish() override;

    bool ShouldUpdateScene() const override;

    // Permitir que Gameplay le pase el contexto después de crear el estado
    void SetContext(IGameplayContext* context) { _context = context; }

private:
    void ContinueToNextWave();
    void TransitionToVictory();
};