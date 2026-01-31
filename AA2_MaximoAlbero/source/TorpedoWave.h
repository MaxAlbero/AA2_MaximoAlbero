#pragma once
#include "EnemyWave.h"
#include "Torpedo.h"

class TorpedoWave : public EnemyWave {
public:
    TorpedoWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;

        float speed = 350.f;
        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 3.f + i * 100.f);
            Torpedo* enemy = new Torpedo(spawnPos, speed);
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