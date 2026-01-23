#pragma once
#include "Vector2.h"
#include "Transform.h"
#include "RigidBody.h"

class EnemyMovement {
protected:
    Transform* _transform;
    RigidBody* _rigidBody;
    bool _finished;

public:
    EnemyMovement(Transform* transform, RigidBody* rigidBody)
        : _transform(transform), _rigidBody(rigidBody), _finished(false) {
    }

    virtual ~EnemyMovement() {}

    virtual void Update(float deltaTime) = 0;
    virtual bool IsFinished() const { return _finished; }
};