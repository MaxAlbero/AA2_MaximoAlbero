#include "Game.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "LevelManager.h"
#include "AudioManager.h"
#include "Gameplay.h"
#include "MainMenu.h"
#include "Ranking.h"
#include "SplashScreen.h"
#include "LevelSelector.h"
#include "NameInputScene.h"
#include <cassert>


void Game::HandleEvents()
{
	_isRunning = !IM->Listen();
}

void Game::Init() {
	srand(time(NULL));
	RM->Init();
	AM->Init();

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
	RM->LoadTexture("resources/Richard.png");
	RM->LoadTexture("resources/daniels.png");
	RM->LoadTexture("resources/torpedo.png");
	RM->LoadTexture("resources/ufo.png");
	RM->LoadTexture("resources/chainsaw.png");
	RM->LoadTexture("resources/annoyer.png");
	RM->LoadTexture("resources/missile.png");
	RM->LoadTexture("resources/crab.png");
	RM->LoadTexture("resources/father.png");
	RM->LoadTexture("resources/powerup_spritesheet.png");
	RM->LoadTexture("resources/explosion_spritesheet.png");

	//Text Fonts
	RM->LoadFont("resources/fonts/cidergum.ttf");

	//SFX and Music
	AM->LoadSoundData("resources/audio/sfx/defeat.wav");
	AM->LoadSoundData("resources/audio/sfx/victory.wav");
	AM->LoadSoundData("resources/audio/sfx/explode10.wav");
	AM->LoadSoundData("resources/audio/sfx/button1.wav");
	AM->LoadSoundData("resources/audio/sfx/pickup_battery.wav");
	AM->LoadSoundData("resources/audio/sfx/LegoYodaDeath.wav");
	AM->LoadSoundData("resources/audio/sfx/sub_select.wav");
	AM->LoadSoundData("resources/audio/sfx/move.wav");
	AM->LoadSoundData("resources/audio/sfx/fire1.wav");
	AM->LoadSoundData("resources/audio/sfx/hit_wall.wav");
	AM->LoadSoundData("resources/audio/sfx/gurp2.wav");

	AM->LoadSoundData("resources/audio/music/MenuBackground.wav");
	AM->LoadSoundData("resources/audio/music/GameplayBackground.wav");

	assert(SM.AddScene("SplashScreen", new SplashScreen()));
	assert(SM.AddScene("MainMenu", new MainMenu()));
	assert(SM.AddScene("Gameplay", new Gameplay()));
	assert(SM.AddScene("LevelSelector", new LevelSelector()));
	assert(SM.AddScene("NameInput", new NameInputScene()));
	assert(SM.AddScene("Ranking", new Ranking()));

	HSM->LoadRankingFromFile("resources/ranking.xml");

	//assert(SM.InitFirstScene("SplashScreen"));
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
	AM->HaltAudio();
	SDL_Quit();
}