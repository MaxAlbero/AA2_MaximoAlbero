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

public:
    WaveManager(Player* playerRef = nullptr)
        : _currentWave(nullptr),
        _delayTimer(0.f),
        _delayBetweenWaves(3.0f),
        _waitingForNextWave(false),
        _playerRef(playerRef) {
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

    // Añadir una wave manualmente
    void AddWave(EnemyWave* wave) {
        _waves.push(wave);
    }

    // Cargar waves desde XML
    bool LoadFromXML(const std::string& filepath) {
        LoadLevel loader;
        std::vector<int> waveOrder;
        std::vector<int> amountEnemies;

        std::string path = filepath;
        if (!loader.LoadFile(path, waveOrder, amountEnemies)) {
            std::cout << "Failed to load level from XML: " << filepath << std::endl;
            return false;
        }

        // Crear waves usando el factory
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

    // Iniciar el sistema de waves
    void Start() {
        if (!_waves.empty() && !_currentWave) {
            StartNextWave();
        }
    }

    // Actualizar
    void Update(float deltaTime) {
        if (_currentWave) {
            _currentWave->Update(deltaTime);

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
            }
        }
    }

    bool HasMoreWaves() const {
        return !_waves.empty();
    }

    bool IsLevelComplete() const {
        return _waves.empty() && (_currentWave == nullptr || _currentWave->IsFinished());
    }

    void SetPlayer(Player* player) {
        _playerRef = player;
    }

private:
    void StartNextWave() {
        if (_waves.empty()) return;

        _currentWave = _waves.front();
        _waves.pop();

        _currentWave->Start();
        WM->SetWaveActive(true);
    }

    void FinishCurrentWave() {
        if (!_currentWave) return;

        _currentWave->End();
        WM->SpawnPowerUp();

        delete _currentWave;
        _currentWave = nullptr;

        WM->SetWaveActive(false);
        _waitingForNextWave = true;
    }
};