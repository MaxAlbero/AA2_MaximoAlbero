#pragma once
#include "Player.h"

class GameplayStateBase {
public:
    virtual ~GameplayStateBase() {}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual bool IsFinished() const = 0;
    virtual int GetNextState() const = 0;
    virtual void Finish() = 0;

    virtual bool ShouldUpdateScene() const { return true; }

    // Callbacks para comunicación sin referencias cruzadas
    virtual void OnPlayerDeath(Player* player) {}  // NUEVO
    virtual void SetGameplayReference(void* gameplayPtr) {}  // NUEVO - void pointer genérico
};