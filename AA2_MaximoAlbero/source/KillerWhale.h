#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "WaveMovement.h"
#include "TargetMovement.h"

class KillerWhale : public Enemy {
private:
    bool _startAtTop;

public:
    KillerWhale(bool startAtTop = false) : Enemy(), _startAtTop(startAtTop) {
        _renderer = new ImageRenderer(_transform, "resources/Wailord.png",
            Vector2(0.f, 0.f), Vector2(306.f, 562.f));
        _transform->size = Vector2(150.f, 80.f);

        // Posición inicial según si empieza arriba o abajo
        if (startAtTop) {
            _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, 0.f);
        }
        else {
            _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x,
                RM->WINDOW_HEIGHT - _transform->size.y);
        }

        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        // Vida y puntos (ya en el constructor, como quieres)
        SetHealth(100);
        SetPointsValue(200);

        // --- Movimientos: definidos aquí en el constructor ---
        float attachedSpeed = 200.f;     // Velocidad horizontal pegado al borde
        float waveSpeed = 100.f;         // Velocidad horizontal en modo onda
        float amplitude = 100.f;         // Amplitud de la onda (altura)
        float frequency = 0.5f;          // Frecuencia (0.5 = media onda por segundo)
        float detachPointX = RM->WINDOW_WIDTH / 2.f;

        // Calcular punto de inicio del movimiento ondulatorio (centro Y)
        float startWaveY = startAtTop ?
            RM->WINDOW_HEIGHT / 3.f :      // Si viene de arriba, baja un poco
            RM->WINDOW_HEIGHT * 3.f / 4.f; // Si viene de abajo, sube un poco

        Vector2 detachPoint(detachPointX, startWaveY);

        // 1) Moverse horizontalmente pegado al borde superior/inferior hasta detachPointX
        movements.push_back(new LeftLinearMovement(_transform, _physics, detachPointX, attachedSpeed));

        // 2) Moverse a la posición de inicio del patrón ondulatorio (target)
        movements.push_back(new TargetMovement(_transform, _physics, detachPoint, attachedSpeed));

        // 3) Movimiento ondulatorio hasta salir de pantalla (inicia su centro en la Y actual al arrancar)
        movements.push_back(new WaveMovement(_transform, _physics, waveSpeed, amplitude, frequency));
        // --- fin movimientos ---
    }

public:
    void Update() override {
        Enemy::Update(); 

        // Destruir cuando sale de la pantalla por la izquierda
        if (_transform->position.x + _transform->size.x < 0.f) {
            Destroy();
        }
    }
};