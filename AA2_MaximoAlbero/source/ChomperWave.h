#pragma once
#include "EnemyWave.h"
#include "Chomper.h"

class ChomperWave : public EnemyWave {
private:
    int _count;
    float _offsetChomper;

public:
    ChomperWave(int count) : _count(count), _offsetChomper(50.f) {}

    void Start() override {
        _started = true;

        for (int i = 0; i < _count; i++) {
            Chomper* chomper = new Chomper(
                Vector2(RM->WINDOW_WIDTH - 50.f, _offsetChomper * i)
            );
            RegisterEnemy(chomper);
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
        if (allDead) _finished = true;
    }

    void End() override {
        _spawnedEnemies.clear();
    }
};