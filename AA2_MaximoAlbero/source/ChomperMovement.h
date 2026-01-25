#pragma once
#include "EnemyMovement.h"
#include <cmath>

// Movimiento específico para "Chomper":
// - realiza movimiento circular alrededor de un centro
// - desplaza el centro ligeramente hacia la izquierda de forma continua,
//   de modo que, tras una vuelta completa, la suma de los pequeños desplazamientos
//   coincida con horizontalShiftPerLoop.
// - puede repetir un número de vueltas (maxLoops) o ser infinito (<=0).
class ChomperMovement : public EnemyMovement {
private:
    float _radius;
    float _angularSpeed;            // rad/s
    float _angle;                   // rad
    float _startAngle;              // rad
    float _horizontalShiftPerLoop;  // unidades a desplazar por cada vuelta completa
    int _maxLoops;                  // <=0 => infinito
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

        // Calculamos desplazamiento horizontal continuo: si horizontalShiftPerLoop
        // es la distancia que queremos desplazar por cada vuelta completa,
        // la velocidad horizontal (units/sec) es:
        //    shiftPerSecond = horizontalShiftPerLoop * (angularSpeed / (2*PI))
        float shiftPerSecond = 0.f;
        if (std::abs(_angularSpeed) > 1e-6f) {
            shiftPerSecond = _horizontalShiftPerLoop * (_angularSpeed / TWO_PI);
        }

        // Aplicamos desplazamiento continuo del centro (suavizado)
        _center.x -= shiftPerSecond * deltaTime;

        // Avanzamos el ángulo
        _angle += _angularSpeed * deltaTime;

        // Actualizamos posición en la circunferencia usando el centro desplazado
        _transform->position.x = _center.x + _radius * std::cos(_angle);
        _transform->position.y = _center.y + _radius * std::sin(_angle);

        // Detectar vueltas completas robustamente (puede pasar más de 2*PI en un frame)
        if (_angle >= _startAngle + TWO_PI) {
            float excess = _angle - _startAngle;
            int completed = static_cast<int>(std::floor(excess / TWO_PI));
            if (completed > 0) {
                _loopsDone += completed;
                // normalizar ángulo dentro del rango
                _angle = _angle - completed * TWO_PI;

                // Si se usaba antes desplazar por vuelta, ya está hecho de forma continua,
                // así que no aplicamos ningún salto adicional ahora.

                // Si hemos completado las vueltas solicitadas, marcamos finished
                if (_maxLoops > 0 && _loopsDone >= _maxLoops) {
                    _finished = true;
                    // posicionar en el "punto alto" final (opcional)
                    _transform->position = Vector2(
                        _center.x + _radius * std::cos(_startAngle),
                        _center.y + _radius * std::sin(_startAngle)
                    );
                }
            }
        }
    }
};