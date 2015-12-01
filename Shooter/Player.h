#pragma once
#include "SDLGameObject.h"
#include "GameObject.h"
#include <SDL.h>
#include <SDL_mouse.h>
#include "InputHandler.h"


class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
private:
	void handleInput();
};
