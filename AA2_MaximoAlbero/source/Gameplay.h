// (VERSIÓN ACTUALIZADA CON STATE MACHINE)
#pragma once
#include "TextObject.h"
#include "Scene.h"
#include "Player.h"
#include "GameplayStateBase.h"
#include "GameplayStatePlaying.h"
#include "GameplayStatePaused.h"
#include "WaveManager.h"
#include <vector>

// Forward declaration para romper dependencias circulares
class GameplayStateFinishWave;

class Gameplay : public Scene {
private:
    Player* player;
    std::vector<GameplayStateBase*> gameplayStates;
    GameplayStateBase* currentState;
    int currentStateIndex;

    TextObject* scoreText;
    TextObject* highScoreText;
    TextObject* extraLivesText;
    TextObject* shieldText;
    TextObject* cannonText;
    TextObject* laserText;

    void UpdateHUD();
    std::string FormatScore(int score);
    void InitializeGameplayElements();

    int currentWaveIndex;
    int totalWaves;
    std::vector<int> waveEnemyIds;
    std::vector<int> waveAmounts;

    WaveManager* waveManager;

public:
    Gameplay() = default;
    ~Gameplay();

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;

    // Getters para que los estados accedan
    Player* GetPlayer() { return player; }

    // Nueva: método para actualizar solo la escena (llamado solo desde PLAYING)
    void UpdateGameplay();

    // Wrapper para que los estados puedan consultar/forzar waves
    bool HasMoreWaves() const { return waveManager ? waveManager->HasMoreWaves() : false; }
    bool IsLevelComplete() const { return waveManager ? waveManager->IsLevelComplete() : true; }
    void ForceStartNextWave() { if (waveManager) waveManager->StartNextWaveImmediate(); }
};