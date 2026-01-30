#pragma once
#include "GameplayStateBase.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include <iostream>
#include <functional>

class GameplayStateDeath : public GameplayStateBase {
private:
    float _deathTimer;
    bool _isInBlackScreen;
    bool _hasDecrementedLives;
    bool _hasResetElements;
    bool _hasRespawned;

    Player* _player;

    std::function<void()> _onResetElements;
    std::function<void()> _onRespawnPlayer;

    const float DEATH_ANIMATION_TIME = 1.0f;
    const float BLACK_SCREEN_TIME = 2.0f;
    const float TOTAL_DEATH_TIME = DEATH_ANIMATION_TIME + BLACK_SCREEN_TIME;

public:
    GameplayStateDeath()
        : _deathTimer(0.0f), _isInBlackScreen(false),
        _hasDecrementedLives(false), _hasResetElements(false), _hasRespawned(false),
        _player(nullptr) {
    }

    void Start() override {
        _deathTimer = 0.0f;
        _isInBlackScreen = false;
        _hasDecrementedLives = false;
        _hasResetElements = false;
        _hasRespawned = false;
    }

    void Update(float deltaTime) override {
        _deathTimer += deltaTime;

        // Decrementar vidas UNA SOLA VEZ al inicio
        if (_deathTimer >= 0.1f && !_hasDecrementedLives && _player) {
            int currentLives = _player->GetExtraLives();
            if (currentLives > 0) {
                _player->SetExtraLives(currentLives - 1);  // <-- Esto DEBE ejecutarse
            }
            _hasDecrementedLives = true;
        }

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

        // Respawn (DESPUÉS de decrementar y resetear)
        if (_deathTimer >= (DEATH_ANIMATION_TIME + BLACK_SCREEN_TIME * 0.5f) &&
            _hasResetElements && !_hasRespawned) {
            if (_onRespawnPlayer) {
                _onRespawnPlayer();  // Aquí se crea el nuevo player con vidas decrementadas
            }
            _hasRespawned = true;
        }
    }

    void Render() override {}

    bool IsFinished() const override {
        return _deathTimer >= TOTAL_DEATH_TIME;
    }

    int GetNextState() const override {
        if (!_player) return 4;  // GAME_OVER
        return _player->GetExtraLives() <= 0 ? 4 : 0;  // GAME_OVER o PLAYING
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