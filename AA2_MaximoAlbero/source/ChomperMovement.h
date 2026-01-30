#pragma once
#include "EnemyMovement.h"
#include <cmath>

class ChomperMovement : public EnemyMovement {
private:
    float _radius;
    float _angularSpeed;
    float _angle;
    float _startAngle;
    float _horizontalShiftPerLoop;
    int _maxLoops;
    int _loopsDone;
    Vector2 _center;

public:
    ChomperMovement(Transform* transform, RigidBody* rigidBody,
        const Vector2& center,
        float radius,
        float angularSpeed,
        float horizontalShiftPerLoop = 50.f,
        int maxLoops = 0,
        float startAngle = -1.5707963f)
        : EnemyMovement(transform, rigidBody),
        _radius(radius),
        _angularSpeed(angularSpeed),
        _angle(startAngle),
        _startAngle(startAngle),
        _horizontalShiftPerLoop(horizontalShiftPerLoop),
        _maxLoops(maxLoops),
        _loopsDone(0),
        _center(center)
    {
        if (_transform) {
            _transform->position = Vector2(
                _center.x + _radius * std::cos(_angle),
                _center.y + _radius * std::sin(_angle)
            );
        }
    }

    void Update(float deltaTime) override {
        if (_finished) return;
        if (!_transform) return;

        const float TWO_PI = 2.0f * 3.14159265f;

        float shiftPerSecond = 0.f;
        if (std::abs(_angularSpeed) > 1e-6f) {
            shiftPerSecond = _horizontalShiftPerLoop * (_angularSpeed / TWO_PI);
        }

        _center.x -= shiftPerSecond * deltaTime;

        _angle += _angularSpeed * deltaTime;

        _transform->position.x = _center.x + _radius * std::cos(_angle);
        _transform->position.y = _center.y + _radius * std::sin(_angle);

        if (_angle >= _startAngle + TWO_PI) {
            float excess = _angle - _startAngle;
            int completed = static_cast<int>(std::floor(excess / TWO_PI));
            if (completed > 0) {
                _loopsDone += completed;
                _angle = _angle - completed * TWO_PI;

                if (_maxLoops > 0 && _loopsDone >= _maxLoops) {
                    _finished = true;
                    _transform->position = Vector2(
                        _center.x + _radius * std::cos(_startAngle),
                        _center.y + _radius * std::sin(_startAngle)
                    );
                }
            }
        }
    }
};