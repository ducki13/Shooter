#include "Game.h"
#include <iostream>
#include "SDL_image.h" // .png and other formats lib

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
	/////////////////////////////////////////////////////////////////////////////////// render drawings START
	// get the texture source, and ready the surface
	//SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
	//SDL_Surface* pTempSurface = SDL_LoadBMP("assets/animate.bmp");
	



	//*****************************************************************************************************
	//                    Biegajacy kotek - pamietaj dobry czlowieku skonfiguruj foldery z assetami
	//*****************************************************************************************************




	SDL_Surface* pTempSurface = IMG_Load("assets/animate.png"); // SDL_image lib version
	m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	// get the texture dimentions
	// get the width and height dimentions to m_pTexture pointer/variable
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h); // & to adres zmiennej odwolanie sie do adresu w headerze
																						  //set the dimentions of the source rectangle

	m_sourceRectangle.x = 0; // 0,0 of the drawing rectangle from hte picture
	m_sourceRectangle.y = 0;

	// change the drawn dimentions of the picture
	m_sourceRectangle.w = 128;
	m_sourceRectangle.h = 82;

	m_destinationRectangle.x = 0; //move the picture
	m_destinationRectangle.y = 0;

	//m_destinationRectangle.x = m_sourceRectangle.x = 0; //set the picture to o,o of the cartizian coordinate system
	//m_destinationRectangle.y = m_sourceRectangle.y = 0;
	m_destinationRectangle.w = m_sourceRectangle.w;
	m_destinationRectangle.h = m_sourceRectangle.h;

	///////////////////////////////////////////////////////////////////////////////////// render drawings END


	std::cout << "init success\n";
	m_bRunning = true; // everything inited successfully,start the main loop



	return true;
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer); // clear the renderer to the draw color

								  //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle,	&m_destinationRectangle); // draw with dimentions from init
								  //SDL_RenderCopy(m_pRenderer, m_pTexture, 0, 0); // draw picture fullscrene max hight/width of screen
	SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, 0, 0, SDL_FLIP_HORIZONTAL); // pass in the horizontal flip

	SDL_RenderPresent(m_pRenderer); // draw to the screen
}



void Game::update()
{
	m_sourceRectangle.x = 128 * int(((SDL_GetTicks() / 100) % 6));
}

void Game::handleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	std::cout << "cleaning game\n";
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
