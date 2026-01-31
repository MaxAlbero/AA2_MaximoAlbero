#pragma once
#include "ImageObject.h"
#include "RenderManager.h"
#include <cstdlib>

enum DecorationAttachPoint {
    CEILING,
    GROUND
};

class BackgroundDecoration : public ImageObject {
private:
    DecorationAttachPoint _attachPoint;
    float _scrollSpeed;
    int _decorationType;

public:
    BackgroundDecoration(DecorationAttachPoint attachPoint, int decorationType = 0)
        : ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(64.f, 128.f)),
        _attachPoint(attachPoint),
        _scrollSpeed(-70.f),
        _decorationType(decorationType) {

        _transform->size = Vector2(64.f, 128.f);
        _transform->scale = Vector2(1.5f, 1.5f);

        float randomX = RM->WINDOW_WIDTH + (_transform->size.x * _transform->scale.x);
        float randomY;

        if (_attachPoint == CEILING) {
            randomY = 50.f + (rand() % 100);
        }
        else {
            randomY = RM->WINDOW_HEIGHT - 100.f - (rand() % 100);
        }

        _transform->position = Vector2(randomX, randomY);

        _physics->SetVelocity(Vector2(_scrollSpeed, 0.f));

    }

    void Update() override {
        if (_transform->position.x + (_transform->size.x * _transform->scale.x) < 0.f) {
            Destroy();
            return;
        }

        Object::Update();
    }

    void Render() override {
        Object::Render();
    }

    int GetDecorationType() const { return _decorationType; }
    DecorationAttachPoint GetAttachPoint() const { return _attachPoint; }
};