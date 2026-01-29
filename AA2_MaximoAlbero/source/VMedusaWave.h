#pragma once
#include "EnemyWave.h"
#include "Vmedusa.h"

class VMedusaWave : public EnemyWave {
private:
    int _count;

public:
    VMedusaWave(int count) : _count(count) {}

    void Start() override {
        _started = true;

        for (int i = 0; i < _count; i++) {
            float positionX = rand() % (int)RM->WINDOW_WIDTH;

            Vmedusa* medusa = new Vmedusa(
                Vector2(positionX, RM->WINDOW_HEIGHT + 50.f)
            );
            RegisterEnemy(medusa);
        }
    }

    void Update(float deltaTime) override {
        bool allDead = true;
        for (Enemy* enemy : _spawnedEnemies) {
            if (!enemy->IsPendingDestroy()) {
                allDead = false;
                break;
            }
        }
        if (allDead) _finished = true;
    }

    void End() override {
        _spawnedEnemies.clear();
    }
};