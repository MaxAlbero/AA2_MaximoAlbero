#pragma once
#include "GameplayStateBase.h"
#include "IGameplayContext.h"
#include "TextObject.h"  // AÑADE ESTO
#include <iostream>

class GameplayStateFinishWave : public GameplayStateBase {
private:
    IGameplayContext* _context;
    bool _finished;
    int _nextState;
    float _displayTimer;
    float _displayDuration;
    bool _isLastWave;
    bool _isLevelComplete;
    bool _isBossDefeated;

    // TextObjects para renderizar información del final de nivel
    TextObject* _levelCompleteText;
    TextObject* _bonusPointsText;
    TextObject* _continueText;
    TextObject* _bossDefeatText;
    int _bonusPoints;

public:
    GameplayStateFinishWave();
    ~GameplayStateFinishWave();

    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool IsFinished() const override;
    int GetNextState() const override;
    void Finish() override;

    bool ShouldUpdateScene() const override;

    void SetContext(IGameplayContext* context) { _context = context; }

private:
    void ContinueToNextWave();
    void TransitionToVictory();
    void CalculateBonusPoints();
};