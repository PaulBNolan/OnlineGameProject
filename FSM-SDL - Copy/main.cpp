#include <iostream>
#include <thread>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"
#include "Client/Client.h"
using namespace std;

int main(int argc, char** argv) {

	DEBUG_MSG("Game Object Created");

	Game* game = new Game();

	Client m_client("127.0.0.1", 1111); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
	if (!m_client.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return -1;
	}

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
		m_client.SendString(game->m_player->GetPosAsString());
	}

	DEBUG_MSG("Calling Cleanup");
	game->clean();
	game->unloadContent();

	return 0;
}