#include "Game.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "LevelSelector.h"
#include "NameInputScene.h"
#include "Ranking.h"
#include <cassert>


void Game::HandleEvents()
{
	_isRunning = !IM->Listen();
}

void Game::Init() {
	srand(time(NULL));
	RM->Init();

	//Aqui la carrega de tots els recursos del joc
	RM->LoadTexture("resources/image.png");
	RM->LoadTexture("resources/background.jpg");
	RM->LoadTexture("resources/VMedusa.png");
	RM->LoadTexture("resources/bebe.jpg");
	RM->LoadTexture("resources/pompa.png");
	RM->LoadTexture("resources/caballo.png");
	RM->LoadTexture("resources/RayoNave.png");
	RM->LoadTexture("resources/Wailord.png");
	RM->LoadTexture("resources/pacman.png");
	RM->LoadTexture("resources/pinky.png");
	RM->LoadTexture("resources/BulletBill.png");
	RM->LoadTexture("resources/BillBuster.png");
	RM->LoadTexture("resources/bat.png");
	RM->LoadTexture("resources/turret.png");
	RM->LoadTexture("resources/slime.png");

	RM->LoadFont("resources/fonts/cidergum.ttf");
	//RM->LoadFont("resources/fonts/hyperspace.ttf");

	//Aqui la carrega de totes les escenes
	assert(SM.AddScene("SplashScreen", new SplashScreen()));
	assert(SM.AddScene("MainMenu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));
	assert(SM.AddScene("LevelSelector", new LevelSelector()));
	assert(SM.AddScene("NameInput", new NameInputScene()));  // NUEVA
	//assert(SM.AddScene("RankingScreen", new RankingScreen()));

	HSM->LoadRankingFromFile("resources/ranking.json");

	//assert(SM.InitFirstScene("SplashScreen"));
	//assert(SM.InitFirstScene("MainMenu"));
	assert(SM.InitFirstScene("Gameplay"));

	_isRunning = !IM->Listen();
}


void Game::Update() {
	SM.UpdateCurrentScene();
}

void Game::Render() {
	RM->ClearScreen();
	SM.GetCurrentScene()->Render();
	RM->RenderScreen();
}

void Game::Release() {
	RM->Release();
	SDL_Quit();
}
