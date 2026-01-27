#pragma once
#include "EnemyWave.h"
#include "Bubbles.h"

class BubblesWave : public EnemyWave {
private:
    int _count;
    float _offsetX;

public:
    BubblesWave(int count) : _count(count), _offsetX(100.f) {}

    void Start() override {
        _started = true;
        std::cout << "BubblesWave started - spawning " << _count << " bubbles" << std::endl;

        for (int i = 0; i < _count; i++) {
            Bubbles* bubbleUp = new Bubbles(TOP_TO_BOTTOM);
            bubbleUp->GetTransform()->position.x += _offsetX * i;
            RegisterEnemy(bubbleUp);

            Bubbles* bubbleDown = new Bubbles(BOTTOM_TO_TOP);
            bubbleDown->GetTransform()->position.x += _offsetX * i;
            RegisterEnemy(bubbleDown);
        }
    }

    void Update(float deltaTime) override {
        // Las burbujas se actualizan automáticamente
        // Verificar si todas han sido destruidas
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
        std::cout << "BubblesWave finished!" << std::endl;
        _spawnedEnemies.clear();
    }
};