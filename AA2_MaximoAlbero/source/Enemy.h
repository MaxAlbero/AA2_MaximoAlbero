#pragma once
#include "ImageObject.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "EnemyMovement.h"
#include "ScoreManager.h"
#include <vector>

class Enemy : public ImageObject, public IAttacker, public IDamageable
{
protected:
    int enemyHealth;
    int pointsValue;
    std::vector<EnemyMovement*> movements;
    int currentMovementIndex;

public:
    Enemy()
        : ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)),
        enemyHealth(50), pointsValue(200), currentMovementIndex(0) {
        _transform->size = Vector2(150.f, 150.f);
        _physics->AddCollider(new AABB(_transform->position, _transform->size));
    }

    virtual ~Enemy() {
        for (auto* movement : movements) {
            delete movement;
        }
        movements.clear();
    }

    virtual void Update() override {
        // Actualizar el movimiento actual
        if (currentMovementIndex < movements.size()) {
            EnemyMovement* currentMovement = movements[currentMovementIndex];
            currentMovement->Update(0.02f); // deltaTime

            // Si el movimiento actual terminó, pasar al siguiente
            if (currentMovement->IsFinished()) {
                currentMovementIndex++;
            }
        }

        Object::Update();
    }

    void OnCollision(Object* other) override;

    virtual void ReceiveDamage(int damageToAdd) override {
        enemyHealth -= damageToAdd;
        if (enemyHealth <= 0) {
            Destroy();
        }
    }

    void Destroy() override {
        HSM->AddPoints(pointsValue);
        Object::Destroy();
    }

    int GetHealth() const { return enemyHealth; }
    void SetHealth(int hp) { enemyHealth = hp; }
    void SetPointsValue(int points) { pointsValue = points; }
};