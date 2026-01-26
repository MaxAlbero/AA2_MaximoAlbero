#pragma once
#include "EnemyMovement.h"
#include <cmath>

class WaveMovement : public EnemyMovement {
private:
    float _horizontalSpeed;  // Velocidad hacia la izquierda
    float _amplitude;        // Amplitud de la onda (altura máxima)
    float _frequency;        // Frecuencia de la onda (cuántas ondas por segundo)
    float _initialY;         // Posición Y inicial (centro de la onda)
    float _timeElapsed;      // Tiempo transcurrido para calcular la onda

public:
    WaveMovement(Transform* transform, RigidBody* rigidBody,
        float horizontalSpeed, float amplitude, float frequency)
        : EnemyMovement(transform, rigidBody),
        _horizontalSpeed(horizontalSpeed),
        _amplitude(amplitude),
        _frequency(frequency),
        _initialY(transform->position.y),
        _timeElapsed(0.f) {
    }

    void Update(float deltaTime) override {
        // Este movimiento nunca termina, se destruye al salir de pantalla

        _timeElapsed += deltaTime;

        // Calcular movimiento ondulatorio usando función seno
        const float PI = 3.14159265f;
        float waveOffset = _amplitude * std::sin(2.0f * PI * _frequency * _timeElapsed);

        // Aplicar velocidad horizontal (siempre hacia la izquierda)
        _transform->position.x -= _horizontalSpeed * deltaTime;

        // Aplicar movimiento ondulatorio vertical
        _transform->position.y = _initialY + waveOffset;
    }

    bool IsFinished() const override {
        return false; // Nunca termina, se destruye al salir de pantalla
    }
};