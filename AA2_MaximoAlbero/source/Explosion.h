#pragma once
#include "AnimatedImageObject.h"

class Explosion : public AnimatedImageObject {
private:
    float _elapsedTime;
    float _animationDuration;
    bool _hasFinished;

public:
    Explosion(Vector2 position)
        : AnimatedImageObject("resources/explosion.png",Vector2(0.f, 0.f), Vector2(512.f, 64.f),8,8,64.f, 64.f, false),
        _elapsedTime(0.f),
        _animationDuration(8.f * (1.f / 60.f)),
        _hasFinished(false)
    {
        _transform->position = position;
        _transform->scale = Vector2(2.f, 2.f); 
        _transform->size = Vector2(64.f, 64.f);
    }

    void Update() override {
        _elapsedTime += TM.GetDeltaTime();

        Object::Update();

        if (!_hasFinished && _elapsedTime >= _animationDuration) {
            _hasFinished = true;
            Destroy();
        }
    }
};