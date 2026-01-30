#pragma once
#include "WeaponComponent.h"
#include "PlayerBullet.h"
#include "Spawner.h"
#include <cmath>

class TurretWeapon : public WeaponComponent {
private:
    float _rotation;
    float _maxRotation;
    float _rotationSign; // 1.0 para torreta inferior, -1.0 para superior
    float _turretXAccumulator;
    const float _rotationPerStep = 45.f;
    const float _distancePerStep = 100.f;

public:
    TurretWeapon(Vector2 offset, bool isTop)
        : WeaponComponent("resources/turret.png", Vector2(482.f, 180.f), offset, Vector2(0.5f, 0.5f)),
        _rotation(0.f), _maxRotation(180.f), _turretXAccumulator(0.f) {
        _rotationSign = isTop ? -1.0f : 1.0f;
    }

    void Update(Vector2 playerPosition) override {
        if (!_isEquipped) return;

        _visual->GetTransform()->position = playerPosition + _offset;
        _visual->GetTransform()->rotation = _rotation * _rotationSign;
        _visual->Update();
    }

    void UpdateRotation(float deltaX) {
        if (!_isEquipped || deltaX == 0.f) return;

        _turretXAccumulator += deltaX;

        while (std::abs(_turretXAccumulator) >= _distancePerStep) {
            int stepSign = (_turretXAccumulator > 0.f) ? 1 : -1;
            float deltaAngle = _rotationPerStep * static_cast<float>(stepSign);

            _rotation += deltaAngle;

            if (_rotation > _maxRotation) _rotation = _maxRotation;
            if (_rotation < 0.f) _rotation = 0.f;

            _turretXAccumulator -= static_cast<float>(stepSign) * _distancePerStep;
        }
    }

    void Shoot(Vector2 playerPosition) override {
        if (!_isEquipped) return;

        const float PI = 3.14159265f;
        Vector2 turretPos = _visual->GetTransform()->position;
        float angleDeg = _visual->GetTransform()->rotation;
        float rad = angleDeg * PI / 180.0f;

        float tipDistance = _visual->GetTransform()->size.x * 0.5f * _visual->GetTransform()->scale.x;
        Vector2 bulletOffset = Vector2(std::cos(rad) * tipDistance, std::sin(rad) * tipDistance);

        SPAWNER.SpawnObject(new PlayerBullet(turretPos + bulletOffset, angleDeg));
    }
};