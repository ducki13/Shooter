
#pragma once
#include "Game.h"
#include <iostream>
#include "SDL_image.h" // .png and other formats lib
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"


Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, bool fullscreen)
{
	// attempt to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		int flags = 0;
		if (fullscreen)
		{
			flags = SDL_WINDOW_FULLSCREEN;
			//lista flag znajduje sie w tabelce w ksiazce
		}



		std::cout << "SDL init success\n";
		// init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos,
			width, height, flags);

		if (m_pWindow != 0) // window init success
		{
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != 0) // renderer init success
			{
				std::cout << "renderer creation success\n";
				//SDL_SetRenderDrawColor(m_pRenderer,	0, 0, 0, 255);
				SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255); // set color to red
			}
			else
			{
				std::cout << "renderer init fail\n";
				return false; // renderer init fail
			}
		}
		else
		{
			std::cout << "window init fail\n";
			return false; // window init fail
		}
	}
	else
	{
		std::cout << "SDL init fail\n";
		return false; // SDL init fail
	}



	// load texture to be used by the m_gameObjects
	if (!TheTextureManager::Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer))
	{
		return false;
	}

	//make a gameObject and push it on a vector list of objects
	//Initializae Gameobjects
	m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(200, 200, 128, 82, "animate")));
	m_gameObjects.push_back(new Player(new LoaderParams(300, 300, 128, 82, "animate")));
	m_gameObjects.push_back(new Enemy(new LoaderParams(400, 400, 128, 82, "animate")));




	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,start the main loop



	return true;
}

//version with TextureManager
void Game::render()
{

	SDL_RenderClear(m_pRenderer); // czyszczenie renderera, po tej instrukcji wstaw wyswietlanie np. funkcje draw

								  //wstaw wyswietlanie obrazow:

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	// to draw
	TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);


	SDL_RenderPresent(m_pRenderer); // konczenie pracy renderera
}

// end version with TextureManager



//version with texture Manager
void Game::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));


	// loop through and update our objects

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	//LOOP trough GameOBjects END

}
// end version with TextureManager

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::clean()
{


	std::cout << "cleaning game\n";

	TheInputHandler::Instance()->clean(); // Inputs

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::draw()
{

	for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}

}

void Game::quit()
{
	//click X on window and SDL_Quit
	SDL_Delay(500);
	// clean up SDL
	SDL_Quit();
	// exit the main game loop
	m_bRunning = false;
}