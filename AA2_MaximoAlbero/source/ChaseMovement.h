#pragma once
#include "EnemyMovement.h"
#include <cmath>

class ChaseMovement : public EnemyMovement {
private:
    Transform* _targetTransform; // Transform del jugador
    float _speed;
    float _tolerance; // Distancia mínima para considerar que alcanzó el objetivo
    int _maxChases;   // Número máximo de persecuciones
    int _currentChase;
    float _stopDuration; // Tiempo que se detiene entre persecuciones
    float _stopTimer;
    bool _isChasing;
    Vector2 _targetPosition; // Posición guardada del jugador

public:
    ChaseMovement(Transform* transform, RigidBody* rigidBody,
        Transform* targetTransform, float speed,
        int maxChases = 3, float stopDuration = 1.5f, float tolerance = 10.f)
        : EnemyMovement(transform, rigidBody),
        _targetTransform(targetTransform),
        _speed(speed),
        _tolerance(tolerance),
        _maxChases(maxChases),
        _currentChase(0),
        _stopDuration(stopDuration),
        _stopTimer(0.f),
        _isChasing(false) {

        // Guardar posición inicial del objetivo
        if (_targetTransform) {
            _targetPosition = _targetTransform->position;
        }
    }

    void Update(float deltaTime) override {
        if (_finished || !_targetTransform) {
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            return;
        }

        if (!_isChasing) {
            // Fase de espera
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _stopTimer += deltaTime;

            if (_stopTimer >= _stopDuration) {
                // Iniciar nueva persecución
                _targetPosition = _targetTransform->position;
                _isChasing = true;
                _stopTimer = 0.f;
                _currentChase++;
            }
        }
        else {
            // Fase de persecución
            Vector2 direction = _targetPosition - _transform->position;

            // Calcular distancia manualmente
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance <= _tolerance) {
                // Alcanzó el objetivo, detenerse
                _rigidBody->SetVelocity(Vector2(0.f, 0.f));
                _isChasing = false;

                // Verificar si alcanzó el máximo de persecuciones
                if (_currentChase >= _maxChases) {
                    _finished = true;
                }
            }
            else {
                // Normalizar dirección y aplicar velocidad
                direction.x /= distance;
                direction.y /= distance;
                _rigidBody->SetVelocity(Vector2(direction.x * _speed, direction.y * _speed));
            }
        }
    }
};