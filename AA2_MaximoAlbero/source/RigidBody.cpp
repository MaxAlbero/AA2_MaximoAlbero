#include "RigidBody.h"

bool RigidBody::CheckCollision(const RigidBody* other) {
    for (AABB* ownCollider : _colliders)
    {
        for (AABB* otherCollider : other->_colliders) {
            if (ownCollider->CheckOverlappingAABB(otherCollider)) {
                return true;
            }
        }
    }

    return false;
}

bool RigidBody::ChecckOverlappingPoint(Vector2 point)
{
    for (AABB* ownCollider : _colliders) {
        if (ownCollider->CheckOverlappingPoint(point))
        {
            return true;
        }
    }

    return false;
}

void RigidBody::Update(float dt) {
    //1
    _velocity = _velocity + _acceleration * dt;
    _angularVelocity = _angularVelocity + _angularAcceleration * dt;

    //2
    _velocity = _velocity * (1.0f / (1.0f + dt * _linearDrag));
    _angularVelocity = _angularVelocity * (1.0f / (1.0f + dt * _angularDrag));

    //3
    _transform->position = _transform->position + _velocity * dt;
    _transform->rotation = _transform->rotation + _angularVelocity * dt;

    //4
    _acceleration = Vector2();
    _angularAcceleration = 0.0f;

    //5
    Vector2 offset = (Vector2(-_transform->size.x, -_transform->size.y) / 2.0f) * _transform->scale;

    for (AABB* collider : _colliders) {
        collider->SetTopLeft(_transform->position + offset);
        collider->SetSize(_transform->size * _transform->scale);
    }

}

