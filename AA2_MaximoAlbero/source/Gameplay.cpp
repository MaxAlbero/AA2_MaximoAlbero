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

// Implementación de los métodos de IGameplayContext
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
    // Inicializar nivel
    currentLevel = 1;
    maxLevel = 2;
    levelCompleted = false;

    // Crear estados
    gameplayStates.push_back(new GameplayStatePlaying());      // Índice 0
    gameplayStates.push_back(new GameplayStatePaused());       // Índice 1
    gameplayStates.push_back(new GameplayStateFinishWave());   // Índice 2
    gameplayStates.push_back(new GameplayStateDeath());        // Índice 3 (NUEVO)

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

    // Inicializar WaveManager
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
    Scene::OnExit();
}

void Gameplay::Update() {
    // Detectar muerte del player
    if (player && player->IsPendingDestroy() && currentStateIndex != 3) {
        currentState->Finish();
        currentStateIndex = 3;  // DEATH state
        currentState = gameplayStates[currentStateIndex];
        currentState->OnPlayerDeath(player);
        currentState->Start();
        return;
    }

    // Actualizar el estado actual
    currentState->Update(TM.GetDeltaTime());

    // Si el estado permite actualizar la escena
    if (currentState->ShouldUpdateScene()) {
        if (waveManager) {
            waveManager->Update(TM.GetDeltaTime());
        }
    }

    // Siempre limpiar objetos destruidos
    Scene::Update();

    // Si WaveManager indica que está esperando la siguiente wave
    if (!levelCompleted && waveManager && waveManager->IsWaitingForNextWave()) {
        if (currentStateIndex != 2) {
            currentState->Finish();
            currentStateIndex = 2;
            currentState = gameplayStates[currentStateIndex];
            currentState->Start();
        }
    }

    // Si el estado ha terminado, transicionar
    if (currentState->IsFinished()) {
        currentState->Finish();
        currentStateIndex = currentState->GetNextState();
        if (currentStateIndex >= 0 && currentStateIndex < static_cast<int>(gameplayStates.size())) {
            currentState = gameplayStates[currentStateIndex];
            currentState->Start();
        }
    }

    UpdateHUD();
}

void Gameplay::Render() {
    Scene::Render();
    currentState->Render();
}

void Gameplay::InitializeGameplayElements() {
    // Implementación existente
}

void Gameplay::RespawnPlayer() {
    if (!player) return;

    // El Death state ya decrementó las vidas
    int currentLives = player->GetExtraLives();

    // NO destruir, solo reemplazar el puntero
    player = new Player();
    player->SetExtraLives(currentLives);
    SPAWNER.SpawnObject(player);

    // Actualizar referencias
    if (waveManager) {
        waveManager->SetPlayer(player);
        waveManager->RestartCurrentWave();
    }
}

void Gameplay::ResetGameplayElements() {
    // Solo destruir enemigos y proyectiles
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

    std::cout << "Level " << currentLevel << " completed!" << std::endl;

    if (IsLastLevel()) {
        std::cout << "¡GAME COMPLETED!" << std::endl;
        SM.SetNextScene("GameOver");
        return;
    }

    currentLevel++;
    std::cout << "Transitioning to level " << currentLevel << std::endl;

    LoadLevel(currentLevel);
    waveManager->Start();

    if (player) {
        player->ResetPosition();
    }

    currentStateIndex = 0;
    currentState = gameplayStates[currentStateIndex];
    currentState->Start();
}