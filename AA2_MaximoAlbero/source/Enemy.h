#pragma once
#include "ImageObject.h"
#include "Spawner.h"
#include "IAttacker.h"
#include "IDamageable.h"
#include "EnemyMovement.h"
#include "ScoreManager.h"
#include <vector>
#include "AudioManager.h"
#include "Explosion.h"

class Enemy : public ImageObject, public IAttacker, public IDamageable
{
protected:
    int enemyHealth;
    int pointsValue;
    std::vector<EnemyMovement*> movements;
    int currentMovementIndex;
    bool _hasBeenOnScreen;
    bool _isBoss;

public:
    Enemy()
        : ImageObject("resources/image.png", Vector2(0.f, 0.f), Vector2(306.f, 562.f)),
        enemyHealth(50), pointsValue(200), currentMovementIndex(0), _hasBeenOnScreen(false) {
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
        UpdateOnScreenStatus();

        if (currentMovementIndex < movements.size()) {
            EnemyMovement* currentMovement = movements[currentMovementIndex];
            currentMovement->Update(0.02f);

            if (currentMovement->IsFinished()) {
                currentMovementIndex++;
            }
        }

        Object::Update();

        CheckOutOfBoundsDestruction();
    }

    void OnCollision(Object* other) override;

    virtual void Attack(IDamageable* other) const override;

    virtual void ReceiveDamage(int damageToAdd) override {
        enemyHealth -= damageToAdd;
        if (enemyHealth <= 0) {
            Destroy();
        }
    }

    void Destroy() override {
        HSM->AddPoints(pointsValue);
        AM->PlaySound("resources/audio/sfx/LegoYodaDeath.wav");

        Explosion* explosion = new Explosion(_transform->position);
        SPAWNER.SpawnObject(explosion);

        Object::Destroy();
    }

    int GetHealth() const { return enemyHealth; }
    void SetHealth(int hp) { enemyHealth = hp; }
    void SetPointsValue(int points) { pointsValue = points; }

    bool HasBeenOnScreen() const { return _hasBeenOnScreen; }

    bool IsBoss() const { return _isBoss; }
    void SetIsBoss(bool isBoss) { _isBoss = isBoss; }

protected:
    virtual bool ShouldDestroyOutOfBounds() const {
        float effectiveWidth = _transform->size.x * _transform->scale.x;
        float effectiveHeight = _transform->size.y * _transform->scale.y;

        return (_transform->position.x + effectiveWidth < 0.f ||
            _transform->position.x - effectiveWidth > RM->WINDOW_WIDTH ||
            _transform->position.y + effectiveHeight < 0.f ||
            _transform->position.y - effectiveHeight > RM->WINDOW_HEIGHT);
    }

private:
    bool IsWithinScreenBounds() const {
        float effectiveWidth = _transform->size.x * _transform->scale.x;
        float effectiveHeight = _transform->size.y * _transform->scale.y;

        return _transform->position.x + effectiveWidth > 0.f &&
            _transform->position.x - effectiveWidth < RM->WINDOW_WIDTH &&
            _transform->position.y + effectiveHeight > 0.f &&
            _transform->position.y - effectiveHeight < RM->WINDOW_HEIGHT;
    }

    void UpdateOnScreenStatus() {
        if (!_hasBeenOnScreen && IsWithinScreenBounds()) {
            _hasBeenOnScreen = true;
        }
    }

    void CheckOutOfBoundsDestruction() {
        if (_hasBeenOnScreen && ShouldDestroyOutOfBounds()) {
            Destroy();
        }
    }
};