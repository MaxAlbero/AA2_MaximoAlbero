#pragma once
#include "EnemyWave.h"
#include "Hmedusa.h"

class HMedusaWave : public EnemyWave {
private:
    int _count;

public:
    HMedusaWave(int count) : _count(count) {}

    void Start() override {
        _started = true;

        for (int i = 0; i < _count; i++) {
            int speed = rand() % 400 + 100;
            float positionY = rand() % (int)RM->WINDOW_HEIGHT;

            Hmedusa* medusa = new Hmedusa(Vector2(RM->WINDOW_WIDTH + 50.f, positionY),(float)speed);
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