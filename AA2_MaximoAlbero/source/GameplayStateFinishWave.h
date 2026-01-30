#pragma once
#include "GameplayStateBase.h"
#include "Gameplay.h"
#include "LevelManager.h"
#include <iostream>

class GameplayStateFinishWave : public GameplayStateBase {
private:
    Gameplay* _gameplay;
    bool _finished;
    int _nextState;
    float _displayTimer;
    float _displayDuration;
    bool _isLastWave;

public:
    GameplayStateFinishWave(Gameplay* gameplay);

    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool IsFinished() const override;
    int GetNextState() const override;
    void Finish() override;

    bool ShouldUpdateScene() const override;

private:
    void ContinueToNextWave();
    void TransitionToVictory();
};