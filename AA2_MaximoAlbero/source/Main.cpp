#include <SDL3/SDL.h>
#include <exception>
#include <iostream>
#include "Game.h"

#include "RenderManager.h"
#include "TimeManager.h"

int main() {

	//RM->SayHi();

	Game game;

	game.Init();

	while (game.IsRunning()) {
		
		TM.Update();
		//std::cout << TM.GetElapsedTime() << std::endl;
		if (TM.ShouldUpdateGame())
		{
			game.HandleEvents();
			game.Update();
			game.Render();
			TM.ResetDeltaTime();
		}
	}

	//Release
	game.Release();

	return 0;
}