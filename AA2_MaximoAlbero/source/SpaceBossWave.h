#pragma once
#include "EnemyWave.h"
#include "SpaceBoss.h"

class SpaceBossWave : public EnemyWave {
public:
    SpaceBossWave() {}

    void Start() override {
        _started = true;
        std::cout << "LEVEL 2 BOSS - SPACE BOSS INCOMING!" << std::endl;

        SpaceBoss* boss = new SpaceBoss();
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
        std::cout << "SPACE BOSS DEFEATED! LEVEL 2 COMPLETE!" << std::endl;
        _spawnedEnemies.clear();
    }
};