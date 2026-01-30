#pragma once
#include "EnemyWave.h"
#include "Nuke.h"

class NukeWave : public EnemyWave {
public:
    NukeWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;
        std::cout << "NUKE WAVE - " << _amount << " nukes incoming!" << std::endl;

        float speed = 200.f;
        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH / 2.f + i * 150.f, -50.f);
            Nuke* enemy = new Nuke(spawnPos, speed);
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
        _spawnedEnemies.clear();
    }

private:
    int _amount;
};