#pragma once
#include "GameplayStateBase.h"
#include <iostream>

class Gameplay;

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

    // No actualizar la escena mientras estamos en esta pantalla
    bool ShouldUpdateScene() const override;

private:
    void ContinueToNextWave();
    void TransitionToVictory();
};