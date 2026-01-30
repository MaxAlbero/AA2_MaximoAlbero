#pragma once
#include "EnemyMovement.h"
#include <cmath>

class ChaseMovement : public EnemyMovement {
private:
    Transform* _targetTransform;
    float _speed;
    float _tolerance;
    int _maxChases;
    int _currentChase;
    float _stopDuration;
    float _stopTimer;
    bool _isChasing;
    Vector2 _targetPosition;

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
            _rigidBody->SetVelocity(Vector2(0.f, 0.f));
            _stopTimer += deltaTime;

            if (_stopTimer >= _stopDuration) {
                _targetPosition = _targetTransform->position;
                _isChasing = true;
                _stopTimer = 0.f;
                _currentChase++;
            }
        }
        else {
            Vector2 direction = _targetPosition - _transform->position;

            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance <= _tolerance) {
                _rigidBody->SetVelocity(Vector2(0.f, 0.f));
                _isChasing = false;

                if (_currentChase >= _maxChases) {
                    _finished = true;
                }
            }
            else {
                direction.x /= distance;
                direction.y /= distance;
                _rigidBody->SetVelocity(Vector2(direction.x * _speed, direction.y * _speed));
            }
        }
    }
};