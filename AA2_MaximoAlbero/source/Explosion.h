#pragma once
#include "AnimatedImageObject.h"

class Explosion : public AnimatedImageObject {
private:
    float _elapsedTime;
    float _animationDuration;
    bool _hasFinished;

public:
    Explosion(Vector2 position)
        : AnimatedImageObject(
            "resources/explosion.png",           // texture path
            Vector2(0.f, 0.f),                   // source offset
            Vector2(512.f, 64.f),                // source size (8 frames * 64 width)
            8,                                   // numFrames
            8,                                   // numColumns
            64.f,                                // frameWidth
            64.f,                                // frameHeight
            false                                // looping (false so it plays once)
        ),
        _elapsedTime(0.f),
        _animationDuration(8.f * (1.f / 60.f)),  // 8 frames at ~60 FPS = ~0.133 seconds per frame
        _hasFinished(false)
    {
        _transform->position = position;
        _transform->scale = Vector2(2.f, 2.f);  // Scale up the explosion
        _transform->size = Vector2(64.f, 64.f);
    }

    void Update() override {
        _elapsedTime += TM.GetDeltaTime();

        Object::Update();

        // Check if animation duration has been reached
        if (!_hasFinished && _elapsedTime >= _animationDuration) {
            _hasFinished = true;
            Destroy();
        }
    }
};