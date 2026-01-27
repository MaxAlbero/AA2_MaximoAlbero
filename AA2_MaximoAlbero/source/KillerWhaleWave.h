#pragma once
#include "EnemyWave.h"
#include "KillerWhale.h"

class KillerWhaleWave : public EnemyWave {
private:
    int _count;

public:
    KillerWhaleWave(int count) : _count(count) {}

    void Start() override {
        _started = true;
        std::cout << "KillerWhaleWave started" << std::endl;

        for (int i = 0; i < _count; i++) {
            KillerWhale* kw = new KillerWhale(i % 2 == 0);
            RegisterEnemy(kw);
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
        std::cout << "KillerWhaleWave finished!" << std::endl;
        _spawnedEnemies.clear();
    }
};