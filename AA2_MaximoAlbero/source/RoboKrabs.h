#pragma once
#include "Enemy.h"
#include "LeftLinearMovement.h"
#include "RightLinearMovement.h"
#include "RoboKrabsMovement.h"
#include "EscapeMovement.h"

class RoboKrabs : public Enemy {
public:
    RoboKrabs(Vector2 spawnPos, Transform* playerTransform) : Enemy() {
        _renderer = new ImageRenderer(_transform, "resources/crab.png",
            Vector2(0.f, 0.f), Vector2(517.f, 483.f));

        _transform->scale = Vector2(0.5f, 0.5f);
        _transform->position = spawnPos;
        _physics->AddCollider(new AABB(_transform->position, _transform->size));

        SetHealth(100);
        SetPointsValue(300);

        float speed = 200.f;
        float xThreshold = RM->WINDOW_WIDTH * 2.f / 3.f;

        // Move to center position first
        movements.push_back(new RightLinearMovement(_transform, _physics, xThreshold, speed));

        // Then attach to wall and jump at player
        bool attachToCeiling = (spawnPos.y < RM->WINDOW_HEIGHT / 2.f);
        movements.push_back(new RoboKrabsMovement(_transform, _physics, playerTransform, spawnPos, attachToCeiling,
            700.f /*jumpSpeed*/, 420.f /*returnSpeed*/, 3.f /*minDelay*/, 5.f /*maxDelay*/, 12.f /*tolerance*/));

        // Finally escape
        movements.push_back(new EscapeMovement(_transform, _physics, speed));
    }
};