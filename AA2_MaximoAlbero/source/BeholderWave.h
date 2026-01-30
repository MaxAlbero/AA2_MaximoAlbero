#pragma once
#include "EnemyWave.h"
#include "Beholder.h"
#include "Player.h"

class BeholderWave : public EnemyWave {
private:
    int _count;
    Player* _playerRef;

public:
    BeholderWave(int count, Player* playerRef)
        : _count(count), _playerRef(playerRef) {
    }

    void Start() override {
        _started = true;

        if (!_playerRef) {
            std::cout << "Error: Player reference is null!" << std::endl;
            _finished = true;
            return;
        }

        float margin = 80.f;

        for (int i = 0; i < _count; i++) {
            Vector2 spawnPos;

            switch (i % 4) {
            case 0:
                spawnPos = Vector2(margin, margin);
                break;
            case 1:
                spawnPos = Vector2(RM->WINDOW_WIDTH - margin, margin);
                break;
            case 2:
                spawnPos = Vector2(RM->WINDOW_WIDTH - margin, RM->WINDOW_HEIGHT - margin);
                break;
            case 3:
                spawnPos = Vector2(margin, RM->WINDOW_HEIGHT - margin);
                break;
            }

            Beholder* beholder = new Beholder(spawnPos, _playerRef->GetTransform());
            RegisterEnemy(beholder);
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