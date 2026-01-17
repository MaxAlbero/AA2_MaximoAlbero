#include "Game.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "SplashScreen.h"
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
	RM->LoadTexture("resources/UmaSentimiento.jpg");
	RM->LoadTexture("resources/VMedusa.png");
	RM->LoadTexture("resources/pompa.png");
	RM->LoadTexture("resources/caballo.png");
	RM->LoadTexture("resources/RayoNave.png");
	RM->LoadTexture("resources/Wailord.png");

	RM->LoadFont("resources/fonts/hyperspace.ttf");

	//Aqui la carrega de totes les escenes
	assert(SM.AddScene("SplashScreen", new SplashScreen()));
	assert(SM.AddScene("MainMenu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));


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
