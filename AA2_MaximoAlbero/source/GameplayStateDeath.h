#pragma once
#include "GameplayStateBase.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "TextObject.h"
#include <iostream>
#include <functional>
#include "ScoreManager.h"

class GameplayStateDeath : public GameplayStateBase {
private:
    float _deathTimer;
    bool _isInBlackScreen;
    bool _hasResetElements;
    bool _hasRespawned;

    Player* _player;
    TextObject* _deathText;

    std::function<void()> _onResetElements;
    std::function<void()> _onRespawnPlayer;

    const float DEATH_ANIMATION_TIME = 1.0f;
    const float BLACK_SCREEN_TIME = 2.0f;
    const float TOTAL_DEATH_TIME = DEATH_ANIMATION_TIME + BLACK_SCREEN_TIME;

public:
    GameplayStateDeath()
        : _deathTimer(0.0f), _isInBlackScreen(false),
        _hasResetElements(false), _hasRespawned(false),
        _player(nullptr), _deathText(nullptr) {
    }

    ~GameplayStateDeath() {
        if (_deathText) {
            delete _deathText;
        }
    }

    void Start() override {
        _deathTimer = 0.0f;
        _isInBlackScreen = false;
        _hasResetElements = false;
        _hasRespawned = false;

        // Decrementar vidas extra al empezar el estado de muerte
        if (_player) {
            int currentExtraLives = _player->GetExtraLives();
            if (currentExtraLives > 0) {
                _player->SetExtraLives(currentExtraLives - 1);
                std::cout << "Player died! Extra lives remaining: " << (currentExtraLives - 1) << std::endl;
            }
        }

        // Crear texto de muerte
        if (_deathText) {
            delete _deathText;
        }
        _deathText = new TextObject("Dead! Respawning...");
        _deathText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
        _deathText->GetTransform()->scale = Vector2(3.f, 3.f);
        _deathText->SetTextColor(SDL_Color{ 255, 255, 255, 255 });
    }

    void Update(float deltaTime) override {
        _deathTimer += deltaTime;

        // Pantalla negra
        if (_deathTimer >= DEATH_ANIMATION_TIME && !_isInBlackScreen) {
            _isInBlackScreen = true;
        }

        // Reset elementos
        if (_isInBlackScreen && !_hasResetElements) {
            if (_onResetElements) {
                _onResetElements();
            }
            _hasResetElements = true;
        }

        // Respawn
        if (_deathTimer >= (DEATH_ANIMATION_TIME + BLACK_SCREEN_TIME * 0.8f) &&
            _hasResetElements && !_hasRespawned) {
            if (_onRespawnPlayer) {
                _onRespawnPlayer();
            }
            _hasRespawned = true;
        }
    }

    void Render() override {
        if (_deathText) {
            _deathText->Render();
        }
    }

    bool IsFinished() const override {
        return _deathTimer >= TOTAL_DEATH_TIME;
    }

    int GetNextState() const override {
        return 0;  // PLAYING
    }

    void Finish() override {}

    bool ShouldUpdateScene() const override {
        return false;
    }

    void OnPlayerDeath(Player* player) override {
        _player = player;
    }

    void SetResetCallback(std::function<void()> callback) {
        _onResetElements = callback;
    }

    void SetRespawnCallback(std::function<void()> callback) {
        _onRespawnPlayer = callback;
    }
};