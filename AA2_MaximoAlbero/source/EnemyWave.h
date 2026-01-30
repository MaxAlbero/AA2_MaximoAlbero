#pragma once
#include "Enemy.h"
#include "Spawner.h"
#include <vector>

class EnemyWave {
protected:
    std::vector<Enemy*> _spawnedEnemies;
    bool _started;
    bool _finished;

public:
    EnemyWave() : _started(false), _finished(false) {}
    virtual ~EnemyWave() {}

    virtual void Start() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void End() = 0;

    bool IsFinished() const {
        if (!_finished) {
            for (Enemy* enemy : _spawnedEnemies) {
                if (!enemy->IsPendingDestroy()) {
                    return false;
                }
            }
            return true;
        }
        return _finished;
    }

    const std::vector<Enemy*>& GetSpawnedEnemies() const {
        return _spawnedEnemies;
    }

protected:
    void RegisterEnemy(Enemy* enemy) {
        SPAWNER.SpawnObject(enemy);
        _spawnedEnemies.push_back(enemy);
    }
};