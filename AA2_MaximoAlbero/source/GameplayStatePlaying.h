#pragma once
#include "GameplayStateBase.h"

class GameplayStatePlaying : public GameplayStateBase {
private:
    bool _finished;
    int _nextState;

public:
    GameplayStatePlaying();
    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool IsFinished() const override;
    int GetNextState() const override;
    void Finish() override;
};