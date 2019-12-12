#ifndef GAME_HPP
#define GAME_HPP
#include <SDL.h>
#undef main
#include <stdio.h>
#include "Debug.h"
#include "Player.h"
#include "Dot.h"
#include "Client.h"
class Game
{
public:
	Game();
	~Game();

	//This initialises the game
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	/// <summary>
	/// This function handles inputs
	/// </summary>
	void handleEvents();
	/// <summary>
	/// This function updates the game
	/// </summary>
	void update();
	/// <summary>
	/// This function renders the game
	/// </summary>
	void render();
	void clean();

	/// <summary>
	/// This function is used to set up the sprite sheet
	/// </summary>
	void loadContent();
	/// <summary>
	/// This function cleans the game when finished
	/// </summary>
	void unloadContent();

	/// <summary>
	/// This function is used to determine whether the game should be running
	/// </summary>
	bool running() { return m_running; };
	Dot* m_player;
	Dot* m_otherPlayer;
	Client* m_client;
private:
	int cnt = 0;
	bool m_running;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	//These three values are used for rendering sprites
	SDL_Texture* m_texture;
	SDL_Rect m_source;
	SDL_Rect m_destination;

	//Player* m_player;
	//Input m_input;

	//These two values are used to animate the sprite
	Uint32 m_ticks;
	Uint32 m_sprite;

	SDL_Surface* m_surface;
};

#endif // !GAME_HPP

