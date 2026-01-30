#pragma once
#include "EnemyWave.h"
#include "Angrygons.h"

class AngrygonsWave : public EnemyWave {
public:
    AngrygonsWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;
        std::cout << "ANGRYGONS WAVE - " << _amount << " enemies incoming!" << std::endl;

        float speed = 150.f;
        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH + i * 150.f, RM->WINDOW_HEIGHT / 4.f);
            Angrygons* enemy = new Angrygons(spawnPos, speed);
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
        std::cout << "ANGRYGONS WAVE DEFEATED!" << std::endl;
        _spawnedEnemies.clear();
    }

private:
    int _amount;
};