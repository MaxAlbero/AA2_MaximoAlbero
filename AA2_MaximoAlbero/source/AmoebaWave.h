#pragma once
#include "EnemyWave.h"
#include "Amoeba.h"
#include "Player.h"
#include <vector>

class AmoebaWave : public EnemyWave {
public:
    AmoebaWave(int amount = 8) : _amount(amount) {
    }

    virtual ~AmoebaWave() {}

    void Start() override {
        if (_started) return;
        _started = true;

        // posición de spawn: ligeramente a la izquierda de la pantalla, centrado verticalmente
        float startX = -50.f;
        float centerY = RM->WINDOW_HEIGHT * 0.5f;

        // Creamos 8 copias (o la cantidad solicitada, hasta 8)
        int toSpawn = std::min(8, _amount);
        for (int i = 0; i < toSpawn; ++i) {
            // distribuimos las 8 copias en un bloque vertical cercano (todas salen juntas)
            float y = centerY + (i - toSpawn / 2);
            Vector2 spawnPos(startX, y);
            Amoeba* a = new Amoeba(spawnPos, i);
            SPAWNER.SpawnObject(a);
            RegisterEnemy(a); // registra en la wave para seguimiento
            _spawnedEnemies.push_back(a);
        }
    }

    void Update(float deltaTime) override {
        // comprobar si la wave terminó (todos los enemies pendiente de destroy)
        bool anyAlive = false;
        for (Enemy* e : _spawnedEnemies) {
            if (e && !e->IsPendingDestroy()) {
                anyAlive = true;
                break;
            }
        }
        if (!anyAlive) {
            _finished = true;
        }
    }

    void End() override {
        // limpieza si hiciera falta (normalmente no)
    }

private:
    int _amount;
    std::vector<Enemy*> _spawnedEnemies;
};