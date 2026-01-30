#pragma once
#include "EnemyWave.h"
#include "BioTitan.h"

class BioTitanWave : public EnemyWave {
public:
    BioTitanWave() {}

    void Start() override {
        _started = true;
        std::cout << "LEVEL 1 BOSS - BIO TITAN INCOMING!" << std::endl;

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
        std::cout << "BIO TITAN DEFEATED! LEVEL 1 COMPLETE!" << std::endl;
        _spawnedEnemies.clear();
    }
};