#pragma once
#include "EnemyWave.h"
#include "TurboChainsaw.h"

class TurboChainsawWave : public EnemyWave {
public:
    TurboChainsawWave() {}

    void Start() override {
        _started = true;
        std::cout << "TURBO CHAINSAW WAVE - 2 enemies incoming!" << std::endl;

        // Un enemigo desde la izquierda y otro desde la derecha para patrón simétrico
        TurboChainsaw* enemy1 = new TurboChainsaw(FROM_LEFT);
        TurboChainsaw* enemy2 = new TurboChainsaw(FROM_RIGHT);

        RegisterEnemy(enemy1);
        RegisterEnemy(enemy2);
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