#pragma once
#include "Scene.h"
#include "TextObject.h"
#include "Button.h"
#include "SceneManager.h"
#include "ScoreManager.h"
#include "RenderManager.h"

class Ranking : public Scene {
private:
    std::vector<TextObject*> rankingTexts;

public:
    Ranking() = default;

    void OnEnter() override {
        TextObject* titleText = new TextObject("HIGH SCORES");
        titleText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, 50.f };
        titleText->GetTransform()->scale = Vector2(2.5f, 2.5f);
        titleText->SetTextColor(SDL_Color{ 255, 215, 0, 255 });
        _ui.push_back(titleText);

        const std::vector<int>& scores = HSM->GetRankingScores();
        const std::vector<std::string>& names = HSM->GetRankingNames();

        float startY = 150.f;
        float lineHeight = 50.f;

        for (size_t i = 0; i < scores.size() && i < 10; i++) {

            std::string rankingText = std::to_string(i + 1) + ". " + names[i] + " - " + std::to_string(scores[i]);

            TextObject* scoreText = new TextObject(rankingText);
            scoreText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, startY + (i * lineHeight) };
            scoreText->GetTransform()->scale = Vector2(1.5f, 1.5f);

            // Colorear el primer lugar diferente
            if (i == 0) {
                scoreText->SetTextColor(SDL_Color{ 255, 215, 0, 255 });
            }
            else {
                scoreText->SetTextColor(SDL_Color{ 200, 200, 200, 255 });
            }

            _ui.push_back(scoreText);
            rankingTexts.push_back(scoreText);
        }


        if (scores.empty()) {
            TextObject* emptyText = new TextObject("NO HIGH SCORES YET");
            emptyText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT / 2.0f };
            emptyText->GetTransform()->scale = Vector2(1.5f, 1.5f);
            emptyText->SetTextColor(SDL_Color{ 255, 100, 100, 255 });
            _ui.push_back(emptyText);
        }

        // Botón para volver al menú
        Button* backButton = new Button([]() {
            SM.SetNextScene("MainMenu");
            });
        backButton->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT - 80.f };
        _ui.push_back(backButton);

        TextObject* backText = new TextObject("RETURN TO MAIN MENU");
        backText->GetTransform()->position = { (float)RM->WINDOW_WIDTH / 2.0f, (float)RM->WINDOW_HEIGHT - 60.f };
        backText->GetTransform()->scale = Vector2(1.2f, 1.2f);
        _ui.push_back(backText);
    }

    void Update() override {
        Scene::Update();
    }

    void Render() override {
        Scene::Render();
    }
};