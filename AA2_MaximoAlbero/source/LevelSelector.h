#pragma once
#include "Scene.h"
#include "Button.h"
#include "LevelManager.h"
#include "TextObject.h"
#include "SceneManager.h"
#include "RenderManager.h"

class LevelSelector : public Scene {
public:
    LevelSelector() = default;

    void OnEnter() override {
        // Título
        TextObject* text = new TextObject("SELECT THE LEVEL YOU WANT TO PLAY");
        text->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.5f, 50.f };
        text->GetTransform()->scale = Vector2(1.8f, 1.8f);
        _ui.push_back(text);

        // Obtener los niveles
        const std::vector<Level>& levels = LM->GetLevels();

        // Crear botones dinámicamente para cada nivel
        float startY = 200.f;
        float buttonSpacing = 120.f;

        for (size_t i = 0; i < levels.size(); i++) {
            // Botón
            Button* levelButton = new Button([i]() {
                LM->SetCurrentLevel(i);
                SM.SetNextScene("Gameplay");
                });
            levelButton->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.0f, startY + (i * buttonSpacing) };
            _ui.push_back(levelButton);

            // Texto del nivel
            std::string levelText = "LEVEL " + std::to_string(levels[i].levelNumber) + " - " + levels[i].name;
            TextObject* levelNameText = new TextObject(levelText);
            levelNameText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.2f, startY + (i * buttonSpacing) + 30.f };
            levelNameText->GetTransform()->scale = Vector2(1.5f, 1.5f);
            _ui.push_back(levelNameText);
        }

        // Botón volver al menú
        Button* button3 = new Button([]() {
            SM.SetNextScene("MainMenu");
            });
        button3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 5.0f, (float)RM->WINDOW_HEIGHT - 80.f };
        _ui.push_back(button3);

        TextObject* text3 = new TextObject("RETURN TO MAIN MENU");
        text3->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 3.2f, (float)RM->WINDOW_HEIGHT - 50.f };
        text3->GetTransform()->scale = Vector2(1.2f, 1.2f);
        _ui.push_back(text3);
    }

    void Update() override {
        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }
};