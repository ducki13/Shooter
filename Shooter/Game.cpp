#include "Game.h"

#include <iostream>
#include "InputHandler.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "AnimatedGraphic.h"
#include "MenuButton.h"
#include "Player.h"
#include "Enemy.h"

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
                //SDL_SetRenderDrawColor(m_pRenderer, 173, 216, 230, 255); // set color to red
                SDL_GetWindowSize(m_pWindow, &m_gameWidth, &m_gameHeight);
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

	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,start the main loop

    TheInputHandler::Instance()->initializeJoysticks();

    GameObjectFactory* pGOF = GameObjectFactory::Instance();
    pGOF->registerType("AnimatedGraphic", new AnimatedGraphicCreator());
    pGOF->registerType("MenuButton", new MenuButtonCreator());
    pGOF->registerType("Player", new PlayerCreator());
    pGOF->registerType("Enemy", new EnemyCreator());
	pGOF->registerType("Asteroid", new AsteroidCreator());

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->pushState(new MainMenuState());

	SoundManager::Instance()->load("assets/shootSound.wav", "shoot", SOUND_SFX);

	return true;
}

//version with TextureManager
void Game::render()
{

	SDL_RenderClear(m_pRenderer); // czyszczenie renderera, po tej instrukcji wstaw wyswietlanie np. funkcje draw

	m_pGameStateMachine->render();

								  //wstaw wyswietlanie obrazow:

	//for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	//{
	//	m_gameObjects[i]->draw();
	//}
	// to draw
	//TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);


	SDL_RenderPresent(m_pRenderer); // konczenie pracy renderera
}

// end version with TextureManager



//version with texture Manager
void Game::update()
{
	m_pGameStateMachine->update();

	//m_currentFrame = int(((SDL_GetTicks() / 100) % 6));


	// loop through and update our objects

	//for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
	//{
	//	m_gameObjects[i]->update();
	//}

	//LOOP trough GameOBjects END

}
// end version with TextureManager

void Game::handleEvents()
{
    InputHandler::Instance()->update();

    if (InputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
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

int Game::getGameWidth() const
{
	return m_gameWidth;
}

int Game::getGameHeight() const
{
	return m_gameHeight;
}
