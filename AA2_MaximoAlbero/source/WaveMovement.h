#pragma once
#include "EnemyMovement.h"
#include <cmath>

class WaveMovement : public EnemyMovement {
private:
    float _horizontalSpeed; 
    float _amplitude;       
    float _frequency;        
    float _initialY;        
    float _timeElapsed;      
    bool _initialized;       

public:
    WaveMovement(Transform* transform, RigidBody* rigidBody,
        float horizontalSpeed, float amplitude, float frequency)
        : EnemyMovement(transform, rigidBody),
        _horizontalSpeed(horizontalSpeed),
        _amplitude(amplitude),
        _frequency(frequency),
        _initialY(0.f), 
        _timeElapsed(0.f),
        _initialized(false) {
    }

    void Update(float deltaTime) override {
        if (!_initialized) {
            if (_transform) {
                _initialY = _transform->position.y;
            }
            else {
                _initialY = 0.f;
            }
            _initialized = true;
            _timeElapsed = 0.f;
        }

        // Este movimiento nunca termina, se destruye al salir de pantalla
        _timeElapsed += deltaTime;

        // Calcular movimiento ondulatorio usando función seno
        const float PI = 3.14159265f;
        float waveOffset = _amplitude * std::sin(2.0f * PI * _frequency * _timeElapsed);

        // Aplicar velocidad horizontal (siempre hacia la izquierda)
        _transform->position.x -= _horizontalSpeed * deltaTime;

        // Aplicar movimiento ondulatorio vertical relativo al centro inicial
        _transform->position.y = _initialY + waveOffset;
    }

    bool IsFinished() const override {
        return false;
    }
};