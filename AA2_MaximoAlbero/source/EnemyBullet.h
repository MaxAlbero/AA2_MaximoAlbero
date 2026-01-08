#pragma once
#include "ImageObject.h"
#include "RenderManager.h"

class EnemyBullet : public ImageObject
{
public:
    EnemyBullet(Vector2 initPosition)
        : ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(100.f, 100.f))
    {
        _transform->position = Vector2(initPosition.x - 40.f, initPosition.y);
        _transform->scale = Vector2(0.5f, 0.15f);
        _physics->SetVelocity(Vector2(-1.f, 0.f)); // Velocidad hacia la izquierda
        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    void Update() override {
        //SetLifeTime();
        Object::Update();
    }

    //void SetLifeTime() {
    //    if (_transform->position.x < 0) {
    //        Destroy();
    //    }
    //}

    //void OnCollision(Object* other) override {
    //    Destroy();
    //}
};