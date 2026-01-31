#include "Gameplay.h"
#include "RenderManager.h"
#include "ScoreManager.h"
#include "TimeManager.h"
#include "Background.h"
#include "PowerUp.h"
#include "Bubbles.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include <cassert>
#include <sstream>
#include <iostream>

bool Gameplay::HasMoreWaves() const {
    return waveManager ? waveManager->HasMoreWaves() : false;
}

void Gameplay::StartNextWave() {
    if (waveManager) waveManager->StartNextWaveImmediate();
}

bool Gameplay::IsLastLevel() const {
    return currentLevel >= maxLevel;
}

int Gameplay::GetCurrentLevel() const {
    return currentLevel;
}

bool Gameplay::IsLevelComplete() const {
    return levelCompleted;
}

Gameplay::~Gameplay() {
    for (auto state : gameplayStates) {
        delete state;
    }
    gameplayStates.clear();
    currentState = nullptr;

    if (waveManager) {
        delete waveManager;
        waveManager = nullptr;
    }
}

void Gameplay::OnEnter() {
    // Obtener el nivel seleccionado del LevelManager
    int selectedLevelIndex = LM->GetCurrentLevelIndex();
    currentLevel = selectedLevelIndex + 1;  // +1 porque levelNumber comienza en 1

    // maxLevel es el total de niveles disponibles
    maxLevel = LM->GetLevelCount();

    levelCompleted = false;
    previousStateIndex = -1;
    shouldTransitionLevel = false;

    gameplayStates.push_back(new GameplayStatePlaying());
    gameplayStates.push_back(new GameplayStatePaused());
    gameplayStates.push_back(new GameplayStateFinishWave());
    gameplayStates.push_back(new GameplayStateDeath());

    currentStateIndex = 0;
    currentState = gameplayStates[currentStateIndex];
    currentState->Start();

    // Inicializar HUD
    float hudX = 60.f;
    float hudY = RM->WINDOW_HEIGHT - 60.f;
    float spacing = 300.f;

    scoreText = new TextObject("SCORE: ");
    scoreText->GetTransform()->position = Vector2(hudX, hudY);
    scoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(scoreText);

    highScoreText = new TextObject("HIGHSCORE: ");
    highScoreText->GetTransform()->position = Vector2(hudX, hudY - 30.f);
    highScoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(highScoreText);

    extraLivesText = new TextObject("LIVES: ");
    extraLivesText->GetTransform()->position = Vector2(hudX + spacing, hudY);
    extraLivesText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(extraLivesText);

    shieldText = new TextObject("SHIELD: ");
    shieldText->GetTransform()->position = Vector2(hudX + spacing * 2, hudY);
    shieldText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(shieldText);

    cannonText = new TextObject("CANNON: NO");
    cannonText->GetTransform()->position = Vector2(hudX + spacing * 3, hudY);
    cannonText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(cannonText);

    laserText = new TextObject("LASER: NO");
    laserText->GetTransform()->position = Vector2(hudX + spacing * 4, hudY);
    laserText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    _ui.push_back(laserText);

    Background* bg1 = new Background();
    bg1->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);
    Background* bg2 = new Background();
    bg2->GetTransform()->position = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);
    SPAWNER.SpawnObject(bg1);
    SPAWNER.SpawnObject(bg2);

    player = new Player();
    SPAWNER.SpawnObject(player);

    GameplayStateFinishWave* finishState = dynamic_cast<GameplayStateFinishWave*>(gameplayStates[2]);
    if (finishState) {
        std::cout << "Setting context for FinishWave state" << std::endl;
        finishState->SetContext(this);
    }
    else {
        std::cout << "ERROR: Could not cast to GameplayStateFinishWave!" << std::endl;
    }

    waveManager = new WaveManager(player, currentLevel);
    waveManager->SetPlayer(player);
    LoadLevel(currentLevel);
    waveManager->Start();

    InitializeGameplayElements();

    GameplayStateDeath* deathState = dynamic_cast<GameplayStateDeath*>(gameplayStates[3]);
    if (deathState) {
        deathState->SetResetCallback([this]() { ResetGameplayElements(); });
        deathState->SetRespawnCallback([this]() { RespawnPlayer(); });
    }
}

void Gameplay::OnExit() {
    scoreText = nullptr;
    highScoreText = nullptr;
    extraLivesText = nullptr;
    shieldText = nullptr;
    cannonText = nullptr;
    laserText = nullptr;

    Scene::OnExit();
}

void Gameplay::Update() {
    if (player && player->IsPendingDestroy() && currentStateIndex != 3) {
        currentState->Finish();
        currentStateIndex = 3;
        currentState = gameplayStates[currentStateIndex];
        currentState->OnPlayerDeath(player);
        currentState->Start();
        return;
    }

    currentState->Update(TM.GetDeltaTime());

    if (currentState->ShouldUpdateScene()) {
        if (waveManager) {
            waveManager->Update(TM.GetDeltaTime());
        }

        Scene::Update();  // Only update scene objects when not paused
    }

    // Detectar cuando WaveManager dice que está esperando la siguiente wave
    if (!levelCompleted && waveManager && waveManager->IsWaitingForNextWave()) {
        if (currentStateIndex != 2) {  // Si NO estamos ya en FinishWave
            std::cout << " Entering FINISH_WAVE state" << std::endl;
            currentState->Finish();
            currentStateIndex = 2;
            currentState = gameplayStates[currentStateIndex];
            currentState->Start();
        }
    }

    previousStateIndex = currentStateIndex;

    if (currentState->IsFinished()) {
        std::cout << "State is finished. Current state index: " << currentStateIndex << std::endl;
        currentState->Finish();
        currentStateIndex = currentState->GetNextState();

        if (currentStateIndex >= 0 && currentStateIndex < static_cast<int>(gameplayStates.size())) {
            std::cout << "Transitioning to state: " << currentStateIndex << std::endl;
            currentState = gameplayStates[currentStateIndex];
            currentState->Start();
        }
    }

    // Detectar transición de nivel limpiamente
    if (previousStateIndex == 2 && currentStateIndex == 0 && shouldTransitionLevel) {
        shouldTransitionLevel = false;
        TransitionToNextLevel();
        return;
    }

    UpdateHUD();
}

void Gameplay::Render() {
    if (currentState && currentState->ShouldUpdateScene()) {
        if (player) {
            player->Render();
        }
        Scene::Render();
    }

    if (currentState) {
        currentState->Render();
    }
}

void Gameplay::InitializeGameplayElements() {
}

void Gameplay::RespawnPlayer() {
    if (!player) return;

    int currentLives = player->GetExtraLives();
    player = new Player();
    player->SetExtraLives(currentLives);
    SPAWNER.SpawnObject(player);

    if (waveManager) {
        waveManager->SetPlayer(player);
        waveManager->RestartCurrentWave();
    }
}

void Gameplay::ResetGameplayElements() {
    for (int i = _objects.size() - 1; i >= 0; i--) {
        Object* obj = _objects[i];
        if (dynamic_cast<Enemy*>(obj) != nullptr ||
            dynamic_cast<EnemyBullet*>(obj) != nullptr) {
            obj->Destroy();
        }
    }
}

void Gameplay::UpdateHUD() {
    if (!player || player->IsPendingDestroy()) {
        return;
    }

    int currentScore = HSM->GetCurrentScore();
    bool isNewHighScore = (currentScore >= HSM->GetHighScore());

    if (isNewHighScore) {
        scoreText->SetTextColor(SDL_Color{ 255, 215, 0, 255 });
    }
    else {
        scoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
    }

    std::string scoreStr = FormatScore(currentScore);
    scoreText->SetText("SCORE: " + scoreStr);

    int highScore = HSM->GetHighScore();
    std::string highScoreStr = FormatScore(highScore);
    highScoreText->SetText("HIGHSCORE: " + highScoreStr);

    std::string livesStr = "LIVES: " + std::to_string(player->GetExtraLives());
    extraLivesText->SetText(livesStr);

    std::string shieldStr = "SHIELD: " + std::to_string(player->GetEnergy());
    shieldText->SetText(shieldStr);

    if (player->HasCannon()) {
        std::string cannonStr = "CANNON: " + std::to_string(player->GetCannonAmmo());
        cannonText->SetText(cannonStr);
    }
    else {
        cannonText->SetText("CANNON: NO");
    }

    if (player->HasLaser()) {
        std::string laserStr = "LASER: " + std::to_string(player->GetLaserAmmo());
        laserText->SetText(laserStr);
    }
    else {
        laserText->SetText("LASER: NO");
    }
}

std::string Gameplay::FormatScore(int score) {
    std::string scoreStr = std::to_string(score);
    if (scoreStr.length() > 6) {
        scoreStr = scoreStr.substr(scoreStr.length() - 6);
    }
    else {
        scoreStr = std::string(6 - scoreStr.length(), '0') + scoreStr;
    }
    return scoreStr;
}

void Gameplay::LoadLevel(int levelNumber) {
    std::stringstream ss;
    ss << "resources/level_" << levelNumber << ".xml";
    std::string levelPath = ss.str();

    if (waveManager) {
        delete waveManager;
    }

    waveManager = new WaveManager(player, levelNumber);
    waveManager->SetPlayer(player);

    if (!waveManager->LoadFromXML(levelPath)) {
        ss.str("");
        ss << "level_" << levelNumber << ".xml";
        levelPath = ss.str();
        waveManager->LoadFromXML(levelPath);
    }

    std::cout << "Loaded level " << levelNumber << std::endl;
    levelCompleted = false;
}

void Gameplay::TransitionToNextLevel() {
    levelCompleted = true;

    std::cout << "TransitionToNextLevel called. Current level: " << currentLevel << ", Max level: " << maxLevel << std::endl;

    if (IsLastLevel()) {
        int finalScore = HSM->GetCurrentScore();
        std::cout << "Last level reached! Final score: " << finalScore << std::endl;

        if (HSM->IsInTopTen(finalScore)) {
            SM.SetNextScene("NameInput");
        }
        else {
            SM.SetNextScene("MainMenu");
        }
        return;
    }

    currentLevel++;
    std::cout << "Loading level " << currentLevel << std::endl;
    LoadLevel(currentLevel);
    waveManager->Start();

    if (player) {
        player->ResetPosition();
        player->RestoreFullEnergy();
        player->SetExtraLives(3);
    }

    HSM->ResetCurrentScore();

    currentStateIndex = 0;
    currentState = gameplayStates[currentStateIndex];
    currentState->Start();

    std::cout << "Level transition complete!" << std::endl;
}