#pragma once

class IGameplayContext {
public:
    virtual ~IGameplayContext() {}

    virtual bool HasMoreWaves() const = 0;
    virtual void StartNextWave() = 0;

    virtual bool IsLastLevel() const = 0;
    virtual void TransitionToNextLevel() = 0;
    virtual int GetCurrentLevel() const = 0;
    virtual bool IsLevelComplete() const = 0;

    // NUEVO: obtener referencia al player
    virtual class Player* GetPlayer() = 0;
};