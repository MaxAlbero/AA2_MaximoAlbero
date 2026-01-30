#pragma once
#include "EnemyWave.h"
#include "Daniels.h"

class DanielsWave : public EnemyWave {
public:
    DanielsWave(int amount) : _amount(amount) {}

    void Start() override {
        _started = true;
        std::cout << "DANIELS WAVE - " << _amount << " enemies incoming!" << std::endl;

        float horizontalSpacing = 150.f;
        float ceilingY = 80.f;
        float floorY = RM->WINDOW_HEIGHT - 80.f;

        for (int i = 0; i < _amount; i++) {

            float xPos = -100.f - (i * horizontalSpacing);


            float yPos = (i % 2 == 0) ? ceilingY : floorY;

            Vector2 spawnPos(xPos, yPos);
            Daniels* enemy = new Daniels(spawnPos);
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