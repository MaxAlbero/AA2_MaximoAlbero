#pragma once
#include "EnemyWave.h"
#include "Ufo.h"

class UfoWave : public EnemyWave {
public:
    UfoWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;
        std::cout << "UFO WAVE - " << _amount << " ufos incoming!" << std::endl;

        float speed = 180.f;
        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH + i * 200.f, 100.f + i * 120.f);
            Ufo* enemy = new Ufo(spawnPos, speed);
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
        std::cout << "UFO WAVE CLEARED!" << std::endl;
        _spawnedEnemies.clear();
    }

private:
    int _amount;
};