#pragma once
#include "TextObject.h"
#include "Scene.h"
#include "TestObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpawnWaves.h"
#include "ScoreManager.h"

//POWERUPS TESTS
#include "PowerUp.h"

#include "Background.h"

#include "LoadLevel.h"

//Testing Enemies
#include "Circler.h"
#include "CirclerBody.h"
#include "Bubbles.h"
#include "Annoyer.h"
#include "TurboChainsaw.h"

class Gameplay : public Scene {
private:
	Player* player;

	TextObject* scoreText;
	TextObject* highScoreText;
	TextObject* extraLivesText;
	TextObject* shieldText;
	TextObject* cannonText;
	TextObject* laserText;

	//void SaveScore();
	//void LoadLevelFromFile(std::string path);


public:
	//SpawnWaves* waves;
	Gameplay() = default;

	void OnEnter() override {

		//waves = new SpawnWaves();
		//LoadLevel levelLoader;
		//std::string filePath = "level_1.xml";

		//if (levelLoader.LoadFile(filePath, waves->GetWaveOrder(), waves->GetAmountEnemies())) {
		//	std::cout << "Level loaded successfully" << std::endl;
		//	waves->Start();
		//}
		//else {
		//	std::cout << "Failed to load level" << std::endl;
		//}

		Background* bg1 = new Background();
		bg1->GetTransform()->position = Vector2(RM->WINDOW_WIDTH - RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);

		Background* bg2 = new Background();
		bg2->GetTransform()->position = Vector2(RM->WINDOW_WIDTH, RM->WINDOW_HEIGHT / 2.f);

		SPAWNER.SpawnObject(bg1);
		SPAWNER.SpawnObject(bg2);

		player = new Player();
		SPAWNER.SpawnObject(player);

		//waves->SetPlayer(player);

		// HUD
		float hudX = 60.f;
		float hudY = RM->WINDOW_HEIGHT - 60.f;
		float spacing = 300.f;

		// Score
		scoreText = new TextObject("SCORE: ");
		scoreText->GetTransform()->position = Vector2(hudX, hudY);
		scoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(scoreText);

		//HIGHEST SCORE <-- RIGHT NOW IMPOSSIBLE
		highScoreText = new TextObject("HIGHSCORE: ");
		highScoreText->GetTransform()->position = Vector2(hudX, hudY - 30.f);
		highScoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(highScoreText);

		// Extra Lives
		extraLivesText = new TextObject("LIVES: ");
		extraLivesText->GetTransform()->position = Vector2(hudX + spacing, hudY);
		extraLivesText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(extraLivesText);

		// Shield/Energy
		shieldText = new TextObject("SHIELD: ");
		shieldText->GetTransform()->position = Vector2(hudX + spacing * 2, hudY);
		shieldText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(shieldText);

		// Cannon
		cannonText = new TextObject("CANNON: NO");
		cannonText->GetTransform()->position = Vector2(hudX + spacing * 3, hudY);
		cannonText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(cannonText);

		// Laser
		laserText = new TextObject("LASER: NO");
		laserText->GetTransform()->position = Vector2(hudX + spacing * 4, hudY);
		laserText->SetTextColor(SDL_Color{ 0, 0, 0, 0 });
		_ui.push_back(laserText);


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

		Bubbles* bubble1 = new Bubbles(TOP_TO_BOTTOM);
		Bubbles* bubble2 = new Bubbles(TOP_TO_BOTTOM, 100.f);

		SPAWNER.SpawnObject(bubble1);
		SPAWNER.SpawnObject(bubble2);


	}

	void OnExit() override { Scene::OnExit(); }

	void Update() override {
		//waves->Update();

		Scene::Update(); 
		UpdateHUD();
	}

	void Render() override { Scene::Render(); }

	private:
		void UpdateHUD() {
			if (!player) return;

			int currentScore = HSM->GetCurrentScore();
			bool isNewHighScore = (currentScore >= HSM->GetHighScore());

			// Cambiar color del score si es nuevo highscore
			if (isNewHighScore) {
				scoreText->SetTextColor(SDL_Color{ 255, 215, 0, 255 }); // Dorado
			}
			else {
				scoreText->SetTextColor(SDL_Color{ 0, 0, 0, 0 }); // Negro
			}

			std::string scoreStr = FormatScore(currentScore);
			scoreText->SetText("SCORE: " + scoreStr);

			int highScore = HSM->GetHighScore();
			std::string highScoreStr = FormatScore(highScore);
			highScoreText->SetText("HIGHSCORE: " + highScoreStr);

			// Actualizar vidas
			std::string livesStr = "LIVES: " + std::to_string(player->GetExtraLives());
			extraLivesText->SetText(livesStr);

			// Actualizar energía/escudo
			std::string shieldStr = "SHIELD: " + std::to_string(player->GetEnergy());
			shieldText->SetText(shieldStr);

			// Actualizar cañón
			std::string cannonStr = "CANNON: " + std::to_string(player->GetCannonAmmo());
			cannonText->SetText(cannonStr);

			// Actualizar láser
			std::string laserStr = "LASER: " + std::to_string(player->GetLaserAmmo());
			laserText->SetText(laserStr);
		}

		// Función para formatear score a 6 dígitos
		std::string FormatScore(int score) {
			std::string scoreStr = std::to_string(score);
			if (scoreStr.length() > 6) {
				// Si tiene más de 6 dígitos, mostrar solo los últimos 6
				scoreStr = scoreStr.substr(scoreStr.length() - 6);
			}
			else {
				// Rellenar con ceros a la izquierda
				scoreStr = std::string(6 - scoreStr.length(), '0') + scoreStr;
			}
			return scoreStr;
		}
};