#include "Gameplay.h"
#include "RenderManager.h"
#include "ScoreManager.h"
#include "TimeManager.h"
#include "Background.h"
#include "PowerUp.h"
// ... otros includes de enemigos

Gameplay::~Gameplay() {
    // Limpiar estados
    for (auto state : gameplayStates) {
        delete state;
    }
    gameplayStates.clear();
    currentState = nullptr;
}

void Gameplay::OnEnter() {
    // Crear y registrar los estados
    gameplayStates.push_back(new GameplayStatePlaying());   // índice 0
    gameplayStates.push_back(new GameplayStatePaused());    // índice 1

    // Iniciar con el estado PLAYING
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

    // Inicializar background
    Background* bg1 = new Background();
    bg1->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);
    Background* bg2 = new Background();
    bg2->GetTransform()->position = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);
    SPAWNER.SpawnObject(bg1);
    SPAWNER.SpawnObject(bg2);

    // Crear player
    player = new Player();
    SPAWNER.SpawnObject(player);

    // Inicializar elementos del gameplay (powerups, enemigos, etc.)
    InitializeGameplayElements();
}

void Gameplay::OnExit() {
    Scene::OnExit();
}

void Gameplay::Update() {
    // Actualizar el estado actual
    currentState->Update(TM.GetDeltaTime());

    // Si el estado ha terminado, transicionar
    if (currentState->IsFinished()) {
        currentState->Finish();
        currentStateIndex = currentState->GetNextState();
        currentState = gameplayStates[currentStateIndex];
        currentState->Start();
    }

    // Actualizar escena (enemigos, balas, etc.) SIEMPRE
    // pero el estado PAUSED no debería llamar a esto
    // Para ello, modifica GameplayStatePlaying para que llame a Scene::Update()
    // y GameplayStatePaused NO lo hace

    // Por ahora, dejamos que Scene::Update() se ejecute siempre
    Scene::Update();
    UpdateHUD();
}

void Gameplay::Render() {
    currentState->Render();
    Scene::Render();
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

    // Añadir enemigos aquí
    // Circler* circler = new Circler();
    // SPAWNER.SpawnObject(circler);
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