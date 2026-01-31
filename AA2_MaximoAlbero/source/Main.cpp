#include <SDL3/SDL.h>
#include <exception>
#include <iostream>
#include "Game.h"

#include "RenderManager.h"
#include "TimeManager.h"

int main() {
	Game game;

	game.Init();

	while (game.IsRunning()) {
		
		TM.Update();
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