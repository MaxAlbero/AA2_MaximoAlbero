#pragma once
#include "EnemyWave.h"
#include "Circler.h"
#include "CirclerBody.h"

class CirclerWave : public EnemyWave {
public:
    CirclerWave() {}

    void Start() override {
        _started = true;
        std::cout << "CirclerWave started" << std::endl;

        Circler* head = new Circler();
        RegisterEnemy(head);

        Enemy* previousSegment = head;
        for (int i = 0; i < 3; i++) {
            CirclerBody* body = new CirclerBody(120.f);
            SPAWNER.SpawnObject(body);
            previousSegment = body;
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
        std::cout << "CirclerWave finished!" << std::endl;
        _spawnedEnemies.clear();
    }
};