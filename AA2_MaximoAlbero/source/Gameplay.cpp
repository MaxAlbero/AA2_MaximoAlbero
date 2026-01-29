#include "Gameplay.h"
#include "RenderManager.h"
#include "ScoreManager.h"
#include "TimeManager.h"
#include "Background.h"
#include "PowerUp.h"
#include "Bubbles.h"
#include "GameplayStateFinishWave.h"
#include <cassert>

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
    // Crear estados: PLAYING (0), PAUSED (1), FINISH_WAVE (2)
    gameplayStates.push_back(new GameplayStatePlaying());   // índice 0
    gameplayStates.push_back(new GameplayStatePaused());    // índice 1
    gameplayStates.push_back(new GameplayStateFinishWave(this)); // índice 2

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

    // Inicializar WaveManager y cargar nivel (XML)
    waveManager = new WaveManager(player);
    waveManager->SetPlayer(player);
    if (!waveManager->LoadFromXML("resources/level_1.xml")) {
        // Intento alternativo si la ruta anterior no existe
        waveManager->LoadFromXML("level_1.xml");
    }
    waveManager->Start();

    InitializeGameplayElements();
}

void Gameplay::OnExit() {
    Scene::OnExit();
}

void Gameplay::Update() {
    // Actualizar el estado actual (input / lógica de transición)
    currentState->Update(TM.GetDeltaTime());

    // Si el estado permite actualizar la escena, actualizamos el WaveManager y la escena.
    if (currentState->ShouldUpdateScene()) {
        if (waveManager) {
            waveManager->Update(TM.GetDeltaTime());
        }

        // Actualizar escena (enemigos, balas, etc.)
        Scene::Update();
    } else {
        // Aunque la escena esté congelada, seguimos pudiendo detectar que waveManager
        // está en modo "waiting" (es decir, la wave acaba de terminar) y debemos
        // asegurarnos de entrar en el estado FINISH_WAVE exactamente cuando toque.
        // Sin embargo, waveManager->Update() se llama solo cuando ShouldUpdateScene()==true,
        // por lo que la bandera de waiting se establece antes de que el estado se convierta en FINISH_WAVE.
    }

    // Si WaveManager indica que está esperando la siguiente wave, y no estamos ya en FINISH_WAVE,
    // forzamos la transición al estado FINISH_WAVE.
    if (waveManager && waveManager->IsWaitingForNextWave()) {
        // Evitar sobrescribir si ya estamos en FINISH_WAVE
        if (currentStateIndex != 2) {
            currentState->Finish();
            currentStateIndex = 2;
            if (currentStateIndex >= 0 && currentStateIndex < static_cast<int>(gameplayStates.size())) {
                currentState = gameplayStates[currentStateIndex];
                currentState->Start();
            }
        }
    }

    // Si el estado ha terminado, transicionar (esto cubre pausado -> playing, finish_wave -> playing, etc.)
    if (currentState->IsFinished()) {
        currentState->Finish();
        currentStateIndex = currentState->GetNextState();
        if (currentStateIndex >= 0 && currentStateIndex < static_cast<int>(gameplayStates.size())) {
            currentState = gameplayStates[currentStateIndex];
            currentState->Start();
        }
    }

    // El HUD se actualiza siempre
    UpdateHUD();
}

void Gameplay::UpdateGameplay() {
    // SOLO se llama desde GameplayStatePlaying
    Scene::Update();
}

void Gameplay::Render() {
    // Renderizar objetos de la escena (sin estado)
    Scene::Render();
    // Renderizar lo específico del estado
    currentState->Render();
}

void Gameplay::InitializeGameplayElements() {
    PowerUp* s1 = new PowerUp();
    s1->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f, RM->WINDOW_HEIGHT / 2.0f);
    PowerUp* s2 = new PowerUp();
    s2->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 1.5f, RM->WINDOW_HEIGHT / 2.0f);
    PowerUp* s3 = new PowerUp();
    s3->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.0f, RM->WINDOW_HEIGHT / 1.5f);
    PowerUp* s4 = new PowerUp();
    s4->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 1.5f, RM->WINDOW_HEIGHT / 1.5f);
    SPAWNER.SpawnObject(s1);
    SPAWNER.SpawnObject(s2);
    SPAWNER.SpawnObject(s3);
    SPAWNER.SpawnObject(s4);

    Bubbles* bubble = new Bubbles(TOP_TO_BOTTOM);
    SPAWNER.SpawnObject(bubble);
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