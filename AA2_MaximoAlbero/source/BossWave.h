#pragma once
#include "EnemyWave.h"
#include "BioTitan.h"

class BossWave : public EnemyWave {
public:
    BossWave() {}

    void Start() override {
        _started = true;
        std::cout << "BOSS WAVE - BIO TITAN INCOMING!" << std::endl;

        BioTitan* boss = new BioTitan();
        RegisterEnemy(boss);
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
        std::cout << "BOSS DEFEATED! LEVEL COMPLETE!" << std::endl;
        _spawnedEnemies.clear();
    }
};