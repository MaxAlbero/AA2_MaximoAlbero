#pragma once

class GameplayStateBase {
public:
    virtual ~GameplayStateBase() {}

    // Llamado cuando se entra en este estado
    virtual void Start() = 0;

    // Actualizar el estado cada frame
    virtual void Update(float deltaTime) = 0;

    // Renderizar (si el estado necesita mostrar algo específico)
    virtual void Render() = 0;

    // Indica si el estado ha terminado y debe transicionar
    virtual bool IsFinished() const = 0;

    // Retorna el índice del siguiente estado (-1 si no hay transición)
    virtual int GetNextState() const = 0;

    // Llamado cuando se sale de este estado
    virtual void Finish() = 0;
};