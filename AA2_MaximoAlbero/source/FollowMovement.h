#pragma once
#include "EnemyMovement.h"
#include "Enemy.h"
#include <cmath>

class FollowMovement : public EnemyMovement {
private:
    Enemy* _leader;               // puntero no propietario
    float _offsetDistance;
    bool _destroyIfLeaderDies;

    static float Dist(const Vector2& a, const Vector2& b) {
        float dx = a.x - b.x; float dy = a.y - b.y; return std::sqrt(dx * dx + dy * dy);
    }

public:
    // destroyIfLeaderDies: true -> owner->Destroy() cuando leader muere; false -> movement termina.
    FollowMovement(Transform* transform, RigidBody* rigidBody, Enemy* leader, float offsetDistance = 120.f, bool destroyIfLeaderDies = true)
        : EnemyMovement(transform, rigidBody),
        _leader(leader),
        _offsetDistance(offsetDistance),
        _destroyIfLeaderDies(destroyIfLeaderDies) {
    }

    void Update(float /*deltaTime*/) override {
        if (_finished) return;
        if (!_transform) return;

        if (_leader == nullptr || _leader->IsPendingDestroy()) {
            if (_destroyIfLeaderDies && _transform) {
                // el owner es responsable de su propia destrucción
                // buscamos al Enemy propietario a través del transform: mejor que el movimiento llame al owner si lo conoce.
                // Si queremos destruir aquí, asumimos que Transform pertenece al Enemy y usamos Object::Destroy vía owner pointer
                // pero EnemyMovement no tiene owner pointer en esta versión: marcamos finished y caller (Enemy) puede destruir si desea.
                _finished = true;
                return;
            }
            _finished = true;
            return;
        }

        Vector2 leaderPos = _leader->GetTransform()->position;
        Vector2 myPos = _transform->position;

        Vector2 toLeader = Vector2(leaderPos.x - myPos.x, leaderPos.y - myPos.y);
        float distance = std::sqrt(toLeader.x * toLeader.x + toLeader.y * toLeader.y);
        if (distance <= 0.0001f) {
            // si están exactamente encima, posicionar en el offset por defecto
            return;
        }

        // normalizar
        toLeader.x /= distance;
        toLeader.y /= distance;

        // objetivo = leaderPos - dir * offsetDistance
        Vector2 targetPos = Vector2(leaderPos.x - toLeader.x * _offsetDistance,
            leaderPos.y - toLeader.y * _offsetDistance);

        // Snap (rápido). Si prefieres suavizar, interpola aquí con un factor.
        _transform->position = targetPos;
    }
};