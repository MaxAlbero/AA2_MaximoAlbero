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

        Vector2 spawnPos(-100.f, RM->WINDOW_HEIGHT / 2.f);
        Ufo* enemy = new Ufo(spawnPos, speed);
        RegisterEnemy(enemy);
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