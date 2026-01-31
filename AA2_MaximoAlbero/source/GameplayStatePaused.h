#pragma once
#include "GameplayStateBase.h"
#include "Button.h"

class GameplayStatePaused : public GameplayStateBase {
private:
    bool _finished;
    int _nextState;
    Button* _resumeButton;

public:
    GameplayStatePaused();
    void Start() override;
    void Update(float deltaTime) override;
    void Render() override;
    bool IsFinished() const override;
    int GetNextState() const override;
    void Finish() override;

    bool ShouldUpdateScene() const override;
};