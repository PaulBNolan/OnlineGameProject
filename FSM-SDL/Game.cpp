
#include "Game.h"
#include <iostream>

Game::Game() : m_running(false)
{
	//m_player = new Player();
	m_player = new Dot(false);
	m_otherPlayer = new Dot(true);

	std::string m_title = "Title";

	m_client = new Client("127.0.0.1", 1111, m_player); //Create client to connect to server 127.0.0.1 [localhost] on port 1111
}

Game::~Game()
{
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised!..." << std::endl;

		m_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_window)
		{
			std::cout << "Window created!" << std::endl;
		}

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		if (m_renderer)
		{
			SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}

		m_running = true;
		m_player->Init(m_renderer);
	}
	else 
	{
		m_running = false;
	}

	if (!m_client->Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	//switch (event.type)
	//{
	//case SDL_KEYDOWN:
	//	switch (event.key.keysym.sym)
	//	{
	//	case SDLK_ESCAPE:
	//		m_running = false;
	//		break;
	//	case SDLK_UP:
	//		//DEBUG_MSG("Up Key Pressed");
	//		m_source.y = 32 * 3;
	//		SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
	//		//m_input.setCurrent(Input::Action::UP);
	//		break;
	//	case SDLK_DOWN:
	//		//DEBUG_MSG("Down Key Pressed");
	//		m_source.y = 32 * 0;
	//		SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
	//		break;
	//	case SDLK_LEFT:
	//		//DEBUG_MSG("Left Key Pressed");
	//		m_source.y = 32 * 1;
	//		SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
	//		//m_input.setCurrent(Input::Action::LEFT);
	//		break;
	//	case SDLK_RIGHT:
	//		//DEBUG_MSG("Right Key Pressed");
	//		m_source.y = 32 * 2;
	//		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
	//		//m_input.setCurrent(Input::Action::RIGHT);
	//		break;
	//	default:
	//		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	//		//m_input.setCurrent(Input::Action::IDLE);
	//		break;
	//	}
		//m_player->handleInput();
	m_player->handleEvent(event);
	//}
}

void Game::update()
{
	//cnt++;
	//std::cout << cnt << std::endl;


	//m_player->update();
	m_player->move(SDL_GetWindowSurface(m_window)->h, SDL_GetWindowSurface(m_window)->w);
}

void Game::render()
{
	SDL_RenderClear(m_renderer);

	//DEBUG_MSG("Width Source" + m_destination.w);
	//DEBUG_MSG("Width Destination" + m_destination.w);
	m_player->render(m_renderer);
	//if (m_renderer != nullptr && m_texture != nullptr)
		//SDL_RenderCopy(m_renderer, m_texture, &m_source, &m_destination);

	SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}

void Game::loadContent()
{
	DEBUG_MSG("Loading Content");
	m_surface = SDL_LoadBMP("ASSETS/IMAGES/sprite.bmp");
	m_texture = SDL_CreateTextureFromSurface(m_renderer, m_surface);
	SDL_FreeSurface(m_surface);

	if (SDL_QueryTexture(m_texture, NULL, NULL, &m_source.w, &m_destination.h) == 0)
	{
		m_source.x = 0;
		m_source.y = 0;
		m_destination.x = 640;
		m_destination.y = 640;
		m_source.w = 32;
		m_source.h = 32;
		m_destination.w = m_source.w * 10;
		m_destination.h = m_source.h * 10;

		DEBUG_MSG("Destination X:" + m_destination.x);
		DEBUG_MSG("Destination Y:" + m_destination.y);
		DEBUG_MSG("Destination W:" + m_destination.w);
		DEBUG_MSG("Destination H:" + m_destination.h);
	}
	else
	{
		DEBUG_MSG("Texture Query Failed");
		m_running = false;
	}
}

void Game::unloadContent()
{
	DEBUG_MSG("Unloading Content");
	//delete(m_p_Texture);
	//m_p_Texture = NULL;
}
