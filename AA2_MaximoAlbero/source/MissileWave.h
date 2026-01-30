#pragma once
#include "EnemyWave.h"
#include "Missile.h"

class MissileWave : public EnemyWave {
public:
    MissileWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;
        std::cout << "MISSILE WAVE - " << _amount << " missiles incoming!" << std::endl;

        float speed = 300.f;
        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f + (i - _amount / 2) * 80.f);
            Missile* enemy = new Missile(spawnPos, speed);
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