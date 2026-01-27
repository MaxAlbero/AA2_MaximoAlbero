#pragma once

class GameplayStateBase {
public:
    virtual ~GameplayStateBase() {}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual bool IsFinished() const = 0;
    virtual int GetNextState() const = 0;
    virtual void Finish() = 0;
};