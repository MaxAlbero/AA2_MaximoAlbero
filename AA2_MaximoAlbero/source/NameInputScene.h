#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "InputManager.h"
#include "RenderManager.h"
#include <string>

class NameInputScene : public Scene {
private:
    std::string _playerName;
    TextObject* _titleText;
    TextObject* _inputText;
    TextObject* _instructionText;
    bool _finished;
    float _blinkTimer;
    const float BLINK_SPEED = 0.5f;

public:
    NameInputScene() : _finished(false), _blinkTimer(0.f) {}

    ~NameInputScene() {
        if (_titleText) delete _titleText;
        if (_inputText) delete _inputText;
        if (_instructionText) delete _instructionText;
    }

    void OnEnter() override {
        _playerName = "";
        _finished = false;
        _blinkTimer = 0.f;

        // Título
        _titleText = new TextObject("ENTER YOUR NAME");
        _titleText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 4.f);
        _titleText->GetTransform()->scale = Vector2(2.5f, 2.5f);
        _titleText->SetTextColor(SDL_Color{ 0, 255, 255, 255 });
        _ui.push_back(_titleText);

        // Entrada de nombre
        _inputText = new TextObject("_");
        _inputText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT / 2.f);
        _inputText->GetTransform()->scale = Vector2(2.f, 2.f);
        _inputText->SetTextColor(SDL_Color{ 255, 255, 255, 255 });
        _ui.push_back(_inputText);

        // Instrucciones
        _instructionText = new TextObject("PRESS ENTER TO SUBMIT");
        _instructionText->GetTransform()->position = Vector2(RM->WINDOW_WIDTH / 2.f, RM->WINDOW_HEIGHT * 3.f / 4.f);
        _instructionText->GetTransform()->scale = Vector2(1.f, 1.f);
        _instructionText->SetTextColor(SDL_Color{ 150, 150, 150, 255 });
        _ui.push_back(_instructionText);
    }

    void OnExit() override {
        Scene::OnExit();
    }

    void Update() override {
        _blinkTimer += TM.GetDeltaTime();

        // Procesar teclas
        HandleInput();

        // Actualizar visual del nombre con cursor parpadeante
        std::string displayName = _playerName;
        if (std::fmod(_blinkTimer, BLINK_SPEED * 2.f) < BLINK_SPEED) {
            displayName += "_";
        }
        _inputText->SetText(displayName);

        // Si se presionó enter y hay nombre, terminar
        if (_finished) {
            return;
        }

        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }

    bool IsFinished() const { return _finished; }
    std::string GetPlayerName() const { return _playerName; }

private:
    void HandleInput() {
        const int MAX_NAME_LENGTH = 10;

        // Letras mayúsculas (A-Z)
        for (int key = SDLK_A; key <= SDLK_Z; key++) {
            if (IM->GetEvent(key, KeyState::DOWN) && _playerName.length() < MAX_NAME_LENGTH) {
                _playerName += static_cast<char>('A' + (key - SDLK_A));
                return;
            }
        }

        // Números (0-9)
        for (int key = SDLK_0; key <= SDLK_9; key++) {
            if (IM->GetEvent(key, KeyState::DOWN) && _playerName.length() < MAX_NAME_LENGTH) {
                _playerName += static_cast<char>('0' + (key - SDLK_0));
                return;
            }
        }

        // Backspace (borrar)
        if (IM->GetEvent(SDLK_BACKSPACE, KeyState::DOWN) && !_playerName.empty()) {
            _playerName.pop_back();
            return;
        }

        // Enter (enviar)
        if (IM->GetEvent(SDLK_RETURN, KeyState::DOWN) && !_playerName.empty()) {
            _finished = true;
            return;
        }

        // Espacio
        if (IM->GetEvent(SDLK_SPACE, KeyState::DOWN) && _playerName.length() < MAX_NAME_LENGTH) {
            _playerName += " ";
            return;
        }
    }
};