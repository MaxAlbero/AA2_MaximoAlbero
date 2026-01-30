#pragma once
#include "EnemyWave.h"
#include "Annoyer.h"
#include "Player.h"

class AnnoyerWave : public EnemyWave {
public:
    AnnoyerWave(int amount, Player* playerRef)
        : _amount(amount), _playerRef(playerRef) {
    }

    void Start() override {
        _started = true;
        std::cout << "ANNOYER WAVE - " << _amount << " enemies incoming!" << std::endl;

        for (int i = 0; i < _amount; i++) {
            Vector2 spawnPos(RM->WINDOW_WIDTH + i * 200.f, RM->WINDOW_HEIGHT / 3.f + i * 50.f);
            Annoyer* enemy = new Annoyer(spawnPos, _playerRef ? _playerRef->GetTransform() : nullptr);
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
        std::cout << "ANNOYER WAVE DEFEATED!" << std::endl;
        _spawnedEnemies.clear();
    }

private:
    int _amount;
    Player* _playerRef;
};