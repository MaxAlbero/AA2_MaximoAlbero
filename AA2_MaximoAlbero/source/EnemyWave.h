#pragma once
#include "Enemy.h"
#include "Spawner.h"
#include "SpawnerManager.h"
#include <vector>

class EnemyWave {
protected:
    std::vector<Enemy*> _spawnedEnemies;
    bool _started;
    bool _finished;

public:
    EnemyWave() : _started(false), _finished(false) {}
    virtual ~EnemyWave() {}

    // Llamado cuando la wave inicia
    virtual void Start() = 0;

    // Actualizar la wave cada frame
    virtual void Update(float deltaTime) = 0;

    // Llamado cuando la wave termina
    virtual void End() = 0;

    // Indica si la wave ha terminado
    virtual bool IsFinished() const { return _finished; }

    // Obtener enemigos spawneados (para tracking)
    const std::vector<Enemy*>& GetSpawnedEnemies() const { return _spawnedEnemies; }

protected:
    // Helper para registrar enemigos spawneados
    void RegisterEnemy(Enemy* enemy) {
        SPAWNER.SpawnObject(enemy);
        WM->SetEnemy(enemy);
        _spawnedEnemies.push_back(enemy);
    }
};