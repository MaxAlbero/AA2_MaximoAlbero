#include "Gameplay.h"
#include "RenderManager.h"
#include "ScoreManager.h"
#include "TimeManager.h"
#include "Background.h"
#include "PowerUp.h"
#include "Bubbles.h"
#include "SceneManager.h"
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
    maxLevel = 2;  // Tenemos 2 niveles
    levelCompleted = false;  // NUEVO

    // Crear estados: PLAYING (0), PAUSED (1), FINISH_WAVE (2)
    gameplayStates.push_back(new GameplayStatePlaying());
    gameplayStates.push_back(new GameplayStatePaused());
    gameplayStates.push_back(new GameplayStateFinishWave());

    // Pasar el contexto al estado FinishWave
    GameplayStateFinishWave* finishWaveState =
        dynamic_cast<GameplayStateFinishWave*>(gameplayStates[2]);
    if (finishWaveState) {
        finishWaveState->SetContext(this);
    }

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

    // Inicializar WaveManager y cargar nivel actual
    waveManager = new WaveManager(player);
    waveManager->SetPlayer(player);
    LoadLevel(currentLevel);
    waveManager->Start();

    InitializeGameplayElements();
}

void Gameplay::OnExit() {
    Scene::OnExit();
}

void Gameplay::Update() {
    // Actualizar el estado actual (input / lógica de transición)
    currentState->Update(TM.GetDeltaTime());

    // Si el estado permite actualizar la escena
    if (currentState->ShouldUpdateScene()) {
        if (waveManager) {
            waveManager->Update(TM.GetDeltaTime());
        }
        Scene::Update();
    }

    // Si WaveManager indica que está esperando la siguiente wave
    // (pero SOLO si el nivel no está completado)
    if (!levelCompleted && waveManager && waveManager->IsWaitingForNextWave()) {
        if (currentStateIndex != 2) {
            currentState->Finish();
            currentStateIndex = 2;
            if (currentStateIndex >= 0 && currentStateIndex < static_cast<int>(gameplayStates.size())) {
                currentState = gameplayStates[currentStateIndex];
                currentState->Start();
            }
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

void Gameplay::UpdateGameplay() {
    Scene::Update();
}

void Gameplay::Render() {
    Scene::Render();
    currentState->Render();
}

void Gameplay::InitializeGameplayElements() {
    // Implementación existente
}

void Gameplay::UpdateHUD() {
    if (!player) return;

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

    std::string cannonStr = "CANNON: " + std::to_string(player->GetCannonAmmo());
    cannonText->SetText(cannonStr);

    std::string laserStr = "LASER: " + std::to_string(player->GetLaserAmmo());
    laserText->SetText(laserStr);
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
    // Construir el path del nivel
    std::stringstream ss;
    ss << "resources/level_" << levelNumber << ".xml";
    std::string levelPath = ss.str();

    // Si el WaveManager ya existe, lo limpiamos
    if (waveManager) {
        delete waveManager;
    }

    // Crear nuevo WaveManager y cargar el nivel
    // NUEVO: pasar levelNumber al constructor
    waveManager = new WaveManager(player, levelNumber);
    waveManager->SetPlayer(player);

    if (!waveManager->LoadFromXML(levelPath)) {
        // Intento alternativo sin "resources/"
        ss.str("");
        ss << "level_" << levelNumber << ".xml";
        levelPath = ss.str();
        waveManager->LoadFromXML(levelPath);
    }

    std::cout << "Loaded level " << levelNumber << std::endl;
    levelCompleted = false;
}

void Gameplay::TransitionToNextLevel() {
    // Marcar el nivel como completado para evitar el bucle
    levelCompleted = true;

    std::cout << "Level " << currentLevel << " completed!" << std::endl;

    // Verificar si hay más niveles
    if (IsLastLevel()) {
        // Ir a pantalla de game over / high scores
        std::cout << "¡GAME COMPLETED! Mostrar pantalla de fin del juego." << std::endl;
        SM.SetNextScene("GameOver");
        return;
    }

    // Incrementar nivel y cargar el siguiente
    currentLevel++;
    std::cout << "Transitioning to level " << currentLevel << std::endl;

    // Cargar el nuevo nivel
    LoadLevel(currentLevel);
    waveManager->Start();

    // Reiniciar los estados (sin resetear el jugador)
    currentStateIndex = 0;
    currentState = gameplayStates[currentStateIndex];
    currentState->Start();

    // Opcionalmente: resetear vidas del jugador o mantenerlas
    // player->ResetPosition();  // Si tienes este método
}