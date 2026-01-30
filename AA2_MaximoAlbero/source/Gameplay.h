#pragma once
#include "TextObject.h"
#include "Scene.h"
#include "Player.h"
#include "GameplayStateBase.h"
#include "GameplayStatePlaying.h"
#include "GameplayStatePaused.h"
#include "GameplayStateFinishWave.h"
#include "GameplayStateDeath.h"
#include "IGameplayContext.h"
#include "WaveManager.h"
#include <vector>

class Gameplay : public Scene, public IGameplayContext {
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

    // NUEVOS: Métodos para reset y respawn
    void ResetGameplayElements();
    void RespawnPlayer();

    WaveManager* waveManager;
    int currentLevel;
    int maxLevel;
    bool levelCompleted;

public:
    Gameplay() = default;
    ~Gameplay();

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;

    Player* GetPlayer() override { return player; }
    void UpdateGameplay();

    bool HasMoreWaves() const override;
    void StartNextWave() override;
    bool IsLastLevel() const override;
    int GetCurrentLevel() const override;
    bool IsLevelComplete() const override;

    void LoadLevel(int levelNumber);
    void TransitionToNextLevel() override;
};