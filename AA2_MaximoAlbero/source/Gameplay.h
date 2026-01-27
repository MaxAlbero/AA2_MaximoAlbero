// (VERSIÓN ACTUALIZADA CON STATE MACHINE)
#pragma once
#include "TextObject.h"
#include "Scene.h"
#include "Player.h"
#include "GameplayStateBase.h"
#include "GameplayStatePlaying.h"
#include "GameplayStatePaused.h"
#include <vector>

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
    void InitializeGameplayElements(); // nueva: setup de enemigos, powerups, etc.

public:
    Gameplay() = default;
    ~Gameplay();

    void OnEnter() override;
    void OnExit() override;
    void Update() override;
    void Render() override;

    // Getters para que los estados accedan
    Player* GetPlayer() { return player; }
};