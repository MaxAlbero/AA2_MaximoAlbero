#pragma once
#include "EnemyWave.h"
#include "WaveFactory.h"
#include "LoadLevel.h"
#include "PowerUp.h"
#include "Player.h"
#include "RenderManager.h"
#include <queue>
#include <string>
#include <iostream>

class WaveManager {
private:
    std::queue<EnemyWave*> _waves;
    EnemyWave* _currentWave;
    float _delayTimer;
    float _delayBetweenWaves;  // Delay después de terminar una wave
    bool _waitingForNextWave;
    Player* _playerRef;
    Vector2 _lastEnemyPosition;
    int _currentLevel;

public:
    WaveManager(Player* playerRef = nullptr, int levelNumber = 1)
        : _currentWave(nullptr),
        _delayTimer(0.f),
        _delayBetweenWaves(5.0f),  // CAMBIO: aumentar a 2 segundos (era 3.0f)
        _waitingForNextWave(false),
        _playerRef(playerRef),
        _lastEnemyPosition(0.f, 0.f),
        _currentLevel(levelNumber) {
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

            EnemyWave* wave = WaveFactory::CreateWave(enemyId, amount, _playerRef, _currentLevel);

            if (wave) {
                _waves.push(wave);
            }
        }

        std::cout << "Loaded " << _waves.size() << " waves from level " << _currentLevel << std::endl;
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

            CheckWaveCompletion();

            if (_currentWave->IsFinished()) {
                FinishCurrentWave();
            }
        }
        else if (_waitingForNextWave) {
            _delayTimer += deltaTime;

            // Cuando el delay termina, iniciar la siguiente wave
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

    bool IsWaitingForNextWave() const {
        return _waitingForNextWave;
    }

    void StartNextWaveImmediate() {
        if (_currentWave) return;
        if (_waves.empty()) return;

        _currentWave = _waves.front();
        _waves.pop();

        std::cout << "Starting wave (forced)..." << std::endl;

        _currentWave->Start();

        _waitingForNextWave = false;
        _delayTimer = 0.f;
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

        int aliveCount = 0;
        Enemy* lastAlive = nullptr;

        for (Enemy* enemy : enemies) {
            if (!enemy) continue;
            Transform* t = enemy->GetTransform();
            if (t && !enemy->IsPendingDestroy()) {
                aliveCount++;
                lastAlive = enemy;
            }
        }

        if (lastAlive) {
            Transform* t = lastAlive->GetTransform();
            if (t) {
                _lastEnemyPosition = t->position;
            }
            else {
                _lastEnemyPosition = Vector2(0.f, 0.f);
            }
        }
    }

    void FinishCurrentWave() {
        if (!_currentWave) return;

        std::cout << "Wave finished! Waiting " << _delayBetweenWaves << " seconds before next wave..." << std::endl;

        _currentWave->End();

        SpawnPowerUp();

        delete _currentWave;
        _currentWave = nullptr;

        _waitingForNextWave = true;
        _delayTimer = 0.f;
    }

    void SpawnPowerUp() {
        if (_lastEnemyPosition.x == 0.f && _lastEnemyPosition.y == 0.f) {
            return;
        }

        if (RM == nullptr) {
            std::cout << "RenderManager not available – skipping PowerUp spawn." << std::endl;
            _lastEnemyPosition = Vector2(0.f, 0.f);
            return;
        }

        const float px = _lastEnemyPosition.x;
        const float py = _lastEnemyPosition.y;

        if (px >= 0.f && px <= static_cast<float>(RM->WINDOW_WIDTH) &&
            py >= 0.f && py <= static_cast<float>(RM->WINDOW_HEIGHT)) {

            PowerUp* powerUp = new PowerUp();
            powerUp->GetTransform()->position = _lastEnemyPosition;
            SPAWNER.SpawnObject(powerUp);

            std::cout << "PowerUp spawned at position ("
                << _lastEnemyPosition.x << ", "
                << _lastEnemyPosition.y << ")" << std::endl;
        }
        else {
            std::cout << "Last enemy position out of screen bounds – not spawning PowerUp ("
                << px << ", " << py << ")." << std::endl;
        }

        _lastEnemyPosition = Vector2(0.f, 0.f);
    }
};