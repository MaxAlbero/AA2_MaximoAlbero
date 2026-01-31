#pragma once
#include "EnemyWave.h"
#include "RoboKrabs.h"

class RoboKrabsWave : public EnemyWave {
public:
    RoboKrabsWave(int amount, Player* playerRef)
        : _amount(amount), _playerRef(playerRef) {
    }

    void Start() override {
        _started = true;
        std::cout << "ROBO KRABS WAVE - " << _amount << " crabs incoming!" << std::endl;

        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos;

            // Randomly choose side (floor or ceiling)
            bool attachToFloor = (rand() % 2 == 0);

            if (attachToFloor) {
                // Spawn at floor level, random X position
                float randomX = rand() % (int)RM->WINDOW_WIDTH;
                spawnPos = Vector2(randomX, RM->WINDOW_HEIGHT - 50.f);
            }
            else {
                // Spawn at ceiling level, random X position
                float randomX = rand() % (int)RM->WINDOW_WIDTH;
                spawnPos = Vector2(randomX, 50.f);
            }

            RoboKrabs* crab = new RoboKrabs(spawnPos, _playerRef->GetTransform());
            RegisterEnemy(crab);
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
        std::cout << "ROBO KRABS WAVE DEFEATED!" << std::endl;
        _spawnedEnemies.clear();
    }

private:
    int _amount;
    Player* _playerRef;
};