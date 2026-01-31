#pragma once
#include "BackgroundDecoration.h"
#include "Spawner.h"
#include <cstdlib>
#include <ctime>

class BackgroundDecorationSpawner {
private:
    float _spawnTimer;
    float _spawnInterval;
    float _spawnChance;

public:
    BackgroundDecorationSpawner()
        : _spawnTimer(0.f),
        _spawnInterval(3.0f),
        _spawnChance(0.4f) {
    }

    void Update(float deltaTime) {
        _spawnTimer += deltaTime;

        // Intentar spawn cada intervalo
        if (_spawnTimer >= _spawnInterval) {
            _spawnTimer = 0.f;

            if ((rand() % 100) / 100.0f < _spawnChance) {
                SpawnRandomDecoration();
            }
        }
    }

private:
    void SpawnRandomDecoration() {
        DecorationAttachPoint attachPoint = (rand() % 2 == 0) ? CEILING : GROUND;

        int decorationType = rand() % 3;

        BackgroundDecoration* decoration = new BackgroundDecoration(attachPoint, decorationType);
        SPAWNER.SpawnObject(decoration);
    }
};