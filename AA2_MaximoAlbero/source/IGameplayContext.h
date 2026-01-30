#pragma once

class IGameplayContext {
public:
    virtual ~IGameplayContext() {}

    virtual bool HasMoreWaves() const = 0;
    virtual void StartNextWave() = 0;

    // Métodos de nivel
    virtual bool IsLastLevel() const = 0;
    virtual void TransitionToNextLevel() = 0;
    virtual int GetCurrentLevel() const = 0;

    // NUEVO: Indicar que el nivel está completo
    virtual bool IsLevelComplete() const = 0;
};