#pragma once
#include "EnemyWave.h"
#include "WaveFactory.h"
#include "LoadLevel.h"
#include "PowerUp.h"
#include "Player.h"
#include <queue>
#include <string>

class WaveManager {
private:
    std::queue<EnemyWave*> _waves;
    EnemyWave* _currentWave;
    float _delayTimer;
    float _delayBetweenWaves;
    bool _waitingForNextWave;
    Player* _playerRef;
    Vector2 _lastEnemyPosition;

public:
    WaveManager(Player* playerRef = nullptr)
        : _currentWave(nullptr),
        _delayTimer(0.f),
        _delayBetweenWaves(3.0f),
        _waitingForNextWave(false),
        _playerRef(playerRef),
        _lastEnemyPosition(0.f, 0.f) {
    }

    ~WaveManager() {
        while (!_waves.empty()) {
            delete _waves.front();
            _waves.pop();
        }

        if (_currentWave) {
            delete _currentWave;
        }
    }

    void AddWave(EnemyWave* wave) {
        _waves.push(wave);
    }

    bool LoadFromXML(const std::string& filepath) {
        LoadLevel loader;
        std::vector<int> waveOrder;
        std::vector<int> amountEnemies;

        std::string path = filepath;
        if (!loader.LoadFile(path, waveOrder, amountEnemies)) {
            std::cout << "Failed to load level from XML: " << filepath << std::endl;
            return false;
        }

        for (size_t i = 0; i < waveOrder.size(); i++) {
            int enemyId = waveOrder[i];
            int amount = amountEnemies[i];

            EnemyWave* wave = WaveFactory::CreateWave(enemyId, amount, _playerRef);

            if (wave) {
                _waves.push(wave);
            }
        }

        std::cout << "Loaded " << _waves.size() << " waves from XML" << std::endl;
        return true;
    }

    void Start() {
        if (!_waves.empty() && !_currentWave) {
            StartNextWave();
        }
    }

    void Update(float deltaTime) {
        if (_currentWave) {
            _currentWave->Update(deltaTime);

            // Trackear enemigos de la wave actual DESPUÉS de update
            CheckWaveCompletion();

            // Verificar si la wave terminó
            if (_currentWave->IsFinished()) {
                FinishCurrentWave();
            }
        }
        else if (_waitingForNextWave) {
            _delayTimer += deltaTime;

            if (_delayTimer >= _delayBetweenWaves) {
                _delayTimer = 0.f;
                _waitingForNextWave = false;

                if (!_waves.empty()) {
                    StartNextWave();
                }
                else {
                    std::cout << "All waves complete!" << std::endl;
                }
            }
        }
    }

    bool HasMoreWaves() const {
        return !_waves.empty();
    }

    bool IsLevelComplete() const {
        return _waves.empty() && (_currentWave == nullptr);
    }

    void SetPlayer(Player* player) {
        _playerRef = player;
    }

private:
    void StartNextWave() {
        if (_waves.empty()) return;

        _currentWave = _waves.front();
        _waves.pop();

        std::cout << "Starting wave..." << std::endl;

        _currentWave->Start();
    }

    void CheckWaveCompletion() {
        if (!_currentWave) return;

        const std::vector<Enemy*>& enemies = _currentWave->GetSpawnedEnemies();

        // Contar enemigos vivos y guardar posición del último
        int aliveCount = 0;
        Enemy* lastAlive = nullptr;

        for (Enemy* enemy : enemies) {
            if (!enemy->IsPendingDestroy()) {
                aliveCount++;
                lastAlive = enemy;
            }
        }

        // Si hay enemigos, guardar posición del último vivo
        if (lastAlive) {
            _lastEnemyPosition = lastAlive->GetTransform()->position;
        }
    }

    void FinishCurrentWave() {
        if (!_currentWave) return;

        std::cout << "Wave finished!" << std::endl;

        _currentWave->End();

        // Spawnear PowerUp en la posición del último enemigo
        SpawnPowerUp();

        delete _currentWave;
        _currentWave = nullptr;

        _waitingForNextWave = true;
        _delayTimer = 0.f;
    }

    void SpawnPowerUp() {
        // Verificar que la posición es válida (no usar 0,0 como condición)
        if (_lastEnemyPosition.x != 0.f || _lastEnemyPosition.y != 0.f) {
            PowerUp* powerUp = new PowerUp();
            powerUp->GetTransform()->position = _lastEnemyPosition;
            SPAWNER.SpawnObject(powerUp);

            std::cout << "PowerUp spawned at position ("
                << _lastEnemyPosition.x << ", "
                << _lastEnemyPosition.y << ")" << std::endl;

            _lastEnemyPosition = Vector2(0.f, 0.f);
        }
    }
};