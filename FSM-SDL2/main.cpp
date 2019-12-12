#include <iostream>
#include <thread>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
using namespace std;

int main(int argc, char** argv) {

	DEBUG_MSG("Game Object Created");

	Game* game = new Game();

	

	//Adjust screen positions as needed
	DEBUG_MSG("Game Initialising");
	game->init("SDL StarterKit", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1000, false);

	DEBUG_MSG("Loading Content");
	game->loadContent();


	DEBUG_MSG("Game Loop Starting......");
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	DEBUG_MSG("Calling Cleanup");
	game->clean();
	game->unloadContent();

	return 0;
}