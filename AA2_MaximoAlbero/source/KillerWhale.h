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

        if (startAtTop) {
            _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x, 0.f);
        }
        else {
            _transform->position = Vector2(RM->WINDOW_WIDTH + _transform->size.x,
                RM->WINDOW_HEIGHT - _transform->size.y);
        }

        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(50);
        SetPointsValue(200);

        float attachedSpeed = 200.f;
        float waveSpeed = 100.f;
        float amplitude = 100.f;
        float frequency = 0.5f;
        float detachPointX = RM->WINDOW_WIDTH / 2.f;

        float startWaveY = startAtTop ?
            RM->WINDOW_HEIGHT / 3.f :
            RM->WINDOW_HEIGHT * 3.f / 4.f;

        Vector2 detachPoint(detachPointX, startWaveY);

        movements.push_back(new LeftLinearMovement(_transform, _physics, detachPointX, attachedSpeed));
        movements.push_back(new TargetMovement(_transform, _physics, detachPoint, attachedSpeed));
        movements.push_back(new WaveMovement(_transform, _physics, waveSpeed, amplitude, frequency));
    }

public:
    void Update() override {
        Enemy::Update();

        if (_transform->position.x + _transform->size.x < 0.f) {
            Destroy();
        }
    }
};