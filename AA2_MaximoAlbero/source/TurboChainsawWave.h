#pragma once
#include "EnemyWave.h"
#include "TurboChainsaw.h"

class TurboChainsawWave : public EnemyWave {
private:
    int _count;

public:
    TurboChainsawWave(int amount) : _count(amount) {}

    void Start() override {
        _started = true;
        std::cout << "TURBO CHAINSAW WAVE - " << _count << " enemies incoming!" << std::endl;

        // Calculate how many spawn from each side
        int fromLeftCount = (_count + 1) / 2;      // Round up for left side
        int fromRightCount = _count - fromLeftCount; // Remaining go to right

        // Spawn enemies from left side
        for (int i = 0; i < fromLeftCount; i++) {
            TurboChainsaw* enemy = new TurboChainsaw(FROM_LEFT);
            RegisterEnemy(enemy);
        }

        // Spawn enemies from right side
        for (int i = 0; i < fromRightCount; i++) {
            TurboChainsaw* enemy = new TurboChainsaw(FROM_RIGHT);
            RegisterEnemy(enemy);
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

        if (allDead) {
            _finished = true;
        }
    }

    void End() override {
        std::cout << "TURBO CHAINSAW WAVE CLEARED!" << std::endl;
        _spawnedEnemies.clear();
    }
};