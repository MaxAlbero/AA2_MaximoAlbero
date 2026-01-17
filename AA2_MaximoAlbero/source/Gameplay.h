#pragma once
#include "TextObject.h"
#include "Scene.h"
#include "TestObject.h"
#include "Player.h"
#include "Enemy.h"
#include "SpawnWaves.h"


//POWERUPS TESTS
#include "PowerUp.h"
#include "PowerUp1000.h"

#include "Background.h"

#include "LoadLevel.h"

//Testing Colisions
#include "Chomper.h"
#include "BioTitan.h"

class Gameplay : public Scene {
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

		Player* player = new Player();
		SPAWNER.SpawnObject(player);

		//waves->SetPlayer(player);

		//Testing PowerUps
		//SPAWNER.SpawnObject(new PowerUp()); //"resources/image.png", Vector2(0.f, 0.f), Vector2(100.f, 100.f))
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

		//SPAWNER.SpawnObject(new Chomper(Vector2(RM->WINDOW_WIDTH / 2.0f, RM->WINDOW_HEIGHT / 2.0f)));
		//SPAWNER.SpawnObject(new BioTitan());
	}

	void OnExit() override { Scene::OnExit(); }

	void Update() override {
		//waves->Update();

		Scene::Update(); 
	
	}

	void Render() override { Scene::Render(); }
private:
	//void SaveScore();
	//void LoadLevelFromFile(std::string path);
};