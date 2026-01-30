#pragma once
#include "Scene.h"
#include "NameInputScene.h"
#include "SceneManager.h"
#include "ScoreManager.h"

class GameOverScreen : public Scene {
private:
    NameInputScene* _nameInput;
    bool _waitingForName;

public:
    GameOverScreen() : _nameInput(nullptr), _waitingForName(true) {}

    ~GameOverScreen() {
        if (_nameInput) delete _nameInput;
    }

    void OnEnter() override {
        if (HSM->IsInTopTen(HSM->GetCurrentScore())) {
            // Mostrar pantalla de entrada de nombre
            _nameInput = new NameInputScene();
            _nameInput->OnEnter();
            _waitingForName = true;
        }
        else {
            // No está en top 10, volver al menú
            SM.SetNextScene("MainMenu");
        }
    }

    void OnExit() override {
        Scene::OnExit();
        if (_nameInput) {
            _nameInput->OnExit();
            delete _nameInput;
        }
    }

    void Update() override {
        if (_waitingForName && _nameInput) {
            _nameInput->Update();

            if (_nameInput->IsFinished()) {
                // Guardar score con nombre
                std::string playerName = _nameInput->GetPlayerName();
                int finalScore = HSM->GetCurrentScore();

                HSM->AddToRanking(finalScore, playerName);
                HSM->SaveRankingToFile("resources/ranking.xml");

                _waitingForName = false;
                SM.SetNextScene("MainMenu");
            }
        }

        Scene::Update();
    }

    void Render() override {
        if (_waitingForName && _nameInput) {
            _nameInput->Render();
        }
        else {
            Scene::Render();
        }
    }
};