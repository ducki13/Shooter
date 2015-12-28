#pragma once
#ifndef __Game__
#define __Game__
#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include <vector>
#include <SDL.h>
#include <SDL_mouse.h>
#include "InputHandler.h"



class Game
{
public:


	// simply set the running variable to true
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void draw(); // rysowanie do klasy gameobjectow
	void clean();
	void quit();
	// a function to access the private running variable
	bool running() { return m_bRunning; }
	int getGameWidth() const;
	int getGameHeight() const;

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	// create the public instance function
	static Game* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}



	std::vector<GameObject*> m_gameObjects;


private:
	// make the constructor private
	Game() {}
	~Game() {}
	// create the s_pInstance member variable
	static Game* s_pInstance;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	SDL_Texture* m_pTexture; // the new SDL_Texture variable
	SDL_Rect m_sourceRectangle; // the first rectangle
	SDL_Rect m_destinationRectangle; // another rectangle

	int m_currentFrame;

	bool m_bRunning;

	int m_gameWidth;
	int m_gameHeight;
};
// create the typedef
typedef Game TheGame;

#endif /* defined(__Game__) */



