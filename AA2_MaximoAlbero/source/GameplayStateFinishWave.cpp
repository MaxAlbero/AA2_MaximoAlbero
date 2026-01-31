#include "GameplayStateFinishWave.h"
#include "InputManager.h"
#include "ScoreManager.h"
#include "Player.h"
#include "TextObject.h"
#include <iostream>
#include <sstream>

GameplayStateFinishWave::GameplayStateFinishWave()
    : _context(nullptr), _finished(false), _nextState(-1),
    _displayTimer(0.f), _displayDuration(2.0f), _isLastWave(false),
    _isLevelComplete(false), _levelCompleteText(nullptr),
    _bonusPointsText(nullptr), _continueText(nullptr),
    _bossDefeatText(nullptr), _isBossDefeated(false), _bonusPoints(0) {
}

GameplayStateFinishWave::~GameplayStateFinishWave() {
    if (_levelCompleteText) delete _levelCompleteText;
    if (_bonusPointsText) delete _bonusPointsText;
    if (_continueText) delete _continueText;
    if (_bossDefeatText) delete _bossDefeatText;
}

void GameplayStateFinishWave::Start() {
    _finished = false;
    _nextState = -1;
    _displayTimer = 0.f;
    _isBossDefeated = false;

    // Limpiar textos anteriores
    if (_levelCompleteText) delete _levelCompleteText;
    if (_bonusPointsText) delete _bonusPointsText;
    if (_continueText) delete _continueText;
    if (_bossDefeatText) delete _bossDefeatText;
    _levelCompleteText = nullptr;
    _bonusPointsText = nullptr;
    _continueText = nullptr;
    _bossDefeatText = nullptr;

    // Verificar si es la última wave
    _isLastWave = (_context == nullptr) ? false : !_context->HasMoreWaves();

    // Si es la última wave, es fin de nivel
    _isLevelComplete = _isLastWave;

    if (_isLevelComplete) {
        std::cout << "¡NIVEL COMPLETADO!" << std::endl;

        // Calcular puntos bonus por vidas restantes
        CalculateBonusPoints();

        // Crear textos para la pantalla de fin de nivel
        _levelCompleteText = new TextObject("LEVEL COMPLETE!");
        _levelCompleteText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 4.f);
        _levelCompleteText->SetTextColor(SDL_Color{ 255, 215, 0, 255 });

        // Texto con los puntos bonus
        std::stringstream ss;
        ss << "BONUS: +" << _bonusPoints << " PTS";
        _bonusPointsText = new TextObject(ss.str());
        _bonusPointsText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f - 50.f);
        _bonusPointsText->SetTextColor(SDL_Color{ 100, 255, 100, 255 });

        // Texto adicional con info de vidas
        std::stringstream ss2;
        int extraLives = _context ? (_context->GetPlayer() ? _context->GetPlayer()->GetExtraLives() : 0) : 0;
        ss2 << "+" << (10000) << " per life x " << extraLives;
        _continueText = new TextObject(ss2.str());
        _continueText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
        _continueText->SetTextColor(SDL_Color{ 150, 150, 150, 255 });

        _bossDefeatText = new TextObject("Press SPACE to continue...");
        _bossDefeatText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT * 3.f / 4.f);
        _bossDefeatText->SetTextColor(SDL_Color{ 200, 200, 200, 255 });
        _isBossDefeated = true;
    }
    else {
        std::cout << "¡OLEADA COMPLETADA!" << std::endl;
    }
}

void GameplayStateFinishWave::Update(float deltaTime) {
    _displayTimer += deltaTime;

    if (_isLevelComplete) {
        if (_isBossDefeated && (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) || IM->GetLeftClick())) {
            TransitionToVictory();
        }
    }
    else if (_isLastWave) {
        // Last wave but not level complete (shouldn't happen)
        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) ||
            IM->GetLeftClick() ||
            _displayTimer >= 5.0f) {
            TransitionToVictory();
        }
    }
    else {
        ContinueToNextWave();
    }
}

void GameplayStateFinishWave::Render() {
    if (_isLevelComplete) {
        if (_levelCompleteText) _levelCompleteText->Render();
        if (_bonusPointsText) _bonusPointsText->Render();
        if (_continueText) _continueText->Render();
        if (_bossDefeatText) _bossDefeatText->Render();  // NEW: Render boss defeat text
    }
}

bool GameplayStateFinishWave::IsFinished() const {
    return _finished;
}

int GameplayStateFinishWave::GetNextState() const {
    return _nextState;
}

void GameplayStateFinishWave::Finish() {
    std::cout << "Saliendo de FINISH_WAVE" << std::endl;
}

bool GameplayStateFinishWave::ShouldUpdateScene() const {
    return false;
}

void GameplayStateFinishWave::ContinueToNextWave() {
    if (_context) {
        _context->StartNextWave();
    }
    _finished = true;
    _nextState = 0; // volver a PLAYING
}

void GameplayStateFinishWave::TransitionToVictory() {
    if (_isLevelComplete && _context && _context->GetPlayer()) {
        HSM->AddPoints(_bonusPoints);
        std::cout << "Bonus points awarded: " << _bonusPoints << std::endl;

        // Only request level transition if it's truly the last wave
        if (_context) {
            _context->RequestLevelTransition();
        }
    }

    _finished = true;
    _nextState = 0;  // Back to PLAYING
}

void GameplayStateFinishWave::CalculateBonusPoints() {
    if (!_context || !_context->GetPlayer()) {
        _bonusPoints = 0;
        return;
    }

    Player* player = _context->GetPlayer();
    int extraLives = player->GetExtraLives();

    _bonusPoints = extraLives * 10000;
}