#pragma once



#include<SDL.h>
#include <iostream>
#include "Game.h"

//SDL_Window* g_pWindow = 0;
//SDL_Renderer* g_pRenderer = 0;

const int FPS = 60; // to FPS
const int DELAY_TIME = 1000.0f / FPS; //to FPS

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime; //to FPS

	std::cout << "game init attempt...\n";
	if (TheGame::Instance()->init("Space shooter v0.0.2",
		100, 100, 800, 600, false))
	{
		std::cout << "game init success!\n";

		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime< DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
	}
	else
	{
		std::cout << "game init failure - " << SDL_GetError() << "\n";
		return -1;
	}

	std::cout << "game closing...\n";
	TheGame::Instance()->clean();
	return 0;
}
